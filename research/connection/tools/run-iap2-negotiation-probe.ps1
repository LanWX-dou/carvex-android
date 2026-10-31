param(
    [string]$PhoneRoot = 'D:/carvex-research/android',
    [string]$CacheRoot = 'C:/Users/iamr0s/.gradle/caches/modules-2/files-2.1'
)
$ErrorActionPreference = 'Stop'
# Remaining phone classes are dependencies from the existing module build.
# No Gradle, packaging, installation, Bluetooth or production source edits.
function Find-AuditJar([string]$group, [string]$artifact, [string]$version) {
    $folder = Join-Path $CacheRoot "$group/$artifact/$version"
    $found = @(Get-ChildItem -LiteralPath $folder -Recurse -Filter "$artifact-$version.jar")
    if ($found.Count -ne 1) { throw "Expected one runtime jar for $artifact $version" }
    return $found[0].FullName
}
$stdlib = Find-AuditJar 'org.jetbrains.kotlin' 'kotlin-stdlib' '2.4.21'
$compilerJars = @(
    (Find-AuditJar 'org.jetbrains.kotlin' 'kotlin-compiler-embeddable' '2.4.21'),
    $stdlib,
    (Find-AuditJar 'org.jetbrains.kotlin' 'kotlin-script-runtime' '2.4.21'),
    (Find-AuditJar 'org.jetbrains.kotlin' 'kotlin-reflect' '2.4.10'),
    (Find-AuditJar 'org.jetbrains.kotlinx' 'kotlinx-coroutines-core-jvm' '1.11.0'),
    (Find-AuditJar 'org.jetbrains' 'annotations' '23.0.0')
)
$classes = Join-Path $PhoneRoot 'protocol-carplay/build/intermediates/built_in_kotlinc/debug/compileDebugKotlin/classes'
$coreClasses = Join-Path $PhoneRoot 'core/build/intermediates/built_in_kotlinc/debug/compileDebugKotlin/classes'
$projectClasspath = "$classes;$coreClasses;$stdlib"
$probe = Join-Path $PSScriptRoot 'Iap2NegotiationProbe.kt'
$phone = Join-Path $PhoneRoot 'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt'
$phoneSources = @('IapLink.kt', 'IapFrameReader.kt', 'Wire.kt', 'IapStartupPolicy.kt') |
    ForEach-Object { Join-Path (Split-Path -Parent $phone) $_ }
$taskTemp = Join-Path ([IO.Path]::GetTempPath()) ('iap2-negotiation-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $taskTemp | Out-Null
$jar = Join-Path $taskTemp 'probe.jar'
$before = @($phoneSources) + @($engine, $probe) | ForEach-Object { Get-FileHash -LiteralPath $_ -Algorithm SHA256 }
& java -cp ($compilerJars -join ';') org.jetbrains.kotlin.cli.jvm.K2JVMCompiler -no-stdlib -no-reflect -jvm-target 17 "-Xfriend-paths=$classes" -classpath $projectClasspath -d $jar @phoneSources $engine $probe
if ($LASTEXITCODE -ne 0) { throw "Probe compilation failed: $LASTEXITCODE" }
& java -cp "$jar;$projectClasspath" Iap2NegotiationProbeKt
if ($LASTEXITCODE -ne 0) { throw "Probe execution failed: $LASTEXITCODE" }
foreach ($item in $before) {
    if ((Get-FileHash -LiteralPath $item.Path -Algorithm SHA256).Hash -ne $item.Hash) {
        throw "Source changed while probing: $($item.Path)"
    }
}
Write-Output ('SOURCE_SNAPSHOT ' + ($before | Select-Object Path, Hash | ConvertTo-Json -Compress))
Write-Output "Probe artifact retained at: $jar"
