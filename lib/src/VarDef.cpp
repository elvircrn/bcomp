//
// Created by elvircrn on 1/29/2018.
//

#include <ParseTree.h>
#include <VarDef.h>

using namespace bompiler;

VarDef::VarDef(bompiler::PNode *_parent, const wstring &_name, const std::vector<std::wstring> &_attrs, bool __isLocal)
    : PNode(_parent,
            _name,
            _attrs), _isLocal(__isLocal) {}
