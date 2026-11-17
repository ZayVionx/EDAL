# TS10 按键改用固定 EDAL 接口的完整示例

本目录是独立的参考实现，没有修改原工程的 `key.c`、`key.h`，也没有修改公共 `Device/Include/Device_KEY.h` 或设备模板。

## 结构与固定头文件

公共 `Device_KEY.h` 的回调只有 `event`，`Control` 和 `GetStatus` 也没有 `key_id`。因此，在不改变该接口的条件下，本例使用一个设备实例对应一个物理按键；五个实例全部由同一个 `Device_KEY_TS10.c` 实现。不会为每个按键复制一份 `.c`，也不会在事件掩码的高位偷偷编码编号。

| 文件 | 内容 |
| --- | --- |
| `Device_KEY_TS10.h` | 板级实例声明、五元素设备表、1 ms 扫描入口 |
| `Device_KEY_TS10.c` | 共用驱动实现，导出 `Device_KEY0`～`Device_KEY4` |
| `key_edal.h` / `key_edal.c` | 应用层键号绑定、业务键值映射、事件队列、兼容字节接口 |
| `key_usage.c` | 初始化、周期扫描、事件读取、参数设置和状态查询示例 |
| `tests` | 使用真实 `emb_btn` 和 `emb_fifo` 的模拟电平验证 |

`Device_KEY_TS10.h` 是本项目的板级头文件，不是需要使用者修改的公共接口。新增按键、修改引脚或业务映射时，调整板级实现和应用配置即可。

## 与原代码对应的配置

| 物理编号 | 设备实例 | 引脚 | 应用业务键值 |
| --- | --- | --- | --- |
| `KEY_0` | `Device_KEY0` | PE0 | `BSP_KEY_VALUE_SET`，设置 |
| `KEY_1` | `Device_KEY1` | PE1 | `BSP_KEY_VALUE_BACK`，返回 |
| `KEY_2` | `Device_KEY2` | PE2 | `BSP_KEY_VALUE_MID`，中键 |
| `KEY_3` | `Device_KEY3` | PE3 | `BSP_KEY_VALUE_ADD`，加 |
| `KEY_4` | `Device_KEY4` | PE4 | `BSP_KEY_VALUE_SUB`，减 |

沿用原实现的 GPIOE、低电平有效、`GPIO_Mode_IPD`。这个上下拉配置照原文件保留，接入硬件时应按实际电路确认；本例没有根据“低电平有效”擅自改成上拉。

去抖 20 ms、双击窗口 150 ms、长按 500 ms、长按连发间隔 100 ms。默认只通知单击、双击、首次长按。`key_usage.c` 的初始化另外演示了为加减键启用连发；如果只调用 `bsp_key_init()`，不会额外开启连发。

业务键值由应用定义，本例枚举值是 1～5，不直接等同于原工程的 `LV_KEY_*` 数值。继续使用原 GUI 映射时，选兼容字节接口；使用结构化接口时，可按 `key_value` 自行映射为 LVGL 的设置、返回等键值。

## 如何纳入工程

这里只写示例，没有替你改变工程的文件列表、头文件或 SysTick。将来采用本例时：

1. 加入 `Device_KEY_TS10.c`、`key_edal.c`，以及原来已经使用的 `emb_btn.c`、`emb_fifo.c`。`key_usage.c` 可作为调用参考，或加入工程用于打印验证。
2. 应用包含 `key_edal.h`。加入本目录和公共 `Device/Include` 到头文件路径；原 `sys.h`、`beep.h`、芯片库及 EmbedLib 路径继续使用。
3. 将原 `key.c` 从该构建目标排除；不要同时包含旧 `key.h` 与本例 `key_edal.h`，两者定义了相同的 `KEY_ID`。原始文件本身无需删除或修改。
4. 本例独占 `emb_btn` 的全局注册表和队列。不要同时运行旧的 `bsp_key_init()` 实现，或让其它代码再次注册、消费同一引擎。
5. 保持 `EMB_CFG_BTN_SCAN_PERIOD_MS = 1`。在现有 SysTick 中用 `TS10_KEY_Scan1ms()` 替换原来的 `emb_btn_scan()` 调用，不能同时保留两次扫描，也不要额外定义第二个 `SysTick_Handler`。

现有 SysTick 中相关部分采用以下形式，其它计时和 LVGL 代码照原工程保留：

```c
#include "Device_KEY_TS10.h"

/* 放在现有 SysTick_Handler 中，每 1 ms 调用一次。 */
TS10_KEY_Scan1ms();
```

扫描入口保留真实 `emb_btn` 去抖及事件识别，在中断内分发回调；随后丢弃引擎队列中的重复副本。应用回调只写事件队列，蜂鸣和业务处理均在前台读取时进行。管理、配置、队列读取从同一个主循环或任务调用，不能在回调中重入，也不能从多个任务并发调用。

## 外部调用一：直接拿按键编号、键值和事件

初始化只需一次：

```c
#include "key_edal.h"

if (!bsp_key_init()) {
    /* 按项目自己的错误处理方式退出初始化。 */
    return;
}
```

前台主循环或按键任务读取：

```c
bsp_key_event_t key;

while (bsp_key_get_event(&key)) {
    /* key.key_id    ：KEY_0～KEY_4，物理编号。 */
    /* key.key_value ：SET/BACK/MID/ADD/SUB，应用业务键值。 */
    /* key.event     ：EDAL_KEY_EVENT_xxx，发生了什么。 */

    if (key.key_value == BSP_KEY_VALUE_SET &&
        key.event == EDAL_KEY_EVENT_CLICKED) {
        /* 处理设置键单击。 */
    }
}
```

