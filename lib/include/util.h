//
// Created by elvircrn on 12/24/2017.
//

#ifndef BOMPILER_COREUTIL_H
#define BOMPILER_COREUTIL_H

namespace util {
template<typename Function, typename Tuple, size_t ... I>
auto call(Function f, Tuple t, std::index_sequence<I ...>)
{
  return f(std::get<I>(t) ...);
}

template<typename Function, typename Tuple>
auto call(Function f, Tuple t)
{
  static constexpr auto size = std::tuple_size<Tuple>::value;
  return call(f, t, std::make_index_sequence<size>{});
}



std::wstring s2ws(const std::string &str);
std::string ws2s(const std::wstring& wstr);
std::string ws2s(std::wstring const& wstr);
}

#endif //BOMPILER_COREUTIL_H
