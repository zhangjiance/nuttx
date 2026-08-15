#!/bin/bash
# Flash NuttX to the hpm5300evk via Blackmagic Probe (GDB interface).
#
# Usage: ./flash_bmp.sh [gdb-port]

GDB=${GDB:-gdb-multiarch}
GDBPORT=${1:-/dev/ttyACM0}

if [ ! -e nuttx ]; then
    echo "error: nuttx not found, build first" >&2
    exit 1
fi

$GDB nuttx \
    -ex "set confirm off" \
    -ex "set pagination off" \
    -ex "tar ext $GDBPORT" \
    -ex "mon jtag_scan" \
    -ex "attach 1" \
    -ex "load" \
    -ex "q"

echo "flashed"
