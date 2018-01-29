#include "Var.h"

using namespace bompiler;

Var::Var(PNode *_parent, const wstring &_name, const std::vector<std::wstring> &_attrs) : PNode(_parent,
                                                                                                _name,
                                                                                                _attrs) {
}
