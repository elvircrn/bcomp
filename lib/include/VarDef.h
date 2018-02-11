#ifndef BOMPILER_VARDEF_H
#define BOMPILER_VARDEF_H

#include "ParseTree.h"

#include <string>

namespace bompiler {
class VarDef : public PNode {
  bool _isLocal;
  bool _isFParam;
  size_t _stackId;

public:
  VarDef(PNode *_parent, const wstring &_name, const std::vector<std::wstring> &attrs, bool __isLocal, bool __isFParam);
  VarDef(PNode *_parent, const wstring &_varName, bool __isLocal, bool __isFParam);
  inline std::wstring varName() const { return attrs[0]; }
  inline bool isLocal() const { return _isLocal; }
  inline size_t stackId() const { return _stackId; }
  inline void stackId(size_t id) { _stackId = id; }
  inline bool isFparam() const { return _isFParam; }
  ~VarDef() override;
};
}

#endif //BOMPILER_VARDEF_H
