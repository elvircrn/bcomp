#include <BFunction.h>
#include <iostream>
#include "Var.h"

using namespace bompiler;

Var::Var(PNode *_parent, const wstring &_name, const std::vector<std::wstring> &_attrs) : PNode(_parent,
                                                                                                _name,
                                                                                                _attrs) {
  // Find stack id
  PNode *node = getAncestorByName(L"FUNCDEF");

  // TODO: Do error handling here
  // Assert node != nullptr
  if (!node) {
    return;
  }

  auto f = node->as<BFunction>();

  std::wcout << L"FUNCTION NAME: " << f->getAttrs()[0] << L"\n\n\n\n\n";

  // TODO: Handle function not found
  if (!f) {
    throw "Assert";
  }

  auto varDef = f->getBlock()->getVarDef(varName());

  // TODO: Do error handling here
  // Asserts that the variable is already declared 
  if (!varDef) {
    _varDef = nullptr;
  } else {
    _varDef = varDef;
  }
}
Var::~Var() = default;


