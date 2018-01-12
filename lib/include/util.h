//
// Created by elvircrn on 12/24/2017.
//

#ifndef BOMPILER_COREUTIL_H
#define BOMPILER_COREUTIL_H

#include <vector>

namespace util {
template<typename Function, typename Tuple, size_t ... I>
auto call(Function f, Tuple t, std::index_sequence<I ...>) {
  return f(std::get<I>(t) ...);
}

template<typename Function, typename Tuple>
auto call(Function f, Tuple t) {
  static constexpr auto size = std::tuple_size<Tuple>::value;
  return call(f, t, std::make_index_sequence<size>{});
}

std::wstring s2ws(const std::string &str);
std::string ws2s(const std::wstring &wstr);
std::string ws2s(std::wstring const &wstr);

/**
 * Takes (alphanumeric) characters starting from 'posotion'
 * ignoring the first whitespaces.
 */
std::pair<std::wstring, int> takeBuff(const std::wstring &buff,
                                      int position,
                                      bool onlyAlpha = false);

/**
 * Takes (alphanumeric) characters starting from 'posotion'
 * ignoring the first whitespaces until non-alphanum character is reached.
 */
std::pair<std::vector<std::wstring>, int> takeBuffs(const std::wstring &buff,
                                                    int position,
                                                    bool onlyAlpha = false);

int matchingParen(const std::wstring &expr, int pos);
}

#endif //BOMPILER_COREUTIL_H
