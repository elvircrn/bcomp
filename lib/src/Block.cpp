#include "ParseTree.h"
#include <Block.h>
#include "Block.h"

using namespace bompiler;

bompiler::Block::Block(PNode *_parent, const std::wstring &_name, const std::vector<std::wstring> &_attrs) : PNode(
    _parent,
    _name,
    _attrs), varCnt(0) {

}