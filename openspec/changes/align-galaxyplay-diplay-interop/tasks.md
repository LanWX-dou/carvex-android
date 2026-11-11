## 1. Source and receiver verification

- [x] 1.1 Identify clean DiPlay source commit, GalaxyPlay APK and Android 17 scope.
- [x] 1.2 Record receiver source hashes and GalaxyPlay call-key DEX ownership/bytes.
- [x] 1.3 Add opt-in source-executing interoperability tooling and demonstrate pre-fix failures.

## 2. Navigation

- [x] 2.1 Honor minimum positive maneuver storage capacity with bounded U16 slots.
- [x] 2.2 Test actual receiver arrow/distance/reset, capacity wrap and single-slot behavior.
- [x] 2.3 Commit navigation changes independently with validation evidence.

## 3. Calls and music preservation

- [x] 3.1 Correct Hook Switch/Drop routing and keep unsupported Flash explicit.
- [x] 3.2 Test source-generated call subscriptions, call-state parser, telephony formats and music metadata.
- [x] 3.3 Commit call changes independently with validation evidence.

## 4. Validation and reporting

- [x] 4.1 Run affected module tests, all flavor compilation and Xiaomi Release lint.
- [x] 4.2 Publish compatibility matrix, reproduction commands and real vehicle acceptance checklist.
- [x] 4.3 Commit verification tooling and root research/submodule pointers; preserve unrelated changes.
- [ ] 4.4 Validate full call metadata, cellular downlink/uplink and instrument output with actual GalaxyPlay device evidence.

## 5. Device log 6 and factory Xiaomi channel

- [x] 5.1 Bind device log 6 to its tested build and record navigation/music chronology without private payloads.
- [x] 5.2 Verify original factory linkhmi APK identity and trace navigation versus music callbacks and native API ownership.
- [x] 5.3 Trace GalaxyPlay OEM navigation registration, model conversion and final output separately from its media bridge.
- [x] 5.4 Add source-to-snapshot diagnostics and focused regressions so the next device log identifies unchanged upstream data and lifecycle boundaries.
- [x] 5.5 Publish the verified end-to-end information flow, remaining receiver evidence and local validation results.

Section 5 evidence and remaining runtime boundaries:
[information flow](../../../research/connection/spec/cluster-navigation-flow-20261111.md),
[APK/log identities](../../../research/connection/evidence/cluster-navigation-flow-20261111.json),
[local validation](../../../research/connection/evidence/cluster-navigation-flow-validation-20261111.json).
GalaxyPlay's optional HUD music-text substitution is confirmed in the original
instructions; its tested setting, final map-service output and instrument rendering
remain OPEN. The factory JNI loader/library identity is verified; its complete
navigation output chain and external map service are not proven. Log 6 identifies
Release 20028 but has no commit hash; its source commit is only a history-derived candidate.

## 6. Confirmed maneuver display and incorrect route distance

- [x] 6.1 Record the user's observed 245 m maneuver display and -1 m route remainder versus approximately 19 km in Amap; trace the receiver's missing-value conversion.
- [x] 6.2 Obtain the supplied Amap producer/version evidence and trace its CarWith vehicle UI navigation IPC through HUD and DataBus; verify explicit null titles, the missing full-route field and the null getValue query.
- [ ] 6.3 Identify a real full-route distance source accessible from CarWith to the phone host in the actual vehicle UI session; the reviewed UCar hint/HUD/DataBus paths do not provide it.
- [x] 6.4 Publish existing evidenced U32 route distances as 5201 p7, clear stale receiver values on unknown input, and verify separation from maneuver distance using the production encoder and original receiver parser.
- [ ] 6.5 Connect the verified CarWith route-distance source through host/relay to the gated p7 encoder; preserve unknown values and avoid invented zero/total-distance fallbacks.
- [ ] 6.6 Validate route remainder against Amap on the vehicle, including updates, rerouting, completion and reconnect; keep the demonstrated maneuver display separate from full route acceptance.

The 2026-11-11 user feedback confirms the maneuver distance is displayed and
GalaxyPlay shows the CarWith vehicle Amap UI. Supplied Amap 17.02.0.2010 / 170200
and CarWith 4.0.14-20260801 now have 19 hash-bound method checks. The reviewed UCar
producer writes both titles as null; CarWith HUD has no typed route remainder,
DataBus copies empty titles, and UCar getValue returns null. The user supplied
local MiAuto commit 8ee36108ab74a58cbb0ef5c305e813a5f2fd8f41; its source callback
and stub signatures were compared with a separate original factory ICCOA SDK.
CarWith's sendNavigationInfoToCar/ControlChannel producer and receiver message 11
dispatch have identical nine-field protobuf schemas, without a typed full-route
remainder. The title fields stay empty on this Amap producer path. MiAuto's
runtime dex is absent and its current navigation flow has no instrument mapping.
Another accessible full-route source in the CarWith vehicle session remains open.
The numeric-core publisher now encodes an existing field-evidenced U32 route
remainder as 5201 p7 and clears stale remainder on unknown input. This independent
encoder change passed 1240 tests, including 14 original receiver-source contracts,
and Xiaomi Debug Kotlin compilation. The current CarWith source still supplies no
verified full-route distance, so GalaxyPlay can still convert its missing remainder
to -1. The user cannot connect the phone for runtime inspection now. No newly
attached device was read or APK packaged/installed.
See [encoder implementation](../../../android/docs/fixes/2026-11-11-navigation-route-distance.md)
and [local validation](../../../research/connection/evidence/navigation-route-distance-validation-20261111.json).
See [producer and CarWith outlet evidence](../../../research/connection/spec/carwith-amap-route-boundary-20261111.md).
See [MiAuto receiver to phone producer mapping](../../../research/connection/spec/miauto-carwith-navigation-20261111.md).
The additionally supplied CarWithEnhance repository was checked across three
public branch tips, 15 reachable commits and its empty public Issues list.
Its media page NavigationRouting and Xposed/DexKit hooks do not establish a
full-route source; see [reference-project search](../../../research/connection/spec/carwith-enhance-navigation-search-20261111.md).
