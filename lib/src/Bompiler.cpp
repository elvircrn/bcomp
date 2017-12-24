#include "Bompiler.h"
#include "Scanner.h"
#include "Parser.h"

#include <iostream>

bool bompiler::Bompiler::compile(const std::wstring &filePath) const {

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

bompiler::Bompiler::State bompiler::Bompiler::getState() {
  return State::SUCCESS;
}
