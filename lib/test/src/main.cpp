// #define ENABLE_TESTS


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
  bompiler::Bompiler program(UNPACK_CONSTRUCTOR(testdata::funcDefParams));
  std::wcout << program.asmStr() << '\n';
}

int main() {
  funcDef();
  return 0;
}
#else
TEST_CASE("Basic compile tests") {
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::test1Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::test2Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::test3Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::test4Params)).getState() == Bompiler::State::SUCCESS);
}


TEST_CASE("printf test") {
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::printfTestParams)).getState() == Bompiler::State::SUCCESS);
}

TEST_CASE("function definition") {
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::funcDefParams)).getState() == Bompiler::State::SUCCESS);
}

#endif

