#ifndef BOMPILER_ARGUMENT_H
#define BOMPILER_ARGUMENT_H

#include "ParseTree.h"

namespace bompiler {
class BArgument {
  bompiler::PNode *node;
public:
  BArgument();
  explicit BArgument(bompiler::PNode *_node);
  inline bompiler::PNode* getNode() const { return node; }
  // Arg info is first child of ARG node
  inline std::wstring argType() const { return node->getChild(0)->getName(); }
  inline PNode *getVal() const { return node->getChild(0); }
};
}

#endif //BOMPILER_ARGUMENT_H
