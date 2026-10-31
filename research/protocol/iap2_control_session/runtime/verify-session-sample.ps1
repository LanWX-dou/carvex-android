# Verify only the two archived 23G90 handshakes, not arbitrary SYN versions.
$ErrorActionPreference = 'Stop'
$sample = Join-Path $PSScriptRoot 'accessoryd-packets-2026-10-16-221117.log.ips'
if ((Get-FileHash -LiteralPath $sample -Algorithm SHA256).Hash.ToLowerInvariant() -ne '7283f8a1d50c6c920198587f816c86aec996b7d749e84be7db771f5a7595dadd') { throw 'Unexpected sample hash' }
$sessions = @{}
foreach ($line in Get-Content -LiteralPath $sample) {
    if ($line -notmatch '; ([0-9A-F-]{36}); [^;]+; (Acc|iPod); .*control=0x([0-9a-f]+); .*session=0x([0-9a-f]+); .*payload\(len=\d+ chk=0x[0-9a-f]+\)=<([0-9a-f ]*)>') { continue }
    $id = $Matches[1]; $role = $Matches[2]
    $control = [Convert]::ToInt32($Matches[3], 16)
    $session = [Convert]::ToInt32($Matches[4], 16)
    $p = [Convert]::FromHexString(($Matches[5] -replace ' ', ''))
    if (-not $sessions.ContainsKey($id)) { $sessions[$id] = @{} }
    $state = $sessions[$id]
    if ($control -eq 0x80 -and $role -eq 'Acc') {
        if ($p.Length -ne 13 -or $p[0] -ne 1 -or $session -ne 0) { throw 'Unexpected sample SYN' }
        $state.syn = [Convert]::ToHexString([byte[]]$p[10..12])
        $state.number = [int]$p[10]
    } elseif ($control -eq 0xc0 -and $role -eq 'iPod') {
        if (-not $state.ContainsKey('syn') -or $p.Length -ne 13 -or $session -ne 0 -or $state.syn -cne [Convert]::ToHexString([byte[]]$p[10..12])) { throw 'SYNACK tuple/order mismatch' }
        $state.ack = $true
    } elseif ($p.Length -ge 6 -and $p[0] -eq 0x40 -and $p[1] -eq 0x40 -and $p[4] -eq 0x1d -and $p[5] -eq 0 -and $role -eq 'iPod') {
        if (-not $state.ack -or $session -ne $state.number) { throw 'Identification session disagrees with prior handshake' }
        $state.identified = $true
    }
}
if ($sessions.Count -ne 2) { throw 'Expected two sample connections' }
foreach ($id in ($sessions.Keys | Sort-Object)) {
    $state = $sessions[$id]
    if (-not $state.identified) { throw 'Missing identification' }
    Write-Output "$id PASS: accessory SYN tuple $($state.syn) precedes matching iPhone SYNACK and 0x1D00 session $($state.number)"
}
