%define main_len 0
 global main
 section .data

section .text
 global main
main:
 PUSH EBP
 MOV EBP,ESP
 SUB ESP,main_len
 MOV EAX,0
 MOV ESP,EBP
 POP EBP
 RET 0
 MOV ESP,EBP
 POP EBP
 RET 0

