#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Bompiler.h"

using bompiler::Bompiler;

int compile(const std::wstring &);

TEST_CASE("Basic compile tests") {
  REQUIRE(bompiler::Bompiler(L"data/test1.b").getState() == bompiler::Bompiler::State::SUCCESS);
  REQUIRE(bompiler::Bompiler(L"data/test2.b").getState() == bompiler::Bompiler::State::SUCCESS);
  REQUIRE(bompiler::Bompiler(L"data/test3.b").getState() == bompiler::Bompiler::State::SUCCESS);
  REQUIRE(bompiler::Bompiler(L"data/test4.b").getState() == bompiler::Bompiler::State::SUCCESS);
}

TEST_CASE("printf test") {
  bompiler::Bompiler compiler(L"data/printftest.b");
  REQUIRE(compiler.getState() == Bompiler::State::SUCCESS);
}



