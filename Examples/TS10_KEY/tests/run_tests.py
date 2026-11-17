"""使用真实 EmbedLib 状态机编译 ARM ELF，并在 Unicorn 中模拟 GPIO 输入。

依赖：Python、pyelftools、unicorn，以及已有的 Arm Compiler 6。
执行：python Examples/TS10_KEY/tests/run_tests.py
可通过 --compiler-dir 和 --embedlib 指定本机安装目录。
不读取、不修改原 TS10 工程；生成文件全部位于本目录的 build 中。
"""

from __future__ import annotations

import argparse
from pathlib import Path
import struct
import subprocess
import sys


def run(command: list[str]) -> None:
    result = subprocess.run(command, text=True, encoding="utf-8", errors="replace",
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    if result.returncode:
        print(result.stdout)
        raise RuntimeError(f"命令失败：{command[0]}")
    if result.stdout.strip():
        print(result.stdout.rstrip())


def main() -> int:
    sys.stdout.reconfigure(encoding="utf-8")
    sys.stderr.reconfigure(encoding="utf-8")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler-dir", type=Path,
                        default=Path("D:/MDK5.39/ARM/ARMCLANG/bin"))
    parser.add_argument("--embedlib", type=Path,
                        default=Path("D:/MDK5.39/Packs/Zjy/EmbedLib/1.0.0"))
    args = parser.parse_args()

    try:
        from elftools.elf.elffile import ELFFile
        from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_MODE_MCLASS, UC_HOOK_CODE
        from unicorn.arm_const import UC_ARM_REG_SP, UC_ARM_REG_LR
    except ImportError as error:
        raise RuntimeError("请先执行：python -m pip install pyelftools unicorn") from error

    tests = Path(__file__).resolve().parent
    example = tests.parent
    repository = example.parent.parent
    build = tests / "build"
    build.mkdir(exist_ok=True)
    compiler = args.compiler_dir / "armclang.exe"
    linker = args.compiler_dir / "armlink.exe"
    button_dir = args.embedlib / "Driver/EMB_BTN"
    sources = [example / "Device_KEY_TS10.c", example / "key_edal.c",
               tests / "test_key.c", button_dir / "emb_btn.c",
               args.embedlib / "Utils/EMB_FIFO/emb_fifo.c"]
    common = [str(compiler), "--target=arm-arm-none-eabi", "-mcpu=cortex-m3", "-mthumb",
              "-std=c99", "-O0", "-g", "-ffreestanding", "-fno-builtin",
              "-D__EMBEDDED_LIB_SUPPORTED__=1", "-D__EMB_CONFIG_LIB_SUPPORTED__=1",
              "-I", str(tests), "-I", str(example), "-I", str(button_dir),
              "-I", str(repository / "Device/Include"),
              "-I", str(args.embedlib)]
    objects = []
    for source in sources:
        output = build / f"{source.stem}.o"
        run(common + ["-c", str(source), "-o", str(output)])
        objects.append(str(output))
    elf_path = build / "test_key.axf"
    run([str(linker), "--no_scanlib", "--entry=test_main", "--ro_base=0x10000",
         "--rw_base=0x20000000", "--no_startup", "-o", str(elf_path)] + objects)

    emulator = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
    emulator.mem_map(0x00010000, 0x00100000)
    emulator.mem_map(0x20000000, 0x00200000)
    with elf_path.open("rb") as elf_file:
        elf = ELFFile(elf_file)
        # armlink 把 RW 初始值放在 RO 后的装载地址；按执行地址装载各节，
        # 相当于启动代码完成 scatter-load，避免依赖目标 C 运行库。
        for section in elf.iter_sections():
            if section["sh_flags"] & 2 and section["sh_type"] != "SHT_NOBITS":
                emulator.mem_write(section["sh_addr"], section.data())
        symbols = {symbol.name: symbol["st_value"]
                   for symbol in elf.get_section_by_name(".symtab").iter_symbols()}

    outcome = {"done": False, "failed": False}
    stop_addresses = {symbols["test_finish"] & ~1, symbols["test_failure"] & ~1}

    def hook_code(uc: Uc, address: int, size: int, user_data: object) -> None:
        del size, user_data
        if address in stop_addresses:
            outcome["done"] = address == (symbols["test_finish"] & ~1)
            outcome["failed"] = not outcome["done"]
            uc.emu_stop()

    def read_word(name: str) -> int:
        return struct.unpack("<I", emulator.mem_read(symbols[name], 4))[0]

    emulator.hook_add(UC_HOOK_CODE, hook_code)
    emulator.reg_write(UC_ARM_REG_SP, 0x201FF000)
    emulator.reg_write(UC_ARM_REG_LR, symbols["test_finish"] | 1)
    emulator.emu_start(symbols["test_main"] | 1, 0, timeout=30_000_000,
                       count=100_000_000)
    if outcome["failed"]:
        line = read_word("test_failed_line")
        source_line = (tests / "test_key.c").read_text(encoding="utf-8").splitlines()[line - 1]
        print(f"测试失败：阶段 {read_word('test_stage')}，test_key.c:{line}")
        print(source_line.strip())
        print(f"诊断：GPIO={read_word('test_gpio_levels'):#x}，已执行断言={read_word('test_checks')}")
        if "s_tEventQueue" in symbols:
            print("队列头 3 项：", bytes(emulator.mem_read(symbols["s_tEventQueue"], 36)).hex(" "))
        return 1
    if not outcome["done"]:
        print(f"仿真未完成：阶段 {read_word('test_stage')}，可能存在链表死循环或超时")
        return 1
    print(f"通过：{read_word('test_checks')} 项断言；真实 emb_btn/emb_fifo，5 组功能场景。")
    print("覆盖：5 键及业务键值映射、0x00 编码、单/双/长/连发、掩码与状态、")
    print("Control 参数与忙状态、逐键时序、零去抖、重复初始化/上下电、队列溢出。")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception as error:
        print(f"测试执行失败：{error}", file=sys.stderr)
        sys.exit(1)
