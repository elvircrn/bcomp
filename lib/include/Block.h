//
// Created by elvircrn on 1/28/2018.
//

#ifndef BOMPILER_BLOCK_H
#define BOMPILER_BLOCK_H

#include "ParseTree.h"

namespace bompiler {
class Block : public PNode {
public:
  int varCnt;
  Block(PNode *parent, const std::wstring &_name, const std::vector<std::wstring> &_attrs);
};
}

#endif //BOMPILER_BLOCK_H
