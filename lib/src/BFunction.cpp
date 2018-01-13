#include <algorithm>
#include "BFunction.h"

using namespace bompiler;

BFunction::BFunction(bompiler::PNode *_declaration) : node(_declaration){
  
}

std::wstring BFunction::name() const {
  return node->getAttrs()[0];
}

std::vector<bompiler::BArgument> BFunction::getArgs(bool reverse) const {
  std::vector<BArgument> args;
  // FPARAMS are children of FHEADER
  for (auto child : node->getChild(0)->getChildren())
    args.emplace_back(child);
  if (reverse)
    std::reverse(args.begin(), args.end());
  return args;
}

