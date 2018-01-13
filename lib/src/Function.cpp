#include "Function.h"

using namespace bompiler;

Function::Function(bompiler::PNode *_declaration) : node(_declaration){
  
}

std::wstring Function::name() const {
  return node->getAttrs()[0];
}
