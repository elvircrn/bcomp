#include <string>

#include "names.h"
#include "Int.h"
#include "TreeOpt.h"
#include "ParseTree.h"

using namespace bompiler; 

bool bompiler::canEval(PNode *node) {
  return (arithNodes.find(node->getName()) != arithNodes.end()) &&
      node->nchildren() == 2 &&
      node->getChild(0)->getName() == L"INT" &&
      node->getChild(1)->getName() == L"INT";
}

Int *bompiler::arithEval(PNode *node) {
  int x = node->getChild(0)->as<Int>()->getVal(),
      y = node->getChild(1)->as<Int>()->getVal();
  std::wstring op = node->getName();

  auto parent = node->getParent();
  node->getParent()->deleteChild(node);

  if (op == L"ADD") {
    return new Int(parent, x + y);
  } else if (op == L"SUB") {
    return new Int(parent, x - y);
  } else if (op == L"OR") {
    return new Int(parent, x | y);
  } else if (op == L"AND") {
    return new Int(parent, x & y);
  } else if (op == L"XOR") {
    return new Int(parent, x ^ y);
  } else if (op == L"DIV") {
    return new Int(parent, x / y);
  }
}

PNode* bompiler::arithOpt(PNode *node) {
  if (canEval(node)) {
    node = arithEval(node);
    return node;
  }

  for (int i = 0; i < (int)node->getChildren().size(); i++) {
    arithOpt(node->getChild(i));
  }

  if (canEval(node))
    node = arithEval(node);
  
  return node;
}

ParseTree bompiler::arithOpt(ParseTree tree) { 
  
  return tree;
}
