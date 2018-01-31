#ifndef BOMPILER_FUNCCALL_H
#define BOMPILER_FUNCCALL_H
#include "ParseTree.h"
#include "BArgument.h"
namespace bompiler {
class FuncCall : public PNode {
public:
  FuncCall(PNode *_parent, const wstring &_name, const vector<wstring> &_args);
  std::vector<bompiler::BArgument*> getArgs(bool reverse = false) const;
  inline std::wstring funcName() const { return getChild(0)->getAttr(0); }
  inline size_t nargs() const { return getArgs().size(); }
};
}
#endif //BOMPILER_FUNCCALL_H
