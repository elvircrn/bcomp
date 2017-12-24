//
// Created by elvircrn on 12/24/2017.
//

#ifndef BOMPILER_ASM_HEAD_H
#define BOMPILER_ASM_HEAD_H

#include <string>

const std::wstring &ASM_HEADER =
LR"(
section .data
         an:    db 'a'
         format: db "num: %c" , 10, 0

section .text
         global main
         extern printf

main:
         push ebp
         mov ebp,esp

         mov eax, [an]
         push eax
         push dword format
         call printf

         add esp, 8
         mov esp,ebp
         pop ebp

         mov eax, 0
         ret

)";

#endif //BOMPILER_ASM_HEAD_H
