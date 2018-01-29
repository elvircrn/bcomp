//
// Created by elvircrn on 1/29/2018.
//

#ifndef BOMPILER_VARDEF_H
#define BOMPILER_VARDEF_H

#include "ParseTree.h"

#include <string>

namespace bompiler {
class VarDef : public PNode {
  bool _isLocal;
public:
  VarDef(PNode *_parent, const wstring &_name, const std::vector<std::wstring> &attrs, bool __isLocal);
  inline std::wstring varName() const { return attrs[0]; }
  inline bool isLocal() const { return _isLocal; }
};
}

#endif //BOMPILER_VARDEF_H
