#include "Bompiler.h"
#include "Scanner.h"
#include "Parser.h"

#include <iostream>

// TODO: Hopelessly in need of refactoring
bool bompiler::Bompiler::compile(const std::wstring &filePath) {

}

std::wstring bompiler::Bompiler::astStr() {
  return parser.AST();
}

std::wstring bompiler::Bompiler::asmStr() {
  return parser.AsmOutput();
}

bompiler::Bompiler::Bompiler(const std::wstring &filePath) : scanner(filePath.c_str()),
                                                             parser(&scanner) {
  parser.Parse();
  if (parser.errors->count == 0)
    state = State::SUCCESS;
  else
    state = State::FAIL;
}

bompiler::Bompiler::Bompiler(const unsigned char* buf, int len) : scanner(buf, len),
                                                             parser(&scanner) {
  parser.Parse();
  if (parser.errors->count) {
    state = State::FAIL;
    return;
  }

  pt = ParseTree(parser.ParseList, 0);

  compile(pt.getRoot()); 

  state = State::SUCCESS;
}

bompiler::Bompiler::State bompiler::Bompiler::getState() {
  return state;
}
void Bompiler::compile() {

}
void Bompiler::compile(PNode *node) {

}
