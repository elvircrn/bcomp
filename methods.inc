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
bool Assignable(int position) { return true; }

void Compile(int position) {
  wstring nodename, elemname;
  int par, z, q;
  nodename = GetNodeName(position);
  par = 1;
  if (nodename == L"ADD") {
    z = ElemPos(position, 1);
    q = ElemPos(position, 2);
    Compile(z);
    if (GetNodeName(q) == L"INT") {
      wcout << L" ADD EAX," << GetElemName(q, 1) << endl;
    } else if (GetNodeName(q) == L"VAR") {
      wcout << L" ADD EAX,[" << GetElemName(q, 1) << "]" << endl;
    } else {
      wcout << L" PUSH EAX";
      Compile(q);
      wcout << L" POP EBX";
      wcout << L" ADD EAX,EBX" << endl;
    }
  } else if (nodename == L"ADDMOV") {
  } else if (nodename == L"ADDROF") {
  } else if (nodename == L"AND") {
  } else if (nodename == L"ANDMOV") {
  } else if (nodename == L"ARG") {
  } else if (nodename == L"ASIZE") {
  } else if (nodename == L"BLOCK") {
    while ((z = ElemPos(position, par)) > 0) {
      Compile(z);
      par++;
    }
  } else if (nodename == L"BREAK") {
  } else if (nodename == L"B") {
    while ((z = ElemPos(position, par)) > 0) {
      Compile(z);
      par++;
    }
  } else if (nodename == L"CHAR") {
  } else if (nodename == L"CONDEXPR") {
  } else if (nodename == L"CONTINUE") {
  } else if (nodename == L"DECLSTAT") {
    while ((z = ElemPos(position, par)) > 0) {
      Compile(z);
      par++;
    }
  } else if (nodename == L"DEFAULT") {
  } else if (nodename == L"DIV") {
  } else if (nodename == L"DIVMOV") {
  } else if (nodename == L"EQU") {
  } else if (nodename == L"EXTRN") {
  } else if (nodename == L"FHEADER") {
  } else if (nodename == L"FPARAM") {
  } else if (nodename == L"FUNCCALL") {
  } else if (nodename == L"FUNCDEF") {
    elemname = GetElemName(position, 1);
    wcout << L" PUBLIC " << elemname << endl;
    wcout << elemname << ":" << endl;
    wcout << L" PUSH EBP" << endl
          << L" MOV EBP,ESP" << endl
          << L" SUB ESP," << elemname << L"_len" << endl;
    Compile(ElemPos(position, 2));
    Compile(ElemPos(position, 3));
    wcout << L" MOV ESP,EBP" << endl << L" RET " << endl;
  } else if (nodename == L"GARRDEF") {
  } else if (nodename == L"GOTO") {
  } else if (nodename == L"GREATEREQUTHAN") {
  } else if (nodename == L"GREATERTHAN") {
  } else if (nodename == L"GVARDEF") {
  } else if (nodename == L"IFELSE") {
  } else if (nodename == L"IF") {
  } else if (nodename == L"INDEX") {
  } else if (nodename == L"INIT") {
  } else if (nodename == L"INT") {
    wcout << L" MOV EAX," << GetElemName(position, 1) << endl;
  } else if (nodename == L"ISEQUMOV") {
  } else if (nodename == L"ISGREATEREQUMOV") {
  } else if (nodename == L"ISGREATERMOV") {
  } else if (nodename == L"ISLESSEQUMOV") {
  } else if (nodename == L"ISLESSMOV") {
  } else if (nodename == L"ISNEQUMOV") {
  } else if (nodename == L"LABEL") {
  } else if (nodename == L"LARRDEF") {
  } else if (nodename == L"LESSEQUTHAN") {
  } else if (nodename == L"LESSTHAN") {
  } else if (nodename == L"LSHIFT") {
  } else if (nodename == L"LSHIFTMOV") {
  } else if (nodename == L"LVARDEF") {
  } else if (nodename == L"MOD") {
  } else if (nodename == L"MODMOV") {
  } else if (nodename == L"MOV") {
    z = ElemPos(position, 1);
    q = ElemPos(position, 2);
    if (GetNodeName(z) == L"VAR") {
      if (GetNodeName(q) == L"INT") {
        wcout << L" MOV DWORD [" << GetElemName(z, 1) << "],"
              << GetElemName(q, 1) << endl;
      } else if (GetNodeName(q) == L"VAR") {
        wcout << L" MOV EAX, [" << GetElemName(q, 1) << "]" << endl;
        wcout << L" MOV [" << GetElemName(z, 1) << "],EAX" << endl;
      } else {
        Compile(q);
        wcout << L" MOV [" << GetElemName(z, 1) << "],EAX" << endl;
      }
    } else {
      if (GetNodeName(q) == L"INT") {
        Compile(z);
        wcout << L" MOV DWORD [EBX]," << GetElemName(q, 1) << endl;
      } else if (GetNodeName(q) == L"VAR") {
        Compile(z);
        wcout << L" MOV EAX, [" << GetElemName(q, 1) << "]" << endl;
        wcout << L" MOV [EBX],EAX" << endl;
      } else {
        Compile(q);
        wcout << L" PUSH EAX" << endl;
        Compile(z);
        wcout << L" POP EAX" << endl;
        wcout << L" MOV [EBX],EAX" << endl;
      }
    }
  } else if (nodename == L"MUL") {
  } else if (nodename == L"MULTMOV") {
  } else if (nodename == L"NEQU") {
  } else if (nodename == L"ONUMBER") {
  } else if (nodename == L"OR") {
  } else if (nodename == L"ORMOV") {
  } else if (nodename == L"POSTDEC") {
  } else if (nodename == L"POSTINC") {
  } else if (nodename == L"PREDEC") {
  } else if (nodename == L"PREINC") {
  } else if (nodename == L"PTR") {
  } else if (nodename == L"RETURN") {
  } else if (nodename == L"RETURNPARAM") {
  } else if (nodename == L"RSHIFT") {
  } else if (nodename == L"RSHIFTMOV") {
  } else if (nodename == L"SAMEAS") {
  } else if (nodename == L"STRING") {
  } else if (nodename == L"SUB") {
  } else if (nodename == L"SUBMOV") {
  } else if (nodename == L"SWITCH") {
  } else if (nodename == L"UMINUS") {
  } else if (nodename == L"UNEG") {
  } else if (nodename == L"UNOT") {
  } else if (nodename == L"UPLUS") {
  } else if (nodename == L"VAR") {
    wcout << L" MOV EAX, [" << GetElemName(position, 1) << "]" << endl;
  } else if (nodename == L"WHILE") {
  } else if (nodename == L"XOR") {
  } else if (nodename == L"XORMOV ") {
  }
}
