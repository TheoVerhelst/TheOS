#!/usr/bin/python3
import subprocess
import argparse

terminal = "gnome-terminal"

parser = argparse.ArgumentParser(description="Run TheOS on an emulator.")
parser.add_argument(
    "-g", "--debug", dest="debug", action="store_true",
    help="run in debug mode, and link with a GDB instance")
parser.add_argument(
    "-m", "--memory", dest="memory", type=str, default="4G",
    help="quantity of memory to simulate in the emulator, 4G by default")
parser.add_argument(
    "-c", "--no-continue", dest="no_continue", action="store_true",
    help="if debug mode is used, do not automatically continue the debugger at"
    "startup")

args = parser.parse_args()

if args.debug:
    continue_arg = "-ex 'c'" if not args.no_continue else ""

    commands = [[
        terminal, "-e", "qemu-system-i386 -cdrom TheOS.iso -m " + args.memory +
        " -S -s -d int -monitor stdio"
    ], [
        terminal, "-e",
        "gdb -ex 'target remote localhost:1234' -ex 'file TheOS.bin' "
        + continue_arg + " -quiet"
    ]]
else:
    commands = [[
        "qemu-system-i386", "-cdrom", "TheOS.iso", "-m", args.memory,
        "-monitor", "stdio"
    ]]

[process.wait() for process in
    [subprocess.Popen(commnand) for commnand in commands]]
print()
