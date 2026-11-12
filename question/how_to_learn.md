# EDAL 架构学习计划

参考仓库：

- `g:\Architecture\rt-thread`
- `g:\Architecture\nuttx`
- `g:\Architecture\CMSIS_5\CMSIS`

---

## 总体顺序与理由

**CMSIS-Driver → RT-Thread 设备模型 → NuttX 上下半部**

- CMSIS-Driver 最短（全部接口头文件加起来不到 3000 行）、最纯（不依赖任何 OS），它就是"一个嵌入式外设抽象层"的教科书答案，和 EDAL 的目标**完全同构**。
- RT-Thread 提供的是"设备类 + 实例 + 注册表"的组织方式。
- NuttX 最重，但它的"上层接口 / 下层硬件操作 / 中间胶水"三层分离以及事件与 poll 机制，是 KEY/TOUCH 这类会产生异步事件的设备的正确解法。

预计 12~14 个工作日（每天 3 小时以上）。

---

## 阶段 0：先写 EDAL 的设计问题清单（半天）

在 `docs/design-questions.md` 里写下这 9 个问题，每个阶段读完后回来作答：

1. 一个外设类型（如 Beep）如何支持多个不同实现（PWM 蜂鸣器 / GPIO 蜂鸣器 / I2C 音频芯片）？
2. 同一个实现如何支持多个实例（两路 UART、两个按键组）？
3. `context` 由谁分配、谁释放、放在 ROM 还是 RAM？
4. ops 表应该放在实例里（值）还是实例指向它（指针）？
5. 设备状态机要有几个状态？`Init` 失败能不能重试？
6. 上层如何"找到"设备：全局数组下标？名字查找？还是编译期静态绑定？
7. KEY/TOUCH 这类事件源，是轮询返回，还是注册回调，还是投递消息队列？
8. 能力查询（GetCapabilities）有必要吗？还是靠返回值报 NOT_SUPPORTED 就够？
9. 纯裸机无 OS 约束下，哪些机制（互斥、队列、超时）能用、哪些必须留钩子？

这 9 个问题的答案就是 EDAL 的"接口契约"。没有它们，读源码会变成模仿。

---

## 阶段 1：CMSIS-Driver —— 接口形状（2.5 天）

按这个顺序读，每读完一个文件用 200 字回答对应问题。

### Day 1 上午

1. `CMSIS\Driver\Include\Driver_Common.h`（69 行，20 分钟）
   先读这个。重点：`ARM_DRIVER_VERSION`（api 版本和 drv 版本**两个**字段，为什么需要两个）、`ARM_DRIVER_OK/ERROR/BUSY`、`ARM_POWER_STATE`、`ARM_DRIVER_STATUS`、`ARM_SIGNAL`。→ 对照 `EDAL_Status_t`，想想少了 BUSY 和 TIMEOUT 会怎样。
2. `CMSIS\Driver\Include\Driver_USART.h`（347 行，2 小时）
   这是全套里最值得精读的一个。按顺序看：`ARM_USART_CAPABILITIES` → `ARM_USART_STATUS` → `ARM_USART_EVENT` 枚举 → `ARM_USART_SignalEvent_t` → `struct ARM_DRIVER_USART` 的成员顺序。**注意成员的排列顺序是有讲究的**：GetVersion/GetCapabilities 在最前（不需要初始化就能调），Initialize 之后才是 PowerControl，业务 API（Send/Receive/Transfer/GetTxCount/GetRxCount/Control）在最后。
3. `CMSIS\Driver\Include\Driver_I2C.h`（223 行，1 小时）
   对照 USART 看总线类接口的组织，注意 `ARM_I2C_BUS_SPEED_*` 这类"常量定义在头文件、驱动内部解释"的做法。

### Day 1 下午

4. `CMSIS\Driver\DriverTemplates\Driver_USART.c`（153 行，1.5 小时）
   读模板骨架。重点不是它留的 TODO，而是**每个函数体是怎么"什么都不做但结构完整"的**——这就是"接口先行、实现滞后"的写法。后面每个 EDAL 驱动都应该能从这个模板复制出结构。
5. `CMSIS\Driver\Include\Driver_Common.h` 回看第 3 遍，专门看 `ARM_DRIVER_VERSION ARM_Driver_USART_GetVersion(void)` 里宏是怎么生成的。
6. `CMSIS\Documentation\index.html` 里 Driver 章节（浏览器打开，只看 API 约定和 Driver Implementation Guidelines 部分，1 小时）

