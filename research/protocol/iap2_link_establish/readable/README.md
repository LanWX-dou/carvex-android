# readable/ — 自动反编译产物（未复核）

## 目录结构

```
readable/
  ghidra/
    accessoryd/
      f_<addr>.ghidra.c   Ghidra 12.1.4 的原始 C 输出
      f_<addr>.json       该函数的元数据（地址、哈希链、状态）
  README.md
```

## 每个 C 文件的头部

```c
/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100008ae8
 * original code SHA256: ...
 * source SHA256: 2b0a2010...
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */
```

`f_<addr>.json` 中的 `status` 恒为 `DECOMPILED_UNREVIEWED`，并记录：

| 字段 | 含义 |
|---|---|
| `address` / `raw_sha256` | 与 `source/asm/accessoryd/index.json` 同一函数 |
| `loaded_code_sha256` | Ghidra 从加载镜像读到的字节哈希，必须等于 `raw_sha256` |
| `ghidra_name` / `signature` | Ghidra 从符号表得到的名字与签名 |
| `c_sha256` | C 文件内容哈希 |

`verify.py` 的 C3 检查会校验这条哈希链，确保"反编译的就是固件原字节"。

## 使用规则

1. **本目录只有参考价值**：任何结论必须回到 `source/asm/accessoryd/f_<addr>.s` 逐条核对。
2. 已知失真（参数个数、跳表、`unaff_` 变量、内联）见 `analysis/00-method-and-environment.md` §0.4。
3. 不要引用本目录的伪代码作为"规范"；`spec/` 中的所有条款都标注了 `A` 编号，指向 `analysis/` 里的汇编证据。

## 覆盖

114 个函数 = `source/asm/accessoryd/index.json` 的全部条目（114 / 8,706 个函数起点），
与 `analysis/13-function-inventory.md` 的分类一致。
