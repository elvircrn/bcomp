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

  Scanner scanner;
  Parser parser;

  State state;

  Objects objs;
  ParseTree pt;
  std::wstringstream _asmOutput, data, header;

public:
  explicit Bompiler(const std::wstring &filePath);
  void genArithOp(PNode *node, const std::wstring &op);
  Bompiler(const unsigned char* buf, int len);
  bool compile(const std::wstring &filePath);
  void compile();
  void compile(PNode *node);
  std::wstring asmStr();
  std::wstring astStr();

  State getState();

  void generateDataSection();
  void generateHeader();
};
}


#endif //BOMPILER_BOMPILER_H
