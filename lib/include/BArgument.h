#ifndef BOMPILER_ARGUMENT_H
#define BOMPILER_ARGUMENT_H

#include "ParseTree.h"
#include "Var.h"

namespace bompiler {
class BArgument : public PNode {
public:

  BArgument(PNode *_parent, const wstring &_name, const vector<wstring> &_args) : PNode(_parent, _name, _args) {}
  // Arg info is first child of ARG node
  inline std::wstring argType() const { return getChild(0)->getName(); }
  inline PNode *getVal() const { return getChild(0); }
};
}

#endif //BOMPILER_ARGUMENT_H
