%define id_len 4
%define main_len 0
 extern printf
 global main
 section .data
LIT_0: db "%d", 10, "", 0

section .text
 global id
id:
 PUSH EBP
 MOV EBP,ESP
 SUB ESP,id_len
 MOV EAX, [EBP + 8]
 MOV ESP,EBP
 POP EBP
 RET 0
 MOV ESP,EBP
 POP EBP
 RET 0
 global main
main:
 PUSH EBP
 MOV EBP,ESP
 SUB ESP,main_len
 PUSH 2
 CALL id
 ADD ESP,4
 PUSH EAX
 PUSH DWORD LIT_0
 CALL printf
 ADD ESP,8
 MOV ESP,EBP
 POP EBP
 RET 0

