#ifndef BOMPILER_VAR_H
#define BOMPILER_VAR_H

#include "ParseTree.h"

#include <vector>
#include <string>

namespace bompiler {
class Var : public PNode {
  PNode * parentScope;
public:
  Var(PNode *_parent, const wstring &_name, const std::vector<std::wstring> &_attrs);
};
}

#endif //BOMPILER_VAR_H
