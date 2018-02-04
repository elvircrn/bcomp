#include <iostream>

#include "Bompiler.h"
#include "ParseTree.h"
#include "util.h"
#include "TestData.h"

#include <string>
#include <fstream>

using bompiler::Bompiler;
using namespace util;
using namespace bompiler;

void compileTest(const std::string &code) {
  bompiler::Bompiler program(UNPACK_CONSTRUCTOR(PACK_PARAM(code)));
  ParseTree(program.astStr(), 0).print();
  std::wcout << program.asmStr() << "\n\n"
             << program.astStr() << '\n';

  std::wfstream fout("asmbuff.asm");
  fout << program.asmStr() << '\n';

  if (program.getState() == bompiler::Bompiler::State::SUCCESS) {
    std::wcout << L"Success\n";
  } else {
    std::wcout << L"Fail\n";
  } 
} 

/** Hello World */
std::string helloWorld = R"(
main() {
  printf("Hello World\n");
}
)";

const std::string exprOrder = R"(
main() {
  auto x;
  x = 2;
  auto y;
  y = 2;
  auto z;
  z = 2;
  auto k;
  k = x * y + z;
  printf("%d\n", k);
  k = x + y * z;
  printf("%d\n", k);
  k = x * (y + z);
  printf("%d\n", k);
  printf("%d\n", 2 + 2);
  printf("%d\n", x * 2 + z);
}
)";


/** 1 */
const std::string charTest = R"(
main() { 
  printf("%c\n", '1');
}
)";


/**
 * 1
 * 1
 * 3*/
const std::string unaryIncr = R"(
main() { 
  auto i;
  i = 0;
  i++;
  printf("%d\n", i);
  printf("%d\n", i++);
  printf("%d\n", ++i);
}
)";

/**
 * 1
 * 1
 * 3*/
const std::string compTest = R"(
main() { 
  auto x;
  auto y;
  x = 1;
  y = 2;
  printf("%d\n", x < y);
  printf("%d\n", y < x);
  printf("%d\n", x < y);
  printf("%d\n", y < x);
}
)";

/**
 * 1
 * 2
 * 1024
 */
const std::string fastPowTest = R"(
fastPow(base, exp) {
  if (exp == 0) {
    return 1;
  } else if (exp == 1) {
    return base;
  } else if (exp % 2 == 0) {
    auto t = fastPow(base, exp / 2);
    return t * t;
  } else if (exp % 2 == 1) {
    return fastPow(base, exp - 1);
  }
}
main() {
  printf("%d\n", fastPow(2, 0));
  printf("%d\n", fastPow(2, 1));
  printf("%d\n", fastPow(2, 10));
)"; 

int main() {
  compileTest(compTest);
  return 0;
}

