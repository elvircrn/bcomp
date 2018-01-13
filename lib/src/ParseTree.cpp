#include "ParseTree.h"

#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <tuple>
#include <queue>
#include "util.h"

using namespace bompiler;
using namespace util;

using std::make_unique;

PNode::PNode(const wstring &_name) : name(_name), parent(nullptr) {}

bool PNode::isRoot() {
  return parent == nullptr;
}

PNode::PNode(PNode *_parent, const wstring &_name) : parent(_parent), name(_name) {}

PNode::~PNode() {
  for (auto &i : children)
    delete i;
}

std::wstring PNode::getName() const {
  return name;
}
std::vector<std::wstring> PNode::getAttrs() const {
  return attrs;
}

PNode *PNode::copy(PNode *parent) const {
  auto cnode = new PNode(parent, name, attrs);
  std::vector<PNode *> children;
  for (const auto &child : children)
    children.push_back(child->copy(cnode));
  cnode->children = children;
  return cnode;
}

PNode::PNode(PNode *_parent, const wstring &_name, const std::vector<std::wstring> &_attrs)
    : parent(_parent), name(_name), attrs(_attrs) {}

void ParseTree::_delete() {
  nodes.clear();
  delete root;
}

size_t ParseTree::nodeCount() const {
  return nodes.size();
}

PNode *ParseTree::dfs(const std::wstring &expr, int &pos, PNode *parent) {
  if (expr[pos] == '(')
    pos++;

  // Ignore whitespace
  while (expr[pos] == ' ')
    pos++;

  // Reached end of subtree
  if (expr[pos] == ')') {
    pos++;
    return nullptr;
  }

  std::vector<std::wstring> attrs;
  std::wstring nodeName;

  std::tie(nodeName, pos) = takeBuff(expr, pos, true);

  auto *node = new PNode(parent, nodeName);

  if (pos == expr.length())
    return node;

  std::tie(attrs, pos) = takeBuffs(expr, pos);

  node->attrs = attrs;

  if (pos == expr.length())
    return node;

  // Finished parsing subtree
  if (expr[pos] == ')') {
    pos++;
    return node;
  }

  for (;;) {
    while (expr[pos] != '(' && pos != expr.length())
      pos++;
    if (pos == expr.length())
      break;
    auto child = dfs(expr, pos, node);
    if (!child)
      break;

    node->children.push_back(child);

    if (pos == expr.length())
      break;
  }

  return node;
}

void ParseTree::print(PNode *node, int depth) {
  for (int i = 0; i < depth; i++)
    std::wcout << ' ';
  std::wcout << node->name << ' ';
  for (const auto &attr : node->attrs)
    std::wcout << attr << ' ';
  std::wcout << '\n';
  for (const auto &next : node->children) {
    print(next, depth + 1);
  }
}

void ParseTree::print() {
  print(root, 0);
}

vector<PNode *> ParseTree::generateFlatList() {
  vector<PNode *> flat;
  std::queue<PNode *> q;
  PNode *node = root;
  q.push(node);
  while (!q.empty()) {
    node = q.front();
    flat.push_back(node);
    q.pop();
    for (const auto &next : node->children)
      q.push(next);
  }
  return flat;
}

ParseTree::ParseTree(const std::wstring &expr, int position) {
  root = dfs(expr, position, nullptr);
  nodes = generateFlatList();
}

vector<PNode *> ParseTree::getNodes() {
  return nodes;
}

PNode *ParseTree::getNode(int id) {
  return nodes[id];
}

ParseTree::~ParseTree() {
  _delete();
}

PNode *ParseTree::getRoot() {
  return root;
}

ParseTree::ParseTree(ParseTree &&pt) noexcept {
  root = pt.root;
  nodes = pt.nodes;
}

ParseTree &ParseTree::operator=(const ParseTree &pt) {
  if (this == &pt)
    return *this;

  _delete();

  root = pt.root->copy();
  nodes = generateFlatList();
  return *this;
}

ParseTree::ParseTree(const ParseTree &pt) {
  root = pt.root->copy();
  nodes = pt.nodes;
}

ParseTree &ParseTree::operator=(ParseTree &&pt) noexcept {
  root = pt.root;
  nodes = pt.nodes;
  return *this;
}
