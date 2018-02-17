#ifndef BOMPILER_WHILE_H
#define BOMPILER_WHILE_H

#include "ParseTree.h"

namespace bompiler {
class While : PNode {
  std::wstring loopLabel, breakLabel;
public:
  While(PNode *_parent, const wstring &_name, const vector<wstring> &_args);

  void setLabels(const std::wstring &_loopLabel, const std::wstring &_breakLabel);
  inline std::wstring getLoopLabel() const { return loopLabel; }
  inline std::wstring getBreakLabel() const { return breakLabel; }
};
}

#endif //BOMPILER_WHILE_H
