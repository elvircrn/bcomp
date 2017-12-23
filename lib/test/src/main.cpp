#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Bompiler.h"

int compile(const std::wstring &);

TEST_CASE("Basic compile tests") {
  bompiler::Bompiler bompiler{};
  REQUIRE(bompiler.compile(L"data/test1.b"));
  REQUIRE(bompiler.compile(L"data/test2.b"));
  REQUIRE(bompiler.compile(L"data/test3.b"));
  REQUIRE(bompiler.compile(L"data/test4.b"));
}


