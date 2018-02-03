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
}
)";


std::string charTest = R"(
main() { 
  printf("%c\n", '1');
}
)";


int main() {
  compileTest(charTest);
  return 0;
}
