#include <algorithm>
#include "BFunction.h"
#include "FParam.h"

using namespace bompiler;

std::wstring BFunction::name() const {
  return getAttrs()[0];
}

std::vector<bompiler::FParam*> BFunction::getArgs(bool reverse) const {
  std::vector<FParam*> args;
  // FPARAMS are children of FHEADER
  for (auto child : getChild(0)->getChildren())
    args.emplace_back(child->as<FParam>());
  if (reverse)
    std::reverse(args.begin(), args.end());
  return args;
}

BFunction::BFunction(PNode *_parent, const wstring &_name, const vector<wstring> &_attrs) : PNode(_parent, _name,
_attrs) { }

BFunction::~BFunction() = default;

