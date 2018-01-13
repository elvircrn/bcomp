//
// Created by elvircrn on 1/12/2018.
//

#ifndef BOMPILER_FUNCTION_H
#define BOMPILER_FUNCTION_H

#include "ParseTree.h"

namespace bompiler {
class Function {
  PNode *node;
public:
  std::wstring name() const;
  Function(PNode *_declaration);
};
}

#endif //BOMPILER_FUNCTION_H
