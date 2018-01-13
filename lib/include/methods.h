#include <string>
#include <cstring>

std::wstring AST() {
  return _ast.str();
}

bool IsDeclaredLocal(Name name1) {
  std::wstring name = std::wstring(name1);
  std::string::size_type found;
  std::wstring decls[4] = {L"EXTRN", L"LARRDEF", L"LVARDEF", L"FPARAM"};
  for (int i = 0; i < 4; i++) {
    found = ParseList.find(L"(" + decls[i] + L" " + name + L" ", scopepos);
    if (found != std::string::npos)
      return true;
  }
  return false;
}

bool IsAuto(Name name1) {
  std::wstring name = std::wstring(name1);
  std::string::size_type found;
  std::wstring decls[3] = {L"LARRDEF", L"LVARDEF", L"FPARAM"};
  for (int i = 0; i < 3; i++) {
    found = ParseList.find(L"(" + decls[i] + L" " + name + L" ", scopepos);
    if (found != std::string::npos)
      return true;
  }
  return false;
}

bool IsDeclaredGlobal(Name name1) {
  std::wstring name = std::wstring(name1);
  std::string::size_type found;
  std::wstring decls[4] = {L"GARRDEF", L"GVARDEF", L"FUNCDEF"};
  for (int i = 0; i < 4; i++) {
    found = ParseList.find(L"(" + decls[i] + L" " + name + L" ", 0);
    if (found != std::string::npos)
      return true;
  }

  return false;
}

void UndecErr(Name name) {
  Name msg;
  wcscpy(msg, L"Undeclared ");
  wcscat(msg, name);
  SemErr(msg);
}

void AlreadyErr(Name name) {
  Name msg;
  wcscpy(msg, L"Already declared ");
  wcscat(msg, name);
  SemErr(msg);
}

std::wstring GetNodeName(int position) {
  wstring NodeName;
  NodeName = L"";
  if (ParseList[position] != '(')
    return L"";
  position++;
  while (ParseList[position] >= 'A' && ParseList[position] <= 'Z') {
    NodeName += ParseList[position];
    position++;
  }
  return NodeName;
}

std::wstring GetElemName(int position, int elemnum) {
  wstring ElemName;
  position = ElemPos(position, elemnum);
  ElemName = L"";
  if (position > 0)
    while (ParseList[position] != ' ' && ParseList[position] != ')') {
      ElemName += ParseList[position];
      position++;
    }
  return ElemName;
}

int ElemPos(int position, int elemnum) {
  int currel, brlevel;
  currel = 0;
  position++;
  while (ParseList[position] >= 'A' && ParseList[position] <= 'Z')
    position++;
  for (;;) {
    while (ParseList[position] == ' ')
      position++;
    currel++;
    if (currel == elemnum && ParseList[position] != ')')
      return position;
    switch (ParseList[position]) {
    case '(':
      brlevel = 1;
      position++;
      while (brlevel != 0) {
        while (ParseList[position] != '(' && ParseList[position] != '`' &&
            ParseList[position] != ')')
          position++;
        switch (ParseList[position]) {
        case '(':
          brlevel++;
          position++;
          break;
        case ')':
          brlevel--;
          position++;
          break;
        case '`':
          do {
            position++;
          } while (ParseList[position] != '`');
          position++;
          break;
        }
      }
      break;
    case ')':
      return -1;
      break;
    case '`':
      do {
        position++;

      } while (ParseList[position] != '`');
      position++;
      break;
    default:
      while (ParseList[position] != '(' && ParseList[position] != ' ' &&
          ParseList[position] != ')')
        position++;
    }
  }
}

// TODO: L"VAR", L"INDEX" ili L"PTR"
bool Assignable(int position);

