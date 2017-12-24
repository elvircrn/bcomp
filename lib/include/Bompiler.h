//
// Created by elvircrn on 12/23/2017.
//

#ifndef BOMPILER_BOMPILER_H
#define BOMPILER_BOMPILER_H
#include <string>
#include "Parser.h"
#include "Scanner.h"

namespace bompiler {
class Bompiler {
public:
  enum class State { SUCCESS, FAIL };

private:
  enum State;

  Scanner scanner;
  Parser parser;

  State state;

public:
  explicit Bompiler(const std::wstring &filePath);
  Bompiler(const unsigned char* buf, int len);
  bool compile(const std::wstring &filePath) const;
  std::wstring asmStr();
  std::wstring astStr();

  State getState();
};
}


#endif //BOMPILER_BOMPILER_H
