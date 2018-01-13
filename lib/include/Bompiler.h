//
// Created by elvircrn on 12/23/2017.
//

#ifndef BOMPILER_BOMPILER_H
#define BOMPILER_BOMPILER_H
#include <string>
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

  void compile();
  void compile(PNode *node);

public:
  explicit Bompiler(const std::wstring &filePath);
  Bompiler(const unsigned char* buf, int len);
  bool compile(const std::wstring &filePath);
  std::wstring asmStr();
  std::wstring astStr();

  State getState();

};
}


#endif //BOMPILER_BOMPILER_H
