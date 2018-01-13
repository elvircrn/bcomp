#include "TestData.h"
#include "Bompiler.h"
#include "util.h"
#include "../../third_party/Catch/include/catch.hpp"

TEST_CASE("Basic compile tests") {
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::test1Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::test2Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::test3Params)).getState() == Bompiler::State::SUCCESS);
  REQUIRE(Bompiler(UNPACK_CONSTRUCTOR(testdata::test4Params)).getState() == Bompiler::State::SUCCESS);
}


TEST_CASE("printf test") {
  auto compileStatus = Bompiler(UNPACK_CONSTRUCTOR(testdata::printfTestParams)).getState();
  REQUIRE(compileStatus == Bompiler::State::SUCCESS);
}



TEST_CASE("function definition") {
  auto compileStatus = Bompiler(UNPACK_CONSTRUCTOR(testdata::funcDefParams)).getState();
  REQUIRE(compileStatus == Bompiler::State::SUCCESS);
}

