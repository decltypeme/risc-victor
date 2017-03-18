#! /bin/sh
# change -o0 to -o2 for better compiler optimization
riscv32-unknown-elf-gcc -Wall -O0 crt0.s $1 -nostdlib -T link.ld -o $1.elf
riscv32-unknown-elf-objcopy -O verilog $1.elf $1.v
riscv32-unknown-elf-objdump -d $1.elf > $2
