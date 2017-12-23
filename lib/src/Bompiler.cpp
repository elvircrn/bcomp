#include "Bompiler.h"
#include "Scanner.h"
#include "Parser.h"

bool bompiler::Bompiler::compile(const std::wstring &filePath) const {
  Scanner scanner = Scanner(filePath.c_str());
  Parser parser = Parser(&scanner);
  parser.Parse();
  if (parser.errors->count == 0) {
    return true;
  }
}
bompiler::Bompiler::Bompiler() = default;
