#!/usr/bin/python3
import subprocess
import argparse

terminal = "gnome-terminal"

parser = argparse.ArgumentParser(description="Run TheOS on an emulator.")
parser.add_argument("-g", "--debug", dest="debug", action="store_true",
                help="run in debug mode, and link with a GDB instance")
parser.add_argument("-m", "--memory", dest="memory", type=str, default="4G",
		help="quantity of memory to simulate in the emulator, 4G by default")

args = parser.parse_args()
debug = args.debug
memory = args.memory

if debug:
    subprocess.Popen([terminal, "-e", "qemu-system-i386 -cdrom TheOS.iso -m " + memory + " -S -s -d int -monitor stdio"])
    subprocess.Popen([terminal, "-e", "gdb -ex 'target remote localhost:1234' -ex 'file TheOS.bin' -quiet"])
else:
    subprocess.Popen(["qemu-system-i386", "-cdrom", "TheOS.iso", "-m", memory, "-monitor stdio"])
