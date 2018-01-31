#include <vector>
#include <BArgument.h>
#include <FuncCall.h>
#include <algorithm>
#include <unordered_set>

std::vector <bompiler::BArgument*> bompiler::FuncCall::getArgs(bool reverse) const {
  std::vector<BArgument*> args;
  bool fname = true;
  // First child is always the name of the function
  for (auto child : children) {
    if (fname)
      fname = false;
    else
      args.emplace_back(child->as<BArgument>());
  }
  if (reverse)
    std::reverse(args.begin(), args.end());
  return args;
}

bompiler::FuncCall::FuncCall(bompiler::PNode *_parent, const wstring &_name, const vector<wstring> &_args) : PNode(
    _parent,
    _name,
    _args) {

}
