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
  explicit Block(PNode *parent, const std::wstring &_name);
};
}

#endif //BOMPILER_BLOCK_H
