#include "ParseTree.h"

#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <tuple>
#include "util.h"

using namespace bompiler;
using namespace util;

using std::make_unique;

PNode::PNode(const wstring &_name) : name(_name), parent(nullptr) {}

bool PNode::isParent() {
  return parent == nullptr;
}

PNode::PNode(PNode *_parent, const wstring &_name) : parent(_parent), name(_name) {

}

PNode* ParseTree::dfs(const std::wstring &expr, int &pos, PNode *parent) {
  if (expr[pos] == '(')
    pos++;

  // Ignore whitespace
  while(expr[pos] == ' ')
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

void ParseTree::print(PNode* node, int depth) {
  for (int i = 0; i < depth; i++)
    std::wcout << ' ';
  std::wcout << node->name << ' ' << node->children.size() << '\n';
  for (auto next : node->children) {
    print(next, depth + 1);
  }
}

void ParseTree::print() {
  print(root, 0);
}

ParseTree::ParseTree(const std::wstring &expr, int position) {
  int pos = 1;
  root = dfs(expr, pos, nullptr);
//  PNode *node = nullptr;
//
//  int i = position, depth = 0;
//  while (i < expr.length()) {
//
//    if (expr[i] == '(') {
//      depth++;
//      continue;
//    } else if (expr[i] == ')') {
//      depth--;
//      if (depth <= 0)
//        break;
//      continue;
//    }
//
//    std::wstring namebuff;
//    int next;
//
//    std::tie(namebuff, next) = takeBuff(expr, position, true);
//
//    // Handle node name
//    if (!namebuff.empty()) {
//      if (!node) {
//        root = new PNode(namebuff);
//        node = root;
//      }
//
//      // Add node attributes if any exist
//      std::wstring attr;
//      do {
//        std::tie(attr, next) = takeBuff(expr, next);
//        if (!attr.empty())
//          node->attrs.push_back(attr);
//      } while(!attr.empty());
//      i = next;
//    }
//  }
}
