#include "ParseTree.h"
#include "While.h"

using namespace bompiler;

While::While(bompiler::PNode *_parent,
             const wstring &_name,
             const std::vector <std::wstring> &_args) : PNode(_parent, _name, _args) {

}
#include <iostream>
void While::setLabels(const std::wstring &_loopLabel, const std::wstring &_breakLabel) {
  loopLabel = _loopLabel;
  breakLabel = _breakLabel;
  std::wcout << L"WOT\n";
}
