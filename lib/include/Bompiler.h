//
// Created by elvircrn on 12/23/2017.
//

#ifndef BOMPILER_BOMPILER_H
#define BOMPILER_BOMPILER_H
#include <string>

namespace bompiler {
class Bompiler {
public:
  Bompiler();
  bool compile(const std::wstring &filePath) const;
};
}

#endif //BOMPILER_BOMPILER_H
