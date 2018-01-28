#include "ParseTree.h"
#include <Block.h>
#include "Block.h"

using namespace bompiler;

bompiler::Block::Block(PNode *_parent, const std::wstring &_name) : PNode(_parent, _name), varCnt(0) {
  
}