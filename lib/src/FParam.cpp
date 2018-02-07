#include "FParam.h"

using namespace bompiler;

FParam::FParam(bompiler::PNode *_parent,
               const std::__cxx11::basic_string<wchar_t> &_name,
               const std::vector <std::wstring> &_args) : PNode(_parent, _name, _args) {}

FParam::FParam(PNode *_parent, const std::wstring &paramName) : PNode(_parent, L"FUNCDEF") {
    attrs.push_back(paramName);
}
