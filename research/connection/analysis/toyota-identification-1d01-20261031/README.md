# Toyota `1D01` IdentificationInfo 静态核对

日期：2026-10-31

目标：

- Toyota CarPlay 配件库：
  `firmware/headunits/toyota/extract/vendor/carplay/libs/libiAP2.so`
- SHA-256：
  `F7F28E152D1791A38C91EE4495297C5EA078BD6F30386DCDE121413F21D9A29F`
- Ghidra 只读项目：
  `firmware/analysis/toyota-libiAP2-20261031/ToyotaLibIAP2`

## 1. 构造入口

- `CIpodIap2::startIdentification @0x12c298`
  - 只调用 `CIpodIap2::identificationInformation()`。
- `CIpodIap2::identificationInformation @0x12aa00`
  - 按固定顺序构造 `1D01`。
  - 0..5 使用配置中的字符串。
  - 6/7 使用配置中的消息声明集合。
  - 之后继续构造 Power 和 transport 字段。

这说明 Toyota 的 `1D01` 不是现场动态拼装的少量字段，而是由
配置文件解析出的配置对象生成。`carplayd.sh` 设置：

```text
IPOD_CARPLAY_CONFIG_PATH=/app/carplay/ipodconfig.xml
```

因此实际运行配置是部署目录中的 `ipodconfig.xml`；同目录的
`iap2_carplay_config.xml` 是另一份配置样本，不能把两者混为一谈。

## 2. 实际外层字段顺序

按 `identificationInformation` 中的 `createParamPacket` 调用顺序：

| 外层 ID | 内容 | 产生条件 / 配置来源 |
|---:|---|---|
| 0..5 | Name、ModelIdentifier、Manufacturer、SerialNumber、FirmwareVersion、HardwareVersion | 固定字符串 |
| 6 | 配件可发送消息集合 | `this+0x30` |
| 7 | 配件可接收消息集合 | `this+0x48` |
| 8 | `PowerProvidingCapability` | `identification+0xc8`，固定 U8 |
| 9 | `MaximumCurrentDrawnFromDevice` | `identification+0xcc`，固定 U16BE |
| 10 | ExternalAccessoryProtocol 组件 | `+0xd0` 非空 |
| 11 | AppMatchTeamID | `+0x100` 字符串长度非零 |
| 12 | CurrentLanguage | 固定字符串 |
| 13 | SupportedLanguage | 列表逐项输出 |
| 14 | SerialTransportComponent | `+0x158` 非零 |
| 15 | USBDeviceTransportComponent | `+0x188` 非零 |
| 16 | USBHostTransportComponent | `+0x1d0` 非零 |
| 17 | BluetoothTransportComponent | `+0x200` 非零 |
| 18 | USBDeviceHID 列表 | `+0x230` 非空 |
| 20 | VehicleInformationComponent | `+0x248` 非零 |
| 21 | VehicleStatusComponent | `+0x2a8` 非零 |
| 22 | LocationInformationComponent | `+0x2d8` 非零 |
| 23 | USBHostHID 列表 | `+0x308` 非空 |
| 24 | WirelessCarPlayTransportComponent | `+0x320` 非空 |
| 29 | BluetoothHIDComponent | `+0x338` 非零 |
| 30 | RouteGuidanceDisplayComponent | `+0x368` 非零 |
| 34 | ProductPlanUID | `this+0x52` 非零 |

对应部署 `ipodconfig.xml`，本次配置实际声明：

```text
10  ExternalAccessoryProtocol (native id 3)
14  SerialTransportComponent      未声明
15  USBDeviceTransportComponent   未声明
16  USBHostTransportComponent      id=3
17  BluetoothTransportComponent    id=7
18  USBDeviceHID                 未声明
20  VehicleInformationComponent    id=5
21  VehicleStatusComponent        未声明
22  LocationInformationComponent  未声明
23  USBHostHID                    未声明
24  WirelessCarPlayTransport      id=8
29  BluetoothHID                 未声明
30  RouteGuidanceDisplayComponent  id=9
34  ProductPlanUID               配置存在
```

这仍是静态配置推导，不证明运行时每个条件块都一定被提交；例如 HID 列表为空时
外层字段不会出现。

## 3. Toyota component 内容

按 `ipodconfig.xml` 的当前值，`identificationInformation` 会形成：

### USB Host，外层字段 16

配置块来自 `+0x1d0`：

```text
sub 0 = id              = 3
sub 1 = name            = HSAE-USBHost
sub 2 = active          = 1 (connection=1)
sub 3 = number          = 1 (number=1)
sub 4 = carplay flag    = void (carplay=1)
```

### Bluetooth，外层字段 17

配置块来自 `+0x200`：

```text
sub 0 = id              = 7
sub 1 = name            = HSAE-Bluetooth
sub 2 = active          = 1 (connection=1)
sub 3 = address         = CIpodVehicle::getBtAddress(), 6 bytes
```

### Wireless CarPlay，外层字段 24

配置块来自 `+0x320` 的列表项：

```text
sub 0 = id              = 8
sub 1 = name            = HSAE-Wireless
sub 2 = active          = 1 (connection=1)
sub 4 = carplay flag    = void (carplay=1)
```

### 其他已声明组件

- 字段 10：ExternalAccessoryProtocol 组件，`ipodconfig.xml` 中 id=1。
- 字段 20：VehicleInformationComponent，id=5。
- 字段 30：RouteGuidanceDisplayComponent，id=9。
- 字段 34：ProductPlanUID。

字段 18、21、22、23、29 的配置项在 `ipodconfig.xml` 中未声明或注释掉，
因此正常配置下不产生对应外层字段。

