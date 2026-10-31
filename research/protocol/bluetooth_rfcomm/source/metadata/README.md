# source/metadata/ —— 导出信息（原始产物，不含分析结论）

本目录只放**从固件二进制直接读出的结构信息**，不含任何推断或注释性结论。

## 1. 文件

| 文件 | 内容 |
|---|---|
| `macho.json` | Mach-O 头、全部 load command 列表、段/节表、UUID、构建版本、函数起点数量 |

生成方式：用 Python `struct` 直接解析 Mach-O（不依赖任何三方库），脚本逻辑见下。

## 2. 关键事实（可直接引用）

| 项 | 值 |
|---|---|
| 文件大小 | 13,092,096 字节 |
| SHA256 | `cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1` |
| 格式 | thin ARM64 Mach-O（`MH_MAGIC_64`，`filetype=2` = `MH_EXECUTE`） |
| `LC_UUID` | `8e49197b-e6bc-3f3b-a8d3-df4bedd37f01` |
| 最低系统版本 | 27.0.0（`LC_BUILD_VERSION.platform=2` = iOS） |
| 函数起点数 | **37,368**（由 `LC_FUNCTION_STARTS` 的 ULEB128 delta 链解码） |
| 首个函数地址 | `0x100000f50` 附近（页内首项） |
| 末个函数地址 | 见 `macho.json` 的 `function_starts.last` |

## 3. 段表

| 段 | vmaddr | vmsize | filesize | 节数 |
|---|---|---|---|---|
| `__PAGEZERO` | `0x0` | 4 GiB | 0 | 0 |
| `__TEXT` | `0x100000000` | 12,173,312 | 12,173,312 | 25 |
| `__DATA_CONST` | `0x100b9c000` | 409,600 | 409,600 | 15 |
| `__DATA` | `0x100c00000` | 720,896 | 147,456 | 8 |
| `__LINKEDIT` | `0x100cb0000` | 376,832 | 361,728 | 0 |

**重要**：`__DATA` 的 `vmsize`（720,896）远大于 `filesize`（147,456），说明该段尾部包含**零填充区（BSS 语义）**。因此：

- 地址映射 `文件偏移 = 地址 - 0x100000000` 只对 `[0x100000000, 0x100c00000 + 147456)` 成立；
- 位于零填充区的全局变量（例如 `analysis/05` 引用的 `0x100cadd68`）**在文件里没有字节**，其初值恒为 0，无法从文件读取；
- `verify.py` 因此只校验地址是否落在镜像窗口内，而不要求落在文件范围内。

## 4. 已确认的 load command

`LC_SEGMENT_64`、`LC_UUID`、`LC_BUILD_VERSION`、`LC_FUNCTION_STARTS`、`LC_DYLD_CHAINED_FIXUPS`、`LC_MAIN`、`LC_SYMTAB`、`LC_DYSYMTAB`、`LC_CODE_SIGNATURE`、`LC_ENCRYPTION_INFO_64`、`LC_SOURCE_VERSION` 等（完整列表见 `macho.json` 的 `macho.load_commands`）。

- **存在 `LC_DYLD_CHAINED_FIXUPS`**：指针为 chained fixup 编码，不能当作裸地址读取。这是本次通过反编译而非静态读指针来获取间接调用的原因之一。
- **存在 `LC_ENCRYPTION_INFO_64`**：该二进制为加密镜像的一部分；本次使用的字节序列可以正常反汇编（`__TEXT` 未加密），但 `__DATA` 中的指针/字符串可能需要运行时才能完全还原。

## 5. 复现脚本

```python
import struct
d = open('source/firmware/bluetoothd','rb').read()
magic, cputype, cpusub, filetype, ncmds, sizeofcmds, flags, res = \
    struct.unpack_from('<IiiIIIII', d, 0)
assert magic == 0xfeedfacf
off = 32
for _ in range(ncmds):
    cmd, size = struct.unpack_from('<II', d, off)
    if cmd == 0x19:      # LC_SEGMENT_64
        ...
    elif cmd == 0x26:    # LC_FUNCTION_STARTS
        dataoff, datasize = struct.unpack_from('<II', d, off + 8)
    off += size
```

函数起点解码：从 `dataoff` 起读 ULEB128，累加得到相对偏移，`地址 = 0x100000000 + 累计值`，遇到 0 结束。

## 6. 与文档的关系

- 本目录**不产生**任何协议结论。
- `analysis/00` 引用本目录的段表解释"为什么某些地址无法从文件读取"。
- `manifest.json` 记录了本目录文件的哈希，`verify.py` 校验固件哈希与函数起点的可复算性。
