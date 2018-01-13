
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

public:
  explicit PNode(const wstring &_name);
  PNode(PNode *_parent, const wstring &_name, const std::vector<std::wstring> &);
  PNode(PNode *_parent, const wstring &_name);
  bool isRoot();
  inline std::vector<PNode*> getChildren() { return children; }
  inline PNode* getChild(int i) { return children[i]; }
  inline std::wstring getName() const { return name; }
  inline std::vector<std::wstring> getAttrs() const { return attrs; }
  inline std::wstring getAttr(int i) const { return attrs[i]; }
  PNode *copy(PNode *parent = nullptr) const;
  vector<PNode *> children;
  PNode *parent;

  ~PNode();

  friend class ParseTree;
};

class ParseTree {
  PNode *root{};
  std::vector<PNode *> nodes;
  void _delete();

public:
  ParseTree() = default;
  ParseTree(const std::wstring &expr, int position);
  ParseTree(ParseTree &&) noexcept;
  ParseTree &operator=(const ParseTree &);
  ParseTree &operator=(ParseTree &&) noexcept ;
  ParseTree(const ParseTree &);
  ~ParseTree();

  friend class Node;
  // TODO: Pass a lambda for pseudo yielding
  PNode *dfs(const wstring &expr, int &pos, PNode *node);
  void print();
  void print(PNode *node, int depth = 0);
  vector<PNode *> generateFlatList();
  vector<PNode *> getNodes();
  PNode *getNode(int id);
  size_t nodeCount() const;
  PNode *getRoot();

};

}

#endif //BOMPILER_AST_H
