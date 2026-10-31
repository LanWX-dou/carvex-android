"""Pure planning model for carplay_network_bootstrap (v0).

This module does NOT perform Wi-Fi association, DHCP, mDNS, or TCP.
It encodes the contract from spec/01-03 so an implementation can be tested
against the documented field/validation/endpoint rules before touching a
real platform.

All network values are synthetic unless a caller passes real observations.
"""
from __future__ import annotations

from dataclasses import dataclass, field
from ipaddress import ip_address
from typing import Iterable, Sequence

# securityType numeric values accepted by the observed WiFiSharing branch.
# The 0/1/2 -> none/WEP/WPA name mapping is still OPEN-NB-2; do not add names here.
VALID_SECURITY_TYPES = (0, 1, 2)

# The doc says channel is a hint and invalid values default to 1 (spec/01 R-NB-1.4).
DEFAULT_CHANNEL = 1
VALID_CHANNEL_RANGE = range(1, 197)


class BootstrapError(ValueError):
    """A validation failure that must stop the bootstrap plan."""


@dataclass(frozen=True)
class StartParams:
    """Relevant subset of iAP2 0x4301, already decoded per control/spec/14."""

    ssid: str | None
    password: str | None = None
    security_type: int | None = None
    channel: int | None = None
    wifi_ips: tuple[str, ...] = ()
    port: int | None = None
    device_id: str | None = None


@dataclass(frozen=True)
class CredentialRecord:
    ssid: str
    password: str | None
    security_type: int
    channel: int
    carplay_uuid: str | None
    carplay_ppid: str | None = None


@dataclass(frozen=True)
class Endpoint:
    host: str
    port: int
    source: str  # "4301" | "link-local" | "mdns" | "config"
    scope: str | None = None

    def dial_string(self) -> str:
        return f"{self.host}%{self.scope}:{self.port}" if self.scope else f"{self.host}:{self.port}"


@dataclass
class BootstrapPlan:
    credentials: CredentialRecord
    endpoint: Endpoint | None
    warnings: list[str] = field(default_factory=list)
    open_items: list[str] = field(default_factory=list)


def validate_start(params: StartParams) -> tuple[str, int, int]:
    """Validate the fields that enter the Wi-Fi credential; return (ssid, security, channel)."""
    ssid = (params.ssid or "").strip()
    if not ssid:
        raise BootstrapError("SSID is empty")

    if params.security_type is None:
        raise BootstrapError("securityType is missing")
    if params.security_type not in VALID_SECURITY_TYPES:
        raise BootstrapError(f"invalid securityType {params.security_type}")

    # The observed WiFiSharing branch rejects "passphrase present but securityType none".
    if params.password and params.security_type == 0:
        raise BootstrapError("passphrase present but securityType is none")

    channel = params.channel if params.channel in VALID_CHANNEL_RANGE else DEFAULT_CHANNEL
    return ssid, params.security_type, channel


def build_credentials(
    params: StartParams,
    carplay_uuid: str | None = None,
    carplay_ppid: str | None = None,
) -> tuple[CredentialRecord, list[str]]:
    """Build the credential record. Missing CarPlayUUID is NOT fabricated."""
    ssid, security, channel = validate_start(params)
    warnings: list[str] = []
    if not carplay_uuid:
        warnings.append("OPEN-NB-3: CarPlayUUID missing; do not derive it from deviceID")
    if params.channel not in VALID_CHANNEL_RANGE and params.channel is not None:
        warnings.append(f"channel {params.channel} invalid; defaulted to {DEFAULT_CHANNEL}")
    return (
        CredentialRecord(
            ssid=ssid,
            password=params.password,
            security_type=security,
            channel=channel,
            carplay_uuid=carplay_uuid,
            carplay_ppid=carplay_ppid,
        ),
        warnings,
    )


def link_local_from_bssid(bssid: str) -> str:
    """Derive the EUI-64 IPv6 link-local address from a BSSID (observed, not universal)."""
    parts = bssid.replace("-", ":").lower().split(":")
    if len(parts) != 6:
        raise BootstrapError(f"invalid BSSID {bssid!r}")
    octets = [int(p, 16) for p in parts]
    if any(o < 0 or o > 255 for o in octets):
        raise BootstrapError(f"invalid BSSID {bssid!r}")
    octets[0] ^= 0x02  # flip the universal/local bit
    eui = octets[:3] + [0xFF, 0xFE] + octets[3:]
    groups = [f"{eui[i] << 8 | eui[i + 1]:x}" for i in range(0, len(eui), 2)]
    return "fe80::" + ":".join(groups)


