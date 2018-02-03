#include "CodeGen.h"
#include "Var.h"

#include <string>
#include <sstream>

using namespace bompiler;

std::wstring bompiler::genStackAddr(Var *var, int _size) {
  std::wstringstream ss;
  ss << L"EBP -" << L" " << var->varDef()->stackId() * _size;
  return ss.str();
}
