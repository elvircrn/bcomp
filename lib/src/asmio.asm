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
ret
