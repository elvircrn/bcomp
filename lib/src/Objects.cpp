#include "Objects.h"

#include <functional>
#include <algorithm>

using std::experimental::optional;
using std::experimental::make_optional;
using namespace bompiler;

bompiler::BFunction& bompiler::Objects::addFunction(const bompiler::BFunction &f) {
  functions.emplace_back(f);
}

optional<bompiler::BFunction &> bompiler::Objects::findFunction(const FuncCall &fcall) {
  for (auto& f : functions)
    if (f.name() == fcall.funcName())
      return make_optional(std::reference_wrapper<bompiler::BFunction>(f));
  return optional<bompiler::BFunction &>{};
}
bool Objects::labelExists(const std::wstring &label) const {
  return std::find_if(labels.begin(), labels.end(), [label](const PNode* node) -> bool {
    return label == node->getAttr(0);
  }) != labels.end();
}
