"""Synthetic tests for bootstrap_fsm. Run: python3 -B test_bootstrap.py"""
from __future__ import annotations

import unittest

from bootstrap_fsm import (
    BootstrapError,
    StartParams,
    build_credentials,
    link_local_from_bssid,
    plan_bootstrap,
    select_endpoint,
    validate_start,
)


class ValidationTests(unittest.TestCase):
    def test_valid_cfmoto_like(self):
        p = StartParams(
            ssid="CFMOTO4801",
            password="synthetic-pass",
            security_type=2,
            channel=157,
            wifi_ips=("192.168.43.1",),
            port=7000,
            device_id="synthetic-device",
        )
        ssid, security, channel = validate_start(p)
        self.assertEqual((ssid, security, channel), ("CFMOTO4801", 2, 157))

    def test_empty_ssid_rejected(self):
        with self.assertRaises(BootstrapError):
            validate_start(StartParams(ssid="   ", password="x", security_type=2, channel=6))

    def test_passphrase_with_security_none_rejected(self):
        with self.assertRaises(BootstrapError):
            validate_start(StartParams(ssid="Lab", password="x", security_type=0, channel=6))

    def test_security_type_3_rejected(self):
        with self.assertRaises(BootstrapError):
            validate_start(StartParams(ssid="Lab", password="x", security_type=3, channel=6))

    def test_invalid_channel_defaults_to_1(self):
        ssid, security, channel = validate_start(
            StartParams(ssid="Lab", password="x", security_type=2, channel=0)
        )
        self.assertEqual(channel, 1)

    def test_missing_uuid_is_not_fabricated(self):
        cred, warnings = build_credentials(
            StartParams(ssid="Lab", password="x", security_type=2, channel=6)
        )
        self.assertIsNone(cred.carplay_uuid)
        self.assertTrue(any("OPEN-NB-3" in w for w in warnings))


class EndpointTests(unittest.TestCase):
    def test_link_local_from_bssid(self):
        self.assertEqual(
            link_local_from_bssid("6c:df:4a:14:6e:ea"),
            "fe80::6edf:4aff:fe14:6eea",
        )

    def test_4301_ipv4_endpoint(self):
        p = StartParams(
            ssid="CFMOTO4801", password="x", security_type=2, channel=157,
            wifi_ips=("192.168.43.1",), port=7000,
        )
        ep, warnings = select_endpoint(p, bssid="6c:df:4a:14:6e:ea", policy="4301-first")
        self.assertEqual(ep.source, "4301")
        self.assertEqual(ep.dial_string(), "192.168.43.1:7000")
        self.assertEqual(warnings, [])

    def test_link_local_endpoint_fallback(self):
        p = StartParams(
            ssid="CFMOTO4801", password="x", security_type=2, channel=157, port=7000,
        )
        ep, warnings = select_endpoint(p, bssid="6c:df:4a:14:6e:ea", policy="4301-first")
        self.assertEqual(ep.source, "link-local")
        self.assertEqual(ep.dial_string(), "fe80::6edf:4aff:fe14:6eea%en0:7000")
        self.assertTrue(any("OPEN-NB-4" in w for w in warnings))

    def test_mdns_endpoint_with_scope(self):
        p = StartParams(ssid="Audi", password="x", security_type=2, channel=149, port=7000)
        mdns = [{"host": "fe80::1c50:9aa2:ce53:8ab9", "port": 7000}]
        ep, _ = select_endpoint(p, bssid=None, mdns=mdns, policy="mdns-first")
        self.assertEqual(ep.source, "mdns")
        self.assertEqual(ep.dial_string(), "fe80::1c50:9aa2:ce53:8ab9%en0:7000")

    def test_no_endpoint(self):
        p = StartParams(ssid="Lab", password="x", security_type=2, channel=6)
        ep, warnings = select_endpoint(p)
        self.assertIsNone(ep)
        self.assertTrue(any("OPEN-NB-4" in w for w in warnings))

    def test_unknown_policy_rejected(self):
        p = StartParams(ssid="Lab", password="x", security_type=2, channel=6)
        with self.assertRaises(BootstrapError):
            select_endpoint(p, policy="nope")


class PlanTests(unittest.TestCase):
    def test_plan_contains_open_items(self):
        p = StartParams(
            ssid="CFMOTO4801", password="x", security_type=2, channel=157,
            wifi_ips=("192.168.43.1",), port=7000,
        )
        plan = plan_bootstrap(p, carplay_uuid="80A46250-7FB2-4A9F-ACF1-8F551F286B88", bssid="6c:df:4a:14:6e:ea")
        self.assertEqual(plan.endpoint.source, "4301")
        self.assertIn("OPEN-NB-2", plan.open_items)
        self.assertIn("OPEN-NB-4", plan.open_items)
        self.assertNotIn("OPEN-NB-3", plan.open_items)

    def test_plan_missing_uuid_adds_open(self):
        p = StartParams(ssid="Lab", password="x", security_type=2, channel=6, port=7000)
        plan = plan_bootstrap(p, bssid="6c:df:4a:14:6e:ea")
        self.assertIn("OPEN-NB-3", plan.open_items)
        self.assertEqual(plan.credentials.carplay_uuid, None)


if __name__ == "__main__":
    unittest.main(verbosity=2)
