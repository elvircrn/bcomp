#include <vector>
#include <BArgument.h>
#include <FuncCall.h>
#include <algorithm>

std::vector <bompiler::BArgument> bompiler::FuncCall::getArgs(bool reverse) const {
  std::vector<BArgument> args;
  bool fname = true;
  // First child is always the name of the function
  for (auto child : node->getChildren()) {
    if (fname)
      fname = false;
    else
      args.emplace_back(child);
  }
  if (reverse)
    std::reverse(args.begin(), args.end());
  return args;
}
bompiler::FuncCall::FuncCall(bompiler::PNode *_node) : node(_node) {

}
bompiler::FuncCall::FuncCall() : node(nullptr) {

}
