#include "util.h"

#include "catch.hpp"

#include <string>
#include <tuple>

TEST_CASE("takeBuff", "[util]") {
  std::wstring buff;
  int next;

  std::tie(buff, next) = util::takeBuff(L"NAME", 0, true);
  REQUIRE((buff == L"NAME" && next == 4));

  std::tie(buff, next) = util::takeBuff(L"     NAME", 0, true);
  REQUIRE((buff == L"NAME" && next == 9));

  std::tie(buff, next) = util::takeBuff(L"     NAME        ", 0, true);
  REQUIRE((buff == L"NAME" && next == 9));

  std::tie(buff, next) = util::takeBuff(L"12345        ", 0);
  REQUIRE((buff == L"12345" && next == 5));

  std::tie(buff, next) = util::takeBuff(L"     name1        ", 0);
  REQUIRE((buff == L"name1" && next == 10));

  std::tie(buff, next) = util::takeBuff(L"           ", 0, true);
  REQUIRE((buff.empty() && next == 11));
}

TEST_CASE("takeBuffs", "[util]") {
  std::vector<std::wstring> buffs;
  int next;

  std::tie(buffs, next) = util::takeBuffs(L" NAME  name1 12345   ", 0);

  REQUIRE(buffs.size() == 3);
  REQUIRE(buffs[0] == L"NAME");
  REQUIRE(buffs[1] == L"name1");
  REQUIRE(buffs[2] == L"12345");
  REQUIRE(next == 21);
}

TEST_CASE("takeBuffs AST", "[util]") {
  std::vector<std::wstring> buffs;
  int next;

  std::tie(buffs, next) = util::takeBuffs(L"(B (A (C) (D) (E)))", 4);
  REQUIRE(buffs.size() == 1);
  REQUIRE(buffs[0] == L"A");
  REQUIRE(next == 6);

  std::tie(buffs, next) = util::takeBuffs(L"(B (A (C) (D) (E)))", 6);
  REQUIRE(buffs.empty());
  REQUIRE(next == 6);

  std::tie(buffs, next) = util::takeBuffs(L"(B (A (C) (D) (E)))", 4);
  REQUIRE(!buffs.empty());
  REQUIRE(buffs[0] == L"A");
  REQUIRE(next == 6);
}
