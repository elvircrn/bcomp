#ifndef BOMPILER_NAMES_H
#define BOMPILER_NAMES_H

#include <string>
#include <set>

namespace bompiler {
const std::wstring STRING_LIT_PREFIX = L"LIT_"; // NOLINT
const std::wstring LABEL_PREFIX = L"LABEL_"; // NOLINT
const std::wstring GOTO_PREFIX = L"GOTO_"; // NOLINT
const std::set<std::wstring> arithNodes = { L"ADD", L"SUB", L"SUB", L"OR", L"AND", L"DIV", L"MUL" };
}

#endif //BOMPILER_NAMES_H
