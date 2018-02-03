#include "Int.h"

#include <sstream>
#include <string>

bompiler::Int::Int(bompiler::PNode *_parent,
                   const wstring &_name,
                   const vector<wstring> &_args) : PNode(_parent, _name, _args) {
  // args[0] Contains the actual integer value
  val = std::stoi(attrs[0]);
}

bompiler::Int::Int(PNode *_parent, int _val) : PNode(_parent, L"INT") {
  attrs.push_back(std::to_wstring(_val));
  val = _val;
}
