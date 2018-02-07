#ifndef BOMPILER_FUNCTION_H
#define BOMPILER_FUNCTION_H

#include "ParseTree.h"
#include "BArgument.h"
#include "Block.h"
#include "VarDef.h"
#include "FParam.h"

namespace bompiler {
class BFunction : public PNode {
public:
  BFunction(PNode *_parent, const wstring &_name, const vector<std::wstring> &);
  std::wstring name() const;
  std::vector<bompiler::FParam*> getArgs(bool reverse = false) const;
  inline size_t nargs() const { return getArgs().size(); }
  // TODO: Add more safety later
  inline Block* getBlock() { return reinterpret_cast<Block*>(getChild(1)); }
  ~BFunction() override;
};
}

#endif //BOMPILER_FUNCTION_H
