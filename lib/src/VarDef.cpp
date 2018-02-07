#include <ParseTree.h>
#include <VarDef.h>
#include <BFunction.h>

using namespace bompiler;

VarDef::VarDef(bompiler::PNode *_parent, const wstring &_name, const std::vector<std::wstring> &_attrs, bool __isLocal)
    : PNode(_parent,
            _name,
            _attrs), _isLocal(__isLocal) {
  std::wstring varName = attrs[0];
  auto f = getAncestorByName(L"FUNCDEF")->as<BFunction>();
  f->getBlock()->addVarDef(this);
}

VarDef::VarDef(PNode *_parent, const wstring &_varName, bool __isLocal) : PNode(_parent, L"VARDEF") {
  attrs.push_back(_varName);
  _isLocal = __isLocal;
}

VarDef::~VarDef() = default;
