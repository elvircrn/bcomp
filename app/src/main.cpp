#include <iostream>

#include "Bompiler.h"
#include "ParseTree.h"
#include "util.h"
#include "TestData.h"

#include <string>

using bompiler::Bompiler;
using namespace util;
using namespace bompiler;

void printfHeaderTest() {
  bompiler::Bompiler compiler(L"data/test1.b");
  std::wcout << compiler.astStr() << '\n';

  std::wstring printfHeader = LR"(
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

  // std::wcout << printfHeader + compiler.asmStr() << '\n';
  std::wcout << compiler.asmStr() << '\n';
}

void funcDef() {
//  const std::string &functionDef = R"(
//fun3(x, y, z) {
//  auto a, b, c;
//  a = 2;
//  b = 3;
//  c = a + b;
//}
//main() {
//  auto a, b, c;
//  a = 1;
//  b = 2;
//  c = 3;
//  fun3(a, b, c);
//  a = 2;
//  b = 1;
//  fun3(1, b, 2);
//  fun3(1, b, "123123");
//}
//)";

  const std::string &exprOrder = R"(
main() {
  auto x;
  auto y;
  auto z;
  auto k;
  k = x / y + z;
}
)";

  const std::string &helloWorld = R"(
main() {
  printf("Hello Wold");
}
)";

  bompiler::Bompiler program(UNPACK_CONSTRUCTOR(PACK_PARAM(helloWorld)));
  ParseTree(program.astStr(), 0).print();
  std::wcout << program.asmStr() << "\n\n"
             << program.astStr() << '\n';
  if (program.getState() == bompiler::Bompiler::State::SUCCESS) {
    std::wcout << L"Success\n";
  } else {
    std::wcout << L"Fail\n";
  }
}

void dfsTest() {
  std::wstring expr = L"(B asd as df (A (C  asdf1 12 ) (D 12 ) (E)))";
  ParseTree(expr, 1).print();

}

/*
 PUBLIC fun3
fun3:
 PUSH EBP
 MOV EBP,ESP
 SUB ESP,fun3_len
 MOV DWORD [a],2
 MOV DWORD [b],3
 MOV EAX, [a]
 ADD EAX,[b]
 MOV [c],EAX
 MOV ESP,EBP
 RET
 PUBLIC main
main:
 PUSH EBP
 MOV EBP,ESP
 SUB ESP,main_len
 MOV DWORD [a],1
 MOV DWORD [b],2
 MOV DWORD [c],3
 MOV DWORD [a],2
 MOV DWORD [b],1
 MOV ESP,EBP
 RET


(B (FUNCDEF fun3 (FHEADER (FPARAM x )(FPARAM y )(FPARAM z )) (BLOCK (DECLSTAT (LVARDEF a ) (LVARDEF b ) (LVARDEF c ) (MOV (VAR a)(INT 2)) ) (MOV (VAR b)(INT 3)) (MOV (VAR c)(ADD (VAR a)(VAR b)) ) ) ) (FUNCDEF main (FHEADER ) (BLOCK (DECLSTAT (LVARDEF a ) (LVARDEF b ) (LVARDEF c ) (MOV (VAR a)(INT 1)) ) (MOV (VAR b)(INT 2)) (MOV (VAR c)(INT 3)) (FUNCCALL (VAR fun3)(ARG (VAR a)) (ARG (VAR b)) (ARG (VAR c)) ) (MOV (VAR a)(INT 2)) (MOV (VAR b)(INT 1)) (FUNCCALL (VAR fun3)(ARG (INT 1)) (ARG (VAR b)) (ARG (INT 2)) ) (FUNCCALL (VAR fun3)(ARG (INT 1)) (ARG (VAR b)) (ARG (STRING `"123123"`)) ) ) ) )
Success

 * 
*/
int main() {
  funcDef();
    return 0;
}
