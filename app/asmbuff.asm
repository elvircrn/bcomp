%define f_len 12
%define main_len 0
 extern printf
 global main
 section .data
LIT_0: db "%d", 10, "", 0

section .text
 global f
f:
 PUSH EBP
 MOV EBP,ESP
 SUB ESP,f_len
 MOV ESP,EBP
 POP EBP
 RET 0
 global main
main:
 PUSH EBP
 MOV EBP,ESP
 SUB ESP,main_len
 PUSH 10
 PUSH 2
 CALL f
 ADD ESP,8
 PUSH EAX
 PUSH DWORD LIT_0
 CALL printf
 ADD ESP,8
 MOV ESP,EBP
 POP EBP
 RET 0

VAR f)(ARG (VAR base)) (ARG (SUB (VAR exp)(INT 1)) ) ) )) )) ) (FUNCDEF main (FHEADER ) (BLOCK (FUNCCALL (VAR printf)(ARG (STRING `"%d\n"`)) (ARG (FUNCCALL (VAR f)(ARG (INT 2)) (ARG (INT 10)) ) ) ) ) ) )
