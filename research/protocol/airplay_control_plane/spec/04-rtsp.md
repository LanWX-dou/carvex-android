# 04 · RTSP 消息

## 4.1 请求行

- R-4.1 请求行**必须**为 `方法 SP URL SP 版本 CRLF`，版本为 `RTSP/1.0`（`A01.2`，`INFERRED`）。
- R-4.2 URL 由消息类型对应的路径给出；`SETUP`/`RECORD` 等使用"包内 URL"，设备**必须**与 `SETUP` 时提交的 URL 保持一致（`A05.2`、`OPEN-AP-9`）。

## 4.2 头

- R-4.3 每个请求**必须**有 `CSeq`（`A01.5`）。
- R-4.4 有 body 时**必须**有 `Content-Length`（十进制）；**应**同时给 `Content-Type`（`A01.7`）。
- R-4.5 `DACP-ID`、`Active-Remote` **应**在已获得对端标识后携带；`User-Agent` **应**携带（`A01.4`、`A01.6`）。
- R-4.6 头名大小写与顺序是否被对端校验为 `OPEN-AP-7`；设备**应**按固件顺序输出（`CSeq` → `DACP-ID` → `Active-Remote` → `User-Agent` → 类型相关头）。
- R-4.7 头部区**不得**超过 8 KiB（`A01.3`）。

## 4.3 方法与类型

- R-4.8 方法集与 4CC 映射以 `analysis/05-rtsp-methods.md` 的表为准；表中"抽检"为空的行走 `OPEN-AP-8`，实现前**必须**逐条核对。**R-4.8 只覆盖方法/4CC 映射，不覆盖 `/info` 响应正文**；响应字段/schema 仍为 `OPEN-AP-45`。
- R-4.9 未知类型**必须**不发包并报错（`A05.1`）。

## 4.4 响应

- R-4.10 设备**必须**按 `CSeq` 匹配响应，并处理无 body / 有 body 两种形态（`A01.8`）。
- R-4.11 收到 `Transfer-Encoding: chunked` 时**必须**按 chunk 解析，不得把 chunk 长度行算作正文（`A01.8`）。
- R-4.12 状态行逐字段解析为 `OPEN-AP-5`；实现**应**至少区分 2xx/4xx/5xx。

## 4.5 示例（示意，不含密钥）

```text
GET /info RTSP/1.0
CSeq: 1
User-Agent: <client>/1.0
X-Apple-ProtocolVersion: <n>

```

正文为空；`Content-Length` 可省略（无 body）。实际数值为 `OPEN-AP-4`。
