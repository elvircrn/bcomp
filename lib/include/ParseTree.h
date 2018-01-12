#ifndef BOMPILER_AST_H
#define BOMPILER_AST_H

#include <string>
#include <cstring>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;
using std::wstring;
using std::weak_ptr;

namespace bompiler {

class ParseTree;

class PNode {
  wstring name;
  vector<wstring> attrs;
  vector<PNode *> children;
  PNode *parent;

public:
  explicit PNode(const wstring &name);
  PNode(PNode *_parent, const wstring &_name);
  bool isParent();

  friend class ParseTree;
};

class ParseTree {
  PNode *root;
public:

  ParseTree(const std::wstring &expr, int position);

  friend class Node;
  PNode* dfs(const wstring &expr, int &pos, PNode *node);
  void print();
  void print(PNode *node, int depth);
};

}

#endif //BOMPILER_AST_H
