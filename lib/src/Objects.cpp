#include "Objects.h"
#include "names.h"

#include <functional>
#include <algorithm>

using std::experimental::optional;
using std::experimental::make_optional;
using namespace bompiler;

bompiler::BFunction* bompiler::Objects::addFunction(bompiler::BFunction *f) {
  functions.emplace_back(f);
  return f;
}

bompiler::BFunction* bompiler::Objects::findFunction(FuncCall *fcall) {
  // TODO: Optimise
  for (auto &f : functions)
    if (f->name() == fcall->funcName())
      return f;

  // Function not found
  return nullptr;
}

bool Objects::labelExists(const std::wstring &label) const {
  return std::find_if(labels.begin(), labels.end(), [label](const PNode* node) -> bool {
    return label == node->getAttr(0);
  }) != labels.end();
}

std::wstring Objects::getOrCreateLiteral(const std::wstring& literal) {
  // First time encountering the literal
  if (stringLiterals.find(literal) == stringLiterals.end())
    return stringLiterals[literal] = STRING_LIT_PREFIX + std::to_wstring(stringLiterals.size());
  else
    return stringLiterals[literal]; 
}
