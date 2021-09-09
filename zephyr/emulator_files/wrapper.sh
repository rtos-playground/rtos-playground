#!/bin/sh
echo "Note: Exit the emulator with Ctrl-a, c"
exec qemu-system-arm -cpu cortex-m3 -machine lm3s6965evb -nographic -vga none -nic none -serial mon:stdio -kernel $1 2> /dev/null
