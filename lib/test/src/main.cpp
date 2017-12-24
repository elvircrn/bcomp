#define ENABLE_TESTS


#include <iostream>


#ifdef ENABLE_TESTS
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#endif

#include "TestData.h"
#include "Bompiler.h"
#include "util.h"

#include <string>

using bompiler::Bompiler;
using namespace util;

#ifndef ENABLE_TESTS
int main() {
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
  return 0;
}
#else
TEST_CASE("Basic compile tests") {
  REQUIRE(Bompiler(std::get<0>(test1Params), std::get<1>(test1Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(std::get<0>(test2Params), std::get<1>(test2Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(std::get<0>(test3Params), std::get<1>(test3Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(std::get<0>(test4Params), std::get<1>(test4Params)).getState() == Bompiler::State::SUCCESS);
}


TEST_CASE("printf test") {
  REQUIRE(Bompiler(std::get<0>(printfTestParams), std::get<1>(printfTestParams)).getState() == Bompiler::State::SUCCESS);
}

#endif

