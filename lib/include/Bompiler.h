//
// Created by elvircrn on 12/23/2017.
//

#ifndef BOMPILER_BOMPILER_H
#define BOMPILER_BOMPILER_H
#include <string>
#include <sstream>
#include "Parser.h"
#include "Scanner.h"
#include "ParseTree.h"
#include "Objects.h"

namespace bompiler {
class Bompiler {
public:
  enum class State { SUCCESS, FAIL };

private:
  enum State;

  Scanner scanner;
  Parser parser;

  State state;

  Objects objs;
  ParseTree pt;
  std::wstringstream _asmOutput;

public:
  explicit Bompiler(const std::wstring &filePath);
  Bompiler(const unsigned char* buf, int len);
  bool compile(const std::wstring &filePath);
  void compile();
  void compile(PNode *node);
  std::wstring asmStr();
  std::wstring astStr();

  State getState();

};
}


#endif //BOMPILER_BOMPILER_H
