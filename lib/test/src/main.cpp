// #define ENABLE_TESTS


#include <iostream>


#ifdef ENABLE_TESTS
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#endif


#include "Bompiler.h"
#include "util.h"

#include <string>

using bompiler::Bompiler;
using namespace util;

#ifndef ENABLE_TESTS
int main() {
  bompiler::Bompiler compiler(L"data/test1.b");
  std::wcout << compiler.astStr() << '\n';
  std::wcout << compiler.asmStr() << '\n';
  return 0;
}
#else
TEST_CASE("Basic compile tests") {
  REQUIRE(bompiler::Bompiler(L"data\\test1.b").getState() == bompiler::Bompiler::State::SUCCESS);
  REQUIRE(bompiler::Bompiler(L"data\\test2.b").getState() == bompiler::Bompiler::State::SUCCESS);
  REQUIRE(bompiler::Bompiler(L"data\\test3.b").getState() == bompiler::Bompiler::State::SUCCESS);
  REQUIRE(bompiler::Bompiler(L"data\\test4.b").getState() == bompiler::Bompiler::State::SUCCESS);
}


TEST_CASE("printf test") {
  bompiler::Bompiler compiler(L"data\\printftest.b");
  REQUIRE(compiler.getState() == Bompiler::State::SUCCESS);
}

#endif

