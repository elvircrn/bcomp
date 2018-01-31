#include "ParseTree.h"
#include <Block.h>
#include "Block.h"

using namespace bompiler;

bompiler::Block::Block(PNode *_parent, const std::wstring &_name,
                       const std::vector<std::wstring> &_attrs)
    : PNode(_parent, _name, _attrs) {
  
}

VarDef* Block::getVarDef(const std::wstring &varName) {
  // TODO: Handle var not found error
  auto res =  varMap.find(varName);
  return res == varMap.end() ? nullptr : res->second;
}

void Block::addVarDef(VarDef *var) {
  varMap[var->varName()] = var;
  var->stackId(varCnt());
}

Block::~Block() = default;