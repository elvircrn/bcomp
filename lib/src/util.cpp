//
// Created by elvircrn on 12/24/2017.
//
#include <string>
#include <codecvt>
#include <locale>
#include <iterator>

#include "util.h"

std::wstring util::s2ws(const std::string &str) {
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  return converterX.from_bytes(str);
}

std::string util::ws2s(const std::wstring &wstr) {
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  return converterX.to_bytes(wstr);
}

int util::matchingParen(const std::wstring &expr, int pos) {
  return (int)expr.find(L')');
}

std::pair<std::wstring, int> util::takeBuff(const std::wstring &buff, int position, bool onlyUpper) {
  std::wstring str;

  while (buff[position] == L' ')
    position++;

  for (; position < buff.length(); position++) {
    auto c = buff[position];
    if ((onlyUpper && !(c >= 'A' && c <= 'Z')) || c == ' ' || c == '(' || c == ')')
      break;
    str += buff[position];
  }

  return {str, position};
}
std::pair<std::vector<std::wstring>, int> util::takeBuffs(const std::wstring &buff,
                                                          int position,
                                                          bool onlyUpper) {
  std::vector<std::wstring> strs;
  std::wstring str;
  while (true) {
    std::tie(str, position) = takeBuff(buff, position, onlyUpper);
    if (str.empty())
      break;
    strs.push_back(str);
  }

  return {strs, position};
}
