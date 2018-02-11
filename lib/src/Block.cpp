#include "ParseTree.h"
#include <Block.h>
#include "Block.h"
#include "BFunction.h"

using namespace bompiler;

bompiler::Block::Block(PNode *_parent, const std::wstring &_name,
                       const std::vector<std::wstring> &_attrs)
    : PNode(_parent, _name, _attrs) {

  // Register VarDefs if parent is function
  // NOTE: Assumes that FHEADER is already parsed
  if (parent->getName() == L"FUNCDEF") { 
    auto f = parent->as<BFunction>();
    size_t paramId{};
    // TODO: Consider moving this somwhere else
    for (FParam *fparam : f->getArgs()) {
      f->getBlock()->addVarDef(new VarDef(f->getBlock(), fparam->paramName(), true, true), paramId++);
    }
  }
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

void Block::addVarDef(VarDef *var, size_t _stackId) {
  varMap[var->varName()] = var;
  var->stackId(_stackId);
}

Block::~Block() = default;