按键 0 单击会取得 `KEY_0`、`BSP_KEY_VALUE_SET`、`EDAL_KEY_EVENT_CLICKED`。多个键同时操作会分别进入队列，不会被一个“当前按键”变量覆盖。队列满时丢弃新事件，可通过 `bsp_key_get_overflow_count()` 检查；应频繁消费。

## 外部调用二：保留原来的字节编码

```c
uint8_t code = bsp_key_get_value();

if (code != BSP_KEY_NONE) {
    KEY_ID key_id = (KEY_ID)(code & 0x0FU);
    uint8_t type = code >> 4U;
    /* type: 0=单击，1=长按或连发，2=双击。 */
    /* 用 key_id/type 继续查原 GUI 的键值映射表。 */
}
```

`0x00` 是按键 0 单击，`0x13` 是按键 3 长按或连发，`0x24` 是按键 4 双击。只有 `0xFF` 表示没有事件，不能写成 `if (code)`。

上述两种读取接口消费同一个队列，业务选择一种；不能两边同时读取并期望各得到完整事件。单击、双击、首次长按在取出事件时调用原来的 `BEEP_DIDIDIDI(100)`，连发不蜂鸣。

## 配置与当前状态

```c
/* 为指定键开启/关闭通知，保留其它通知位。 */
int32_t result = bsp_key_add_event(KEY_3, EDAL_KEY_EVENT_LONG_PRESS_REPEAT);
result = bsp_key_remove_event(KEY_ALL, EDAL_KEY_EVENT_DOUBLE_CLICK);

/* 独立配置某个键的长按阈值。操作时按键应空闲，并检查返回值。 */
result = Device_KEY0.Control(EDAL_KEY_SET_LONG_PRESS_TIME, 1000);
result = Device_KEY1.Control(EDAL_KEY_SET_LONG_PRESS_TIME, 2000);

/* 用数组选择一个实例，公共 API 不需要改签名。 */
EDAL_KEY_STATUS status = TS10_KEY_Devices[KEY_2]->GetStatus();
if (status.press) {
    /* 中键当前仍处于去抖后的按下状态。 */
}
```

初始化后，通知掩码统一由 `bsp_key_add_event/remove_event` 管理；本应用层保存当前掩码，不要绕过它直接调用 `Control(SET_EVENT_MASK, ...)`，否则缓存会不同步。仅使用裸设备实例、不使用本应用层时，则可以自行管理完整通知掩码。

| `Control` | 本例行为 |
| --- | --- |
| `SET_EVENT_MASK` | 只过滤回调；识别、状态更新继续；0 关闭通知 |
| `SET_DEBOUNCE_TIME` | 0～65535 ms；0 表示一次采样即确认 |
| `SET_DOUBLE_CLICK_TIME` | 1～65535 ms |
| `SET_LONG_PRESS_TIME` | 1～65535 ms |
| `SET_REPEAT_PERIOD` | 1～65535 ms |
| `CONTROL_WAKEUP` | 关闭返回成功，开启返回不支持 |

正在按下、去抖或等待双击完成时修改时间参数会返回 `EDAL_DEVICE_ERROR_BUSY`。非法参数返回 `EDAL_DEVICE_ERROR_PARAMETER`；未知命令返回 `EDAL_DEVICE_ERROR_UNSUPPORTED`；失败不改变原设置。参数值使用毫秒，本例严格匹配 1 ms 扫描。

`GetStatus()` 中 `press` 是当前稳定状态，其余六位是事件锁存位，读取后清除。通知掩码为零时状态仍更新。锁存位会合并同类重复事件，不能用于统计连发次数；需要顺序和次数时读事件队列。查询状态不会消费应用事件队列。

`Initialize` 注册回调、恢复默认配置，随后 `PowerControl(FULL)` 才开始识别。`OFF` 清除该实例运行状态并停止通知，再次 `FULL` 从空闲开始、保留配置。`Uninitialize` 解除逻辑使用，但保留引擎链表节点，之后可以重新初始化而不会重复注册。软件扫描方案不支持低功耗唤醒，`PowerControl(LOW)` 返回不支持。

## 与旧实现有一项行为区别

原 `emb_btn_remove_event(...DOUBLE_CLICK)` 不仅关闭通知，还会让释放时立即产生单击。固定 `Device_KEY.h` 已约定 `SET_EVENT_MASK` 只过滤通知，因此本例关闭双击通知后仍执行双击识别：单击仍等待窗口结束，双击会被识别后过滤，不会自动变成两次单击。保留默认通知时与原来的单击、双击、长按路径一致。若需要独立关闭双击识别，需要由公共接口维护者另行定义对应功能；使用者不应私改公共头文件或复用通知掩码表达另一种含义。

## 验证范围

三个示例 `.c` 均使用真实 TS10 工程头文件通过 ARM Compiler 5 和 Arm Compiler 6 的 C99 编译。模拟验证使用真实 `emb_btn.c` 和 `emb_fifo.c`，仅替换 GPIO、临界区和蜂鸣器，312 项断言通过。验证没有烧录硬件，物理 GPIO 电气配置仍需在目标板上确认。

```powershell
python Examples/TS10_KEY/tests/run_tests.py
```

测试依赖 Python 的 `pyelftools`、`unicorn`，以及本机现有 Arm Compiler 6 和 EmbedLib；路径可通过脚本参数覆盖。生成的 ARM 测试文件位于已忽略的 `tests/build` 中。
