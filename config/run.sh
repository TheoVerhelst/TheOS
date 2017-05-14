#!/bin/bash
OPTIND=1
getopt --test > /dev/null
if [[ $? -ne 4 ]]; then
    echo "I’m sorry, `getopt --test` failed in this environment."
    exit 1
fi

memory="4G"
debug=false
short_options="gm:"

# -temporarily store output to be able to check for errors
# -activate advanced mode getopt quoting e.g. via “--options”
# -pass arguments only via   -- "$@"   to separate them correctly
parsed_options=`getopt --options $short_options --name "$0" -- "$@"`

if [[ $? -ne 0 ]]; then
    # getopt has complained about wrong arguments to stdout
    exit 2
fi
# use eval with "$PARSED" to properly handle the quoting
eval set -- "$parsed_options"

# now enjoy the options in order and nicely split until we see --
while true; do
    case "$1" in
        -g)
			debug=true
			shift
			;;
        -m)
            memory="$2"
            shift 2
            ;;
        --)
            shift
            break
            ;;
        *)
            echo "Programming error"
            exit 3
            ;;
    esac
done

if [ "$debug" = true ]
then
	mate-terminal -t "TheOS on QEMU" -e "qemu-system-i386 -cdrom TheOS.iso -m $memory -S -s -d int -monitor stdio" &
    mate-terminal -t "GDB Debugger"  -e "gdb -ex 'target remote localhost:1234' -ex 'file TheOS.bin' -quiet"
else
	qemu-system-i386 -cdrom TheOS.iso -m $memory -monitor stdio
fi
