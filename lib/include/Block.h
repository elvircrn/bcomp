#ifndef BOMPILER_BLOCK_H
#define BOMPILER_BLOCK_H

#include "ParseTree.h"
#include "VarDef.h"

#include <map>
#include <set>

namespace bompiler {
class Block : public PNode {
  std::map<std::wstring, VarDef*> varMap;
public:
  inline size_t varCnt() const { return varMap.size(); }
  Block(PNode *parent, const std::wstring &_name, const std::vector<std::wstring> &_attrs);
  void addVarDef(VarDef* );
  VarDef* getVarDef(const std::wstring &varName);
  ~Block() override;
};
}

#endif //BOMPILER_BLOCK_H
