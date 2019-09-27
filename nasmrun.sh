#!/bin/bash 
sudo ./nasm -f elf hello.asm
sudo gcc -m32 -o hello hello.o
sudo ./hello