### Day 2 上午：交叉对照

7. 拿 `struct ARM_DRIVER_USART` 和 `Beep_DrvType_t` 逐成员对比，写一页纸：
   - 为什么 CMSIS 没有 `DeInit` 而有 `Uninitialize` + `PowerControl(ARM_POWER_OFF)`
   - 为什么事件是 `SignalEvent` 回调而不是 `GetEvent`
   - 为什么 `GetCapabilities` 返回位掩码而不是一堆 `IsXxxSupported()`
8. 顺带扫一眼 `Driver_SPI.h`、`Driver_Flash.h` 的 ops 表，确认 CMSIS 的形状是**统一的**（每个外设都是同样的 12~14 个成员序列）。

**产出**：`docs/01-cmsis-driver-notes.md`，含一张你画的 `ARM_DRIVER_USART` 生命周期图（Uninitialized → Initialized → Powered），以及回答阶段 0 的问题 4、6、8。

**不要做的**：不要照抄 `SignalEvent`。CMSIS 的 SignalEvent 是为"中断里直接回调上层"设计的，裸机上要考虑回调里能不能做重活。

---

## 阶段 2：RT-Thread 设备模型 —— 类 / 实例 / 注册表（4 天）

RT-Thread 有 `RT_USING_DEVICE_OPS` 和 `RT_USING_DM` 两套路径。**只读传统路径**（`RT_USING_DEVICE_OPS` 关闭时），`dm.c`/`bus.c`/`ofw.c` 那一套是 Linux 设备树移植，跟裸机 EDAL 无关，跳过。

### Day 3 上午：类型系统

1. `include\rtdef.h` **L1254-1290**（15 分钟）
   `enum rt_device_class_type` — 这是 RT-Thread 的"设备类"枚举，Char/Block/MTD/Graphic/I2CBUS/SPIBUS…。**关键认识：类不是靠 C 语言类型实现的，是靠一个 enum 字段 + 约定实现的。**
2. 同文件 **L1290-1330**（15 分钟）
   `RT_DEVICE_FLAG_*`（ACTIVATED/SUSPENDED/STREAM/INT_RX/DMA_RX…）和 `RT_DEVICE_CTRL_*`（控制命令编号段）以及 `RT_DEVICE_CTRL_BASE(Type)` 宏。← 这个宏很值得抄：**用 class 编号推导控制命令基址，避免不同设备的 ioctl 命令冲突**。
3. 同文件 **L1334-1360**（`#ifdef RT_USING_DEVICE_OPS` 的 `struct rt_device_ops`）+ **L1378-1440**（`struct rt_device`）
   看 `struct rt_device` 前 30 个字段：`parent`（继承 `rt_object`，带名字）、`type`、`flag`、`open_flag`、`ref_count`、`rx_indicate`、`tx_complete`、`user_data`。**注意 `user_data`** —— 这就是 `context` 在 RT-Thread 里的等价物，但它挂在内核对象上而不是 ops 里。

### Day 3 下午

4. `components\drivers\core\device.c`（483 行，3 小时，全读）
   这是阶段 2 的核心。`rt_device_register` / `rt_device_find` / `rt_device_init` / `rt_device_open` / `rt_device_read` / `rt_device_write` / `rt_device_control` / `rt_device_set_rx_indicate`。
   读的时候全程问一个问题：**"这些函数只是转发到 dev->ops->xxx，为什么还要包一层？"** 答案在 `ref_count`（多任务同时 open）、`open_flag`（防止重复 open）、`ACTIVATED` 标志（延迟初始化）。这层"薄转发"就是 EDAL 上层函数应该长成的样子——现在的 `Beep_Play` 已经在做类似的事了，但缺 ref_count 和 open 语义。

### Day 4 上午

5. `components\drivers\core\driver.c`（53 行，20 分钟）+ `core\bus.c` L1-120（1 小时）
   只看 `struct rt_driver` 和 bus 的 match 逻辑。**如果时间紧就跳过整套 DM**，只需要知道：RT-Thread 区分了"设备（实例）"和"驱动（提供 ops 的一方）"，两者通过 match 函数绑定。这个概念和阶段 1 的 `ARM_DRIVER_USART` 是同一件事，只是多了一层运行期匹配。
