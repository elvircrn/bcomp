#!/bin/bash 
sudo ./nasm -f elf hello.asm
sudo gcc -o hello hello.o
sudo ./hello
