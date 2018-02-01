#include "Objects.h"
#include "names.h"

#include <functional>
#include <algorithm>

using std::experimental::optional;
using std::experimental::make_optional;
using namespace bompiler;

bompiler::BFunction *bompiler::Objects::addFunction(bompiler::BFunction *f) {
  functions.emplace_back(f);
  return f;
}

bompiler::BFunction *bompiler::Objects::findFunction(FuncCall *fcall) {
  // TODO: Optimise
  for (auto &f : functions)
    if (f->name() == fcall->funcName())
      return f;

  // Function not found
  return nullptr;
}

bool Objects::labelExists(const std::wstring &label) const {
  return std::find_if(labels.begin(), labels.end(), [label](const PNode *node) -> bool {
    return label == node->getAttr(0);
  }) != labels.end();
}

std::wstring Objects::getOrCreateLiteral(const std::wstring &literal) {
  std::wstring parsedLiteral;
  for (size_t i = 0; i < literal.size(); i++) {
    if (i < literal.size() - 1 && literal[i] == '\\' && literal[i + 1] == 'n') {
      parsedLiteral += L"\", 10, \"";
      i++;
    } else {
      parsedLiteral += literal[i];
    }
  }

  // First time encountering the literal
  if (stringLiterals.find(parsedLiteral) == stringLiterals.end())
    return stringLiterals[parsedLiteral] = STRING_LIT_PREFIX + std::to_wstring(stringLiterals.size());
  else
    return stringLiterals[parsedLiteral];
}
