//
// Created by elvircrn on 1/11/2018.
//

#ifndef BOMPILER_AST_H
#define BOMPILER_AST_H

#include <string>
#include <cstring>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;
using std::string;

namespace bompiler {
class Node {
  string name;
  vector<unique_ptr<Node>> children;
};

class ParseTree {
  explicit ParseTree(const std::string &expr);

  friend class Node;
};
}

#endif //BOMPILER_AST_H
