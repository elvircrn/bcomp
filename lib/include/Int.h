#ifndef BOMPILER_INT_H
#define BOMPILER_INT_H

#include "ParseTree.h"

namespace bompiler {
class Int : public PNode {
  int val;
public:
  Int(PNode *_parent, const wstring &_name, const vector<wstring> &_args);
  Int(PNode *_parent, int _val);
  inline int getVal() { return val; }
};
}

#endif //BOMPILER_INT_H