6. `components\drivers\input\input.c`（405 行，2 小时）
   直接读。这是 RT-Thread 的输入子系统：`struct rt_input_device` + `struct rt_input_ops`（只有 `readpoint` 和 `control`）+ 事件队列 `rt_input_event`。**这是 KEY/TOUCH 最该参考的东西**：一个 key 驱动只需要实现"读原始点"，框架负责去抖、产生 event、投递到设备节点。
7. `components\drivers\input\input_touch.c`（453 行）+ `input_uapi.c`（399 行，可选）
   对照看 touch 是怎么复用 input 框架的。

### Day 4 下午：串口，泛化的范本

8. `components\drivers\include\drivers\dev_serial.h`（322 行，1.5 小时，全读）
   重点两条：`struct rt_serial_device` 的第一个成员是 `struct rt_device parent`（**C 语言实现继承**），`struct rt_uart_ops` 单独定义并放在文件后面。**看清楚"类 ops"和"实例结构"的层次关系** —— 这一条直接回答阶段 0 的问题 4。
9. `components\drivers\serial\dev_serial.c`（1681 行）—— 跳读，只读三处：
   - `L1477 rt_hw_serial_register`（注册函数，看它怎么填 parent 的 type/flag/ops）
   - `L1522 rt_hw_serial_isr`（中断服务入口，看 event 枚举 `RT_SERIAL_EVENT_RX_IND` 怎么分派）
   - `L534 _serial_fifo_calc_recved_len` 附近那组函数（看 FIFO 逻辑放在框架里之后，驱动要做的事就只剩"搬数据"了）

### Day 5 上午

10. `components\drivers\include\drivers\dev_serial_v2.h`（427 行）与 v1 对比
    v2 最大的变化：FIFO 完全收进框架，驱动的 ops 从"你给缓冲区"变成"你给硬件寄存器的读写"。**这是"框架该承担多少"这个问题的两个不同答案**，要为自己的 EDAL 选一个。
11. `components\drivers\include\drivers\dev_touch.h`（245 行）+ `touch\dev_touch.c`（253 行）
    很短，全读。`struct rt_touch_ops` 只有 `touch_readpoint` 和 `touch_control` 两个函数 —— 看它多克制。

### Day 5 下午：总结

写 `docs/02-rtthread-notes.md`，必须包含：

- 一张表：`rt_object / rt_device / rt_serial_device / rt_uart_ops` 四者的包含关系
- `Beep_Device_t` / `Key_Device_t` 对应到哪一层
- 回答阶段 0 的问题 3、5、6、7

---

## 阶段 3：NuttX —— 上下半部与事件机制（4 天）

NuttX 是基于 VFS 的，**不需要 FS**，所以只读三个切面。三天的核心是第 6、7、9 项。

### Day 6：VFS 形状与串口上下半部

1. `include\nuttx\fs\fs.h` **L223-260**（`struct file_operations`，20 分钟）
   现在是 open/close/read/write/seek/ioctl/mmap/truncate/poll/readv/writev/unlink。注意 `poll`。**NuttX 用"文件"当统一接口，RT-Thread 用"设备类"当统一接口** —— 两种抽象哲学，要判断裸机下哪个更轻。
2. `include\nuttx\serial\serial.h` 中的 `struct uart_dev_s` 和 `struct uart_ops_s`（1 小时）
   `uart_dev_s` 里嵌了 `struct uart_ops_s *ops`（下层：setup/shutdown/attach/detach/send/receive/ioctl/rxint/rxavailable/txint/txready），还有 RX/TX 环形缓冲区指针、信号量。**这就是"下层 ops"的样板**。
3. `drivers\serial\serial.c` **L100-200**（`g_serialops` 和 `uart_open/close/readv/writev/ioctl/poll` 的声明，30 分钟）
   看清：`g_serialops` 里的 `read`/`write` 是 `NULL`，实际实现挂在 `readv`/`writev` 上（新版 NuttX 把 read/write 迁移到 readv/writev）。这是个容易看错的地方。
4. 同文件 **`uart_open`**（用 grep 定位）、**`uart_ioctl`**、**`uart_readv`**（3 小时，跳读）
   重点看 `uart_open` 里怎么调 `ops->setup` 和 `ops->attach`（**上层函数是驱动生命周期的唯一入口**），以及 `uart_ioctl` 里 `TCGETS/TCSETS` 的分派方式。
