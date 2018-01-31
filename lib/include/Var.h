#ifndef BOMPILER_VAR_H
#define BOMPILER_VAR_H

#include "ParseTree.h"

#include <vector>
#include <string>

namespace bompiler {
class Var : public PNode {
  PNode * parentScope;
  VarDef *_varDef;
public:
  Var(PNode *_parent, const wstring &_name, const std::vector<std::wstring> &_attrs);
  inline std::wstring varName() const { return attrs[0]; }
  ~Var() override;
  inline VarDef* varDef() const { return _varDef; }
};
}

#endif //BOMPILER_VAR_H
