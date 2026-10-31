# Read-only verification of the archived 23G90 sample, not a trust-chain validator.
# Run with PowerShell 7: pwsh -File ./verify-auth-sample.ps1
$ErrorActionPreference = 'Stop'
$sample = Join-Path $PSScriptRoot 'accessoryd-packets-2026-10-16-221117.log.ips'
$expectedHash = '7283f8a1d50c6c920198587f816c86aec996b7d749e84be7db771f5a7595dadd'
if ((Get-FileHash -LiteralPath $sample -Algorithm SHA256).Hash.ToLowerInvariant() -ne $expectedHash) {
    throw 'Unexpected sample hash'
}
$connections = @{}
foreach ($line in Get-Content -LiteralPath $sample) {
    if ($line -notmatch '; ([0-9A-F-]{36}); .*payload\(len=\d+ chk=0x[0-9a-f]+\)=<([0-9a-f ]+)>') { continue }
    $id = $Matches[1]
    $payload = [Convert]::FromHexString(($Matches[2] -replace ' ', ''))
    if ($payload.Length -lt 10 -or $payload[0] -ne 0x40 -or $payload[1] -ne 0x40 -or $payload[4] -ne 0xaa) { continue }
    $messageId = [int]$payload[5]
    if ($messageId -notin @(1, 2, 3, 6)) { continue }
    $messageLength = ([int]$payload[2] -shl 8) -bor $payload[3]
    $paramLength = ([int]$payload[6] -shl 8) -bor $payload[7]
    if ($messageLength -ne $payload.Length -or $paramLength -ne $payload.Length - 6 -or $payload[8] -ne 0 -or $payload[9] -ne 0) {
        throw 'Unexpected message/parameter layout'
    }
    if (-not $connections.ContainsKey($id)) { $connections[$id] = @{} }
    $connections[$id][$messageId] = [byte[]]$payload[10..($payload.Length - 1)]
}
if ($connections.Count -ne 2) { throw 'Expected two captured authentication exchanges' }
$certificateContainers = @()
foreach ($id in ($connections.Keys | Sort-Object)) {
    $values = $connections[$id]
    foreach ($required in @(1, 2, 3, 6)) {
        if (-not $values.ContainsKey($required)) { throw 'Incomplete exchange' }
    }
    $certificates = [System.Security.Cryptography.X509Certificates.X509Certificate2Collection]::new()
    $certificates.Import($values[1])
    if ($certificates.Count -ne 1) { throw 'Expected one certificate in this sample' }
    $cert = $certificates[0]
    $ec = [System.Security.Cryptography.X509Certificates.ECDsaCertificateExtensions]::GetECDsaPublicKey($cert)
    try {
        if ($ec.ExportParameters($false).Curve.Oid.Value -ne '1.2.840.10045.3.1.7') { throw 'Unexpected curve' }
        if ($values[2].Length -ne 32 -or $values[3].Length -ne 64) { throw 'Unexpected challenge/signature size' }
        if ($cert.SerialNumber -cne [System.Text.Encoding]::ASCII.GetString($values[6])) { throw 'Serial mismatch' }
        $format = [System.Security.Cryptography.DSASignatureFormat]::IeeeP1363FixedFieldConcatenation
        if (-not $ec.VerifyHash($values[2], $values[3], $format)) { throw 'Direct digest verification failed' }
        if ($ec.VerifyData($values[2], $values[3], [System.Security.Cryptography.HashAlgorithmName]::SHA256, $format)) { throw 'Unexpected rehashed verification success' }
        $negative = [byte[]]$values[2].Clone()
        $negative[0] = $negative[0] -bxor 1
        if ($ec.VerifyHash($negative, $values[3], $format)) { throw 'Modified challenge accepted' }
        $certificateContainers += [Convert]::ToHexString($values[1])
        Write-Output "$id PASS: one certificate, P-256, serial matches, raw r||s, direct digest verified; rehash and altered digest rejected"
    } finally {
        if ($null -ne $ec) { $ec.Dispose() }
        foreach ($item in $certificates) { $item.Dispose() }
    }
}
if ($certificateContainers[0] -cne $certificateContainers[1]) { throw 'Expected identical certificate containers across these two connections' }
Write-Output 'PASS: certificate container unchanged across both connections. Trust chain, revocation and other devices NOT verified.'