5. 同文件 **L2580 附近 `uart_register`**（30 分钟）
   `register_driver(path, &g_serialops, 0600, dev)` —— 把 ops 表和历史上下文的 `dev` 指针一起挂到 inode 上。

### Day 7：输入类与触摸芯片

6. `drivers\input\button_upper.c`（822 行，3 小时）
   `L785 btn_register` → `L544 btn_ioctl` → `L675 btn_poll` → `L324 btn_open`。
   **重点**：按键状态由"下半部"通过 `btn_samples` 之类的接口塞进来，上半部只负责 `BTNIOC_REGISTER`/`BTNIOC_GETSTATE` 和 poll 唤醒。这和 KEY 的 `AddEvent`/`RemoveEvent` 设计意图一致，但 NuttX 用 ioctl + poll 实现，不用 `AddEvent` 注册回调。
7. `drivers\input\ft5x06.c`（1.5 小时）
   一个真实 I2C 触摸芯片驱动。看它：定义 `struct ft5x06_dev_s`（含 i2c_master_s 指针和 config）→ 实现下半部的 `touchsample()` → 末尾 `register_driver("/dev/input0", ...)`。**这就是 `drivers/TOUCH/touch.c` 未来该长的样子。**
8. 顺带扫 `drivers\input\kmatrix.c` 与 `button_upper.c` 的配合（30 分钟）

### Day 8：LCD —— 最值得抄的骨架

9. `drivers\lcd\skeleton.c`（410 行，3 小时，**全读，这是阶段 3 的核心**）
   这就是一个"新 LCD 驱动从这开始"的模板。看：文件头的 `CONFIG_LCD_SKELDEBUG` 分组、`g_videoinfo`/`g_planeinfo` 静态表、每个函数（`skel_putrun`/`skel_getrun`/`skel_getplaneinfo`/`skel_getvideoinfo`/`skel_getpower`/`skel_setpower`/`skel_setcontrast`/`skel_getcontrast`）的空实现，最后 `up_oledinitialize(spi)` 返回 `struct lcd_dev_s *`。
   **注意 `up_oledinitialize` 的命名和返回类型**：init 函数返回的是"设备接口指针"，而不是错误码。这跟 EDAL 现在 `edal_board_devices_init()` 返回 `EDAL_DeviceState_t` 是不同的思路，值得权衡。
10. `drivers\lcd\lcd_dev.c`（463 行，1.5 小时）
    看 NuttX 怎么把这个 `lcd_dev_s` 包装成文件设备。
11. `include\nuttx\lcd\lcd.h` 的 `struct lcd_dev_s`（L196 起）和 `struct lcd_planeinfo_s`（1 小时）
    对照 `lcd_dev_s` 和 `lcd_planeinfo_s`：**为什么一个设备有两个结构体？** 因为 `lcd_dev_s` 是"显示控制器"，`lcd_planeinfo_s` 是"平面（帧缓冲）"——一个控制器可以有多个平面。这是"复合设备"的抽象方法，EDAL 的 LCD 驱动如果将来要支持"画点/画线/刷新区域"多级接口会遇到同样问题。

### Day 9：初始化组织 + 总结

