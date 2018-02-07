#ifndef BOMPILER_FPARAM_H
#define BOMPILER_FPARAM_H

#include "ParseTree.h"

namespace bompiler {
class FParam : public bompiler::PNode {
public:
  FParam(PNode *_parent, const wstring &_name, const vector<wstring> &_args);
  FParam(PNode *_parent, const std::wstring &paramName);
  inline std::wstring paramName() const { return attrs[0]; }
};
}

#endif //BOMPILER_FPARAM_H
