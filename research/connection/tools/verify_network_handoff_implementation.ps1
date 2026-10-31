param([switch]$CheckTests)
$ErrorActionPreference = 'Stop'
$evidencePath = Join-Path $PSScriptRoot '../evidence/network-handoff-implementation.json'
$evidence = Get-Content -LiteralPath $evidencePath -Raw -Encoding UTF8 | ConvertFrom-Json
$checked = 0
foreach ($record in @($evidence.source_snapshots) + @($evidence.reference_snapshots)) {
    $hash = (Get-FileHash -LiteralPath $record.path -Algorithm SHA256).Hash.ToLowerInvariant()
    if ($hash -ne $record.sha256) { throw "Snapshot changed: $($record.path)" }
    $checked++
}
if ($CheckTests) {
    foreach ($module in $evidence.test_results) {
        $files = @(Get-ChildItem -LiteralPath $module.directory -Filter 'TEST-*.xml')
        if ($files.Count -ne $module.suites) { throw "Suite count changed: $($module.directory)" }
        $total = 0
        foreach ($record in $module.reports) {
            $path = Join-Path $module.directory $record.name
            if ((Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant() -ne $record.sha256) {
                throw "Test XML changed (rerun needs a new evidence snapshot): $path"
            }
            $suite = ([xml](Get-Content -LiteralPath $path -Raw)).testsuite
            if ([int]$suite.failures -ne 0 -or [int]$suite.errors -ne 0 -or [int]$suite.skipped -ne 0) {
                throw "Unsuccessful test suite: $path"
            }
            $total += [int]$suite.tests
        }
        if ($total -ne $module.tests) { throw "Test count changed: $($module.directory)" }
    }
}
[pscustomobject]@{
    ok = $true
    sourceAndReferenceSnapshots = $checked
    testsChecked = [bool]$CheckTests
    limit = 'Integrity only; not firmware execution, Android networking, or vehicle acceptance'
} | ConvertTo-Json -Compress