12. `drivers\drivers_initialize.c`（1 小时）
    看 NuttX 怎么组织所有驱动初始化顺序（分 `drivers_initialize()` 和 `board_initialize()` 两级）。**这条直接对应 [edal.c:44](../edal.c#L44) 的空函数。**
13. 可选：`drivers\lcd\ssd1306_base.c` 前 200 行 + `ssd1306_i2c.c`（145 行），看 OLED 是怎么把 `lcd_dev_s` 和 I2C 结合的 —— 这个和 EDAL 的 `edal_lcd.h` 关系最紧。

写 `docs/03-nuttx-notes.md`，回答阶段 0 的问题 1、2、7、9。

---

## 阶段 4：三份笔记合成一份架构决策记录（2 天）

新建 `docs/architecture.md`，按下面章节写。**这一份文档才是这轮学习的真正产出**，不是笔记。

1. **分层图**：画出你的 4 层 —— `board（实例与绑定）` / `edal 核心（转发+状态+校验）` / `class ops（类接口表）` / `driver（硬件实现）`。对照 RT-Thread 的 `rt_device` / `rt_uart_ops` / `uart_dev`。
2. **ops 签名定稿**：统一加 `void *context`（解决 Beep/Key 不一致），并且定义 `GetCapabilities()` 还是用返回值 + `NOT_SUPPORTED`。
3. **实例存放策略**：ops 表 `static const` 在 driver 层，实例 `static` 在 board 层，实例里 `const Xxx_DrvType_t *drv`（指针，不是值）。给出 [edal_key.h:26](../device/include/edal_key.h#L26) 和 [edal_key.h:52](../device/include/edal_key.h#L52) 的具体修改。
4. **注册表**：决定用 `edal_board_devices_init()` 里逐个静态绑定，还是 `edal_xxx_register(device)` 运行期注册（RT-Thread 的 `rt_device_register`）。裸机建议**静态绑定 + 一张 const 表**，不需要 `rt_device_find` 的字符串查找。
5. **事件机制**：KEY/TOUCH 选哪一种 —— 轮询 `GetValue`（现在）、回调注册（CMSIS `SignalEvent`）、内部队列 + `Read`（RT-Thread input）、poll（NuttX）。裸机没有 poll 的基础设施，建议"回调 + 可选的内部 FIFO"，但**回调必须能在中断上下文中安全调用**，这一点要在文档里写明约束。
6. **状态机**：`UNINITIALIZED / READY / SUSPENDED`，加不加 `BUSY`？`Init` 失败后 `state` 保持 UNINITIALIZED 以便重试（现在 `Beep_Init` 是对的，保持）。
7. **控制命令编号**：采用 `RT_DEVICE_CTRL_BASE` 的做法，给每个 class 分配 0x100 段。
8. **明确不做的**：不引入 `rt_object` 容器、不做设备树/OFW、不做 Kconfig、不做 ref_count（除非多任务）。把这些写成"考虑过并拒绝"的一节，避免以后反复摇摆。

---

## 阶段 5：按文档重构（3 天，只重构 BEEP 和 KEY 两个）

**不要一次重构四个设备**。选一个最简单的（BEEP）和最有事件的（KEY）作为样板，验证架构，跑通了再复制到 LCD/TOUCH/IIC。

按这个顺序：

1. 改 `device/edal_types.h`：加 `EDAL_Status_t` 的 `BUSY`/`TIMEOUT`，加 `EDAL_DeviceState_t` 的 `SUSPENDED`，加 `EDAL_CTRL_BASE(class)` 宏。
2. 改 `device/include/edal_beep.h`：`Beep_DrvType_t` 保持（它已经基本正确），只补 `GetCapabilities`（可选）和版本号。
3. 改 `device/include/edal_key.h`：`Key_DrvType_t` 全部函数加 `void *context`，`Key_Device_t.drv` 改成 `const Key_DrvType_t *drv`，与 Beep 对齐。
4. 改 `drivers/BEEP/beep.c`：把 `beep_dev[]` 移走，只留 `beep0_ops`（`static const Beep_DrvType_t`），并 `#include` 后 `extern` 暴露。
5. 新建 `board/board_beep.c`（或直接在 `edal.c`）：定义 `static Beep_Device_t beep0 = { .drv = &beep0_ops, .context = &beep0_hw_cfg, .state = EDAL_DEVICE_UNINITIALIZED };`，在 `edal_board_devices_init()` 里 `Beep_Init(&beep0)`。
6. 同样套路做 KEY。
7. 如果板子在手，用 Mklink 烧录跑一下；不在就把 `Init` 打桩、用条件编译的 host 编译验证链接无错（这套库应该能做到 `arm-none-eabi-gcc -c` + 主机 gcc 编译通过）。

---

## 每天怎么读（比读什么更重要）

对每个核心文件用三遍法，**不要第一遍就逐行读**：

- **第一遍（20%）**：只看文件里的结构体定义和函数声明，画出"谁包含谁"。
- **第二遍（50%）**：`grep` 定位一个具体符号（例如 `rt_device_register`），从头到尾追一条完整调用链：上层调用 → 参数校验 → ops 转发 → 硬件操作 → 返回值。只追这一条。
- **第三遍（30%）**：合上文件，用自己的话写 200 字回答一个阶段 0 的问题。写不出来就是没读懂，回去重读第二遍。

推荐每阶段配一个 `docs/answers-Qn.md`，九个问题每个阶段答一遍，三遍答案如果有变化，说明你的理解在收敛——最后那份就是阶段 4 的输入。
