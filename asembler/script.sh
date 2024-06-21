#!/bin/bash

number='6'

nasm -f elf test$number.asm
ld -m elf_i386 -s -o hello test$number.o

./hello
