#ifndef BOMPILER_CODEGEN_H
#define BOMPILER_CODEGEN_H

#include "Var.h"

namespace bompiler {
std::wstring genStackAddr(Var *var, int _size = 4);
std::wstring deref(const std::wstring& addr);
}

#endif //BOMPILER_CODEGEN_H
