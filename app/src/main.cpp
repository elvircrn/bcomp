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
std::string compTest = R"(
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
std::string fastPowTest = R"(
f(base, exp) {
  printf("base: %d exp: %d\n", base, exp);
  if (exp == 0) {
    return(1);
  }

  if (exp == 1) {
    return(base);
  }

  if (exp % 2 == 0) {
    auto t;
    t = f(base, exp / 2);
    return(t * t);
  } else {
    return(base * f(base, exp - 1));
  }
}

main() {
  printf("%d\n", f(2, 10));
}
)"; 

std::string funcDefTest = R"(
f(a, b, c) {
  return;
}

main() {
}
)"; 

const std::string idTest = R"(
id(x) {
  return(x);
}

main() {
  printf("%d\n", id(2));
}
)";

/**
 * 1
 * 0
 * 2
 * 3
 */
const std::string divTest = R"(
main() {
  printf("%d\n", 5 % 2);
  printf("%d\n", 6 % 2);
  printf("%d\n", 5 / 2);
  printf("%d\n", 6 / 2);
}
)";

const std::string ifTest = R"(
main() {
  auto x;
  x = 2;
  if (x == 2) {
    printf("It works!\n");
  }
}
)";

const std::string guessingGame = R"(
main() {
  auto left, right, guessCmp, cnt;
  cnt = 1;
  left = 1;
  right = 100; 
  printf("Da li je tvoj broj %d?\n", (left + right) / 2);
  scanf("%d", &guessCmp);
  while (guessCmp != 0) {
    if (guessCmp < 0) {
      right = (left + right) / 2;
    } 
    if (guessCmp > 0) {
      left = (left + right) / 2 + 1;
    }
    printf("Da li je tvoj broj %d?\n", (left + right) / 2);
    scanf("%d", &guessCmp);
    cnt++;
  }
  printf("Trebalo mi je %d pokusaja da pogodim broj\n", cnt);
  return(0);
}
)";

/**
 * 50
 */
const std::string varDivTest = R"(
main() {
  auto left, right, pivot;
  left = 1;
  right = 100;
  pivot = (left + right) / 2;
  printf("%d\n", pivot);
}
)";

const std::string globalTest = R"(
x;
main() {
  return(0);
}
)";


int main() {
  compileTest(guessingGame);
  return 0;
}