def _endpoint_from_4301(params: StartParams) -> Endpoint | None:
    if not params.port or not (1 <= params.port <= 65535):
        return None
    for candidate in params.wifi_ips:
        try:
            ip = ip_address(candidate)
        except ValueError:
            continue
        if ip.version == 4:
            return Endpoint(host=str(ip), port=params.port, source="4301")
        if ip.version == 6:
            scope = "en0" if ip.is_link_local else None
            return Endpoint(host=str(ip), port=params.port, source="4301", scope=scope)
    return None


def _endpoint_from_link_local(bssid: str | None, port: int | None) -> Endpoint | None:
    if not bssid or not port or not (1 <= port <= 65535):
        return None
    return Endpoint(host=link_local_from_bssid(bssid), port=port, source="link-local", scope="en0")


def _endpoint_from_mdns(mdns: Sequence[dict] | None) -> Endpoint | None:
    if not mdns:
        return None
    for row in mdns:
        host = str(row.get("host", "")).strip()
        port = row.get("port")
        if not host or not isinstance(port, int) or not (1 <= port <= 65535):
            continue
        try:
            ip = ip_address(host)
        except ValueError:
            continue
        scope = "en0" if ip.version == 6 and ip.is_link_local else None
        return Endpoint(host=str(ip), port=port, source="mdns", scope=scope)
    return None


def select_endpoint(
    params: StartParams,
    bssid: str | None = None,
    mdns: Sequence[dict] | None = None,
    policy: str = "4301-first",
) -> tuple[Endpoint | None, list[str]]:
    """Select a control endpoint under an explicit policy.

    The authority (0x4301 vs mDNS vs link-local) is OPEN-NB-4; the policy is a
    local choice, not a protocol fact.
    """
    warnings: list[str] = []
    candidates: dict[str, Endpoint | None] = {
        "4301": _endpoint_from_4301(params),
        "link-local": _endpoint_from_link_local(bssid, params.port),
        "mdns": _endpoint_from_mdns(mdns),
    }
    orders = {
        "4301-first": ("4301", "link-local", "mdns"),
        "link-local-first": ("link-local", "4301", "mdns"),
        "mdns-first": ("mdns", "4301", "link-local"),
    }
    if policy not in orders:
        raise BootstrapError(f"unknown endpoint policy {policy!r}")
    for name in orders[policy]:
        ep = candidates.get(name)
        if ep:
            if name != orders[policy][0]:
                warnings.append(f"OPEN-NB-4: fell back to {name} endpoint")
            return ep, warnings
    warnings.append("OPEN-NB-4: no usable endpoint; provide 0x4301 wifiIP/port or mDNS SRV")
    return None, warnings


def plan_bootstrap(
    params: StartParams,
    carplay_uuid: str | None = None,
    carplay_ppid: str | None = None,
    bssid: str | None = None,
    mdns: Sequence[dict] | None = None,
    endpoint_policy: str = "4301-first",
) -> BootstrapPlan:
    """Build a pure plan: credentials + endpoint + warnings/open items.

    This is a planning result, not a connected session. Association/DHCP/TCP
    are platform actions that must be executed and logged separately.
    """
    credentials, warnings = build_credentials(params, carplay_uuid, carplay_ppid)
    endpoint, endpoint_warnings = select_endpoint(params, bssid, mdns, endpoint_policy)
    warnings.extend(endpoint_warnings)
    open_items = ["OPEN-NB-1", "OPEN-NB-4", "OPEN-NB-5", "OPEN-NB-6"]
    if not carplay_uuid:
        open_items.append("OPEN-NB-3")
    # The numeric securityType -> name mapping is not closed yet.
    open_items.append("OPEN-NB-2")
    return BootstrapPlan(
        credentials=credentials,
        endpoint=endpoint,
        warnings=warnings,
        open_items=sorted(set(open_items), key=lambda s: int(s.split("-")[-1])),
    )
