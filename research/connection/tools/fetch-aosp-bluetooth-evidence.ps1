param(
    [string]$Revision = '4b73ee6039271ffbf71ebdc8c109fc98eac8e137',
    [string[]]$SourcePaths = @(
        'framework/java/android/bluetooth/BluetoothAdapter.java',
        'framework/java/android/bluetooth/BluetoothSocket.java',
        'framework/java/android/bluetooth/BluetoothServerSocket.java',
        'framework/java/android/bluetooth/BluetoothDevice.java',
        'framework/java/android/bluetooth/BluetoothSocketSettings.java',
        'android/app/aidl/android/bluetooth/IBluetooth.aidl',
        'android/app/aidl/android/bluetooth/IBluetoothSocketManager.aidl',
        'android/app/src/com/android/bluetooth/btservice/BluetoothSocketManagerBinder.java',
        'android/app/src/com/android/bluetooth/sdp/SdpManager.java',
        'android/app/src/com/android/bluetooth/sdp/SdpManagerNativeInterface.java',
        'android/app/jni/com_android_bluetooth_btservice_AdapterService.cpp',
        'android/app/jni/com_android_bluetooth_sdp.cpp',
        'system/btif/src/btif_sock_rfc.cc',
        'system/btif/src/btif_sock_sdp.cc',
        'system/btif/src/btif_sdp_server.cc',
        'system/include/hardware/bt_sdp.h',
        'system/stack/sdp/sdp_db.cc',
        'system/bta/jv/bta_jv_act.cc',
        'system/bta/sys/bta_sys_main.cc',
        'NOTICE'
    )
)

# Research-only download cache. No phone/head-unit project or firmware is written.
# Existing source snapshots must match the upstream bytes; never overwrite them.
$ErrorActionPreference = 'Stop'
if ($Revision -notmatch '^[0-9a-f]{40}$') { throw 'Use an immutable full commit SHA.' }
$evidenceBase = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '../evidence/aosp-bluetooth'))
$snapshotRoot = Join-Path $evidenceBase $Revision
$snapshotPrefix = $snapshotRoot + [IO.Path]::DirectorySeparatorChar
foreach ($sourcePath in $SourcePaths) {
    if ($sourcePath -notmatch '^[a-zA-Z0-9_./-]+$') { throw "Invalid source path: $sourcePath" }
    $destination = [IO.Path]::GetFullPath((Join-Path $snapshotRoot $sourcePath))
    if (-not $destination.StartsWith($snapshotPrefix, [StringComparison]::OrdinalIgnoreCase)) {
        throw "Source path escapes evidence directory: $sourcePath"
    }
    $sourceUrl = "https://android.googlesource.com/platform/packages/modules/Bluetooth/+/$Revision/${sourcePath}?format=TEXT"
    $response = Invoke-WebRequest -UseBasicParsing -Uri $sourceUrl -TimeoutSec 30
    $payload = $response.Content
    if ($payload -is [byte[]]) { $payload = [Text.Encoding]::ASCII.GetString($payload) }
    $bytes = [Convert]::FromBase64String($payload.Trim())
    $hasher = [Security.Cryptography.SHA256]::Create()
    try { $digest = ([BitConverter]::ToString($hasher.ComputeHash($bytes))).Replace('-', '').ToLowerInvariant() }
    finally { $hasher.Dispose() }
    if (Test-Path -LiteralPath $destination) {
        $existing = (Get-FileHash -LiteralPath $destination -Algorithm SHA256).Hash.ToLowerInvariant()
        if ($existing -ne $digest) { throw "Existing snapshot differs; refusing overwrite: $destination" }
    } else {
        [IO.Directory]::CreateDirectory([IO.Path]::GetDirectoryName($destination)) | Out-Null
        [IO.File]::WriteAllBytes($destination, $bytes)
    }
    [pscustomobject]@{ source = $sourcePath; sha256 = $digest; bytes = $bytes.Length }
}