## 4. 24A446 对应回调

已从 24A446 `accessoryd` 原始函数确认：

- USB Host component callback：
  `cbIdentificationInfoUSBHostTransportComponentParams @0x10004f5bc`
- Bluetooth component callback：
  `cbIdentificationInfoBluetoothTransportComponentParams @0x10004f870`
- Wireless component callback：
  `cbIdentificationInfoWirelessCarPlayTransportComponentParams @0x10004fa38`
- `iap2_features_registerIdentificationParamHandlers @0x10006a3e4`
  按 feature 注册表安装这些 handler；注册表项只有 callback 返回成功后才进入
  required-success 集合。

局部 callback 条件与 Toyota 配置的对应关系：

| Toyota component | 24A446局部条件 | Toyota当前值 |
|---|---|---|
| USB Host | id/name/active/number/carplay 子字段 | `3/HSAE-USBHost/1/1/void` |
| Bluetooth | sub0/1必须成功，sub2 active，sub3地址低字节长度6 | `7/HSAE-Bluetooth/1`, 6字节地址 |
| Wireless | sub0/1必须成功，sub2 active，sub4/5为标志位 | `8/HSAE-Wireless/1/1` |

这些是静态预期通过，不是运行时抓包；BT 地址的实际六字节内容仍需运行时
或 `CIpodVehicle::getBtAddress` 的调用上下文确认。

## 5. Power 字段

`CIpodConfig::debugConfig @0x1176d8` 明确给出配置对象偏移：

| `1D01` 字段 | 配置偏移 | 含义 | 当前 XML |
|---:|---:|---|---|
| 8 | `+0xc8` (`puVar11 + 0x19`) | `PowerProvidingCapability` | `2` |
| 9 | `+0xcc` | `MaximumCurrentDrawnFromDevice` | `0` |

`identificationInformation` 对这两个字段的构造是：

```text
createParamPacket(this, 8, config + 0xc8, 1, ...)
createParamPacket(this, 9, config + 0xcc, 2, ...)
```

字段 9 在包内按大端 16 位写入。`ipodconfig.xml` 与备用的
`iap2_carplay_config.xml` 对这两个值目前相同；按部署配置推导，正常路径应为：

```text
field 8 = 02
field 9 = 00 00
```

这是配置和构造代码推导，不是现场抓包；最终线值仍取决于运行时实际加载的
`ipodconfig.xml` 是否与提取目录中的文件一致。

## 6. 与 24A446 接收条件的关系

24A446 的 Power 接收规则中：

- ID8 是 U8，值 1 的拒绝条件与 raw transport 0/8 有关。
- ID9 是 U16BE；已确认的 Bluetooth iAP 上下文
  `parent type2 / rawKind2` 的 provider 值为 100。
- Toyota 推导值 `8=2`、`9=0` 不会命中已确认的局部拒绝条件。
- 这不等于整条 `1D01` 必然接受，仍要经过 required-success、transport、
  feature、消息声明和平台授权。

## 7. CarVeX 当前差异

当前 CarVeX 的 `IapIdentifyInfo`：

- 已按 ordered TLV 解析 0..9、12、13、16、17、24、34。
- 8/9 现在进入 Power 校验；16 使用 USB Host component callback。
- 20（Vehicle Information）和 30（Route Guidance）仍是 deferred 字段。
- 生产接受路径现在要求 8/9 存在，并按 Bluetooth iAP 的 provider=100
  检查 ID9；Toyota 的 `8=2`、`9=0` 通过。

Power 校验已按 24A446 的局部分支接入，`IdentificationEndpointContext` 现在
携带 raw transport 和 provider 值：

- ID8：精确 U8 宽度和对应承载否决条件。
- ID9：精确 U16BE 宽度、provider 上限和失败拒绝形状。
- required-success 只记录回调成功，不把“字段出现”冒充成功。

## 8. Transport 配置

实际 `ipodconfig.xml` 还声明了：

```text
USBHostTransportComponent          id=3, carplay=1
BluetoothTransportComponent        id=7
WirelessCarPlayTransportComponent  id=8, carplay=1
```

这些配置项证明 Toyota 配置中存在三类 transport 组件，且
`identificationInformation` 已有对应的条件构造块。它们不证明本次运行时
每个条件块都会提交，也不证明当前连接实际启用的是哪一类；运行时列表内容和
可变的 BT 地址仍保持 `OPEN`。

## 9. 结论与 OPEN

已确认：

- Toyota `1D01` 的字段 8/9 构造位置和配置来源。
- 当前部署 XML 推导值为 `8=2`、`9=0`。
- CarVeX 已实现 Power 8/9 的 required-success 和 provider 校验。
- CarVeX 已解析 USB Host component 16、Bluetooth component 17 和
  Wireless component 24；Toyota 配置向量已加入测试。

仍为 OPEN：

- 运行时是否总是加载这份 XML，以及是否存在覆盖配置。
- 24A446 对 Toyota 实际 Bluetooth/AirPlay endpoint 上下文的完整映射。
- 字段 20/30 的完整消费者，以及 1D01 其余 component/feature 组合是否全部通过。
- 现场抓包或实车验证；当前只有静态二进制和配置证据。

## 10. 验证

```powershell
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest :app:compileXiaomiDebugKotlin --console=plain
```

- `protocol-carplay`：1032 项，127 套，0 失败、0 错误。
- `core`：81 项，13 套，0 失败、0 错误。
- `:app:compileXiaomiDebugKotlin`：成功。
- 未打包、未安装、未实车验证。
