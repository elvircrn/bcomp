#ifndef BOMPILER_FUNCCALL_H
#define BOMPILER_FUNCCALL_H
#include "ParseTree.h"
#include "BArgument.h"
namespace bompiler {
class FuncCall {
  PNode *node;
public:
  FuncCall();
  explicit FuncCall(PNode *_node);
  inline PNode* getNode() const { return node; }
  std::vector<bompiler::BArgument> getArgs(bool reverse = false) const;
  inline std::wstring funcName() const { return node->getChild(0)->getAttr(0); }
  inline size_t nargs() const { return getArgs().size(); }
};
}
#endif //BOMPILER_FUNCCALL_H
