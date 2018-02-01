#include "util.h"
#include "Bompiler.h"
#include "Scanner.h"
#include "Parser.h"
#include "BFunction.h"
#include "CodeGen.h"
#include "names.h"

#include <FuncCall.h>
#include <Var.h>

using namespace bompiler;

// TODO: Hopelessly in need of refactoring
bool bompiler::Bompiler::compile(const std::wstring &filePath) {

}

std::wstring bompiler::Bompiler::astStr() {
  return parser.AST();
}

bompiler::Bompiler::Bompiler(const std::wstring &filePath) : scanner(filePath.c_str()),
                                                             parser(&scanner) {
  parser.Parse();
  if (parser.errors->count == 0)
    state = State::SUCCESS;
  else
    state = State::FAIL;
}

bompiler::Bompiler::Bompiler(const unsigned char *buf, int len) : scanner(buf, len),
                                                                  parser(&scanner) {
  parser.Parse();
  if (parser.errors->count) {
    state = State::FAIL;
    return;
  }

  std::wcout << L"Expression:\n" << parser.ParseList << endl;

  pt = ParseTree(parser.ParseList, 0);
  pt.print();
  std::wcout << endl;
  compile(pt.getRoot());
  generateDataSection();
  generateHeader();

  state = State::SUCCESS;
}

bompiler::Bompiler::State bompiler::Bompiler::getState() {
  return state;
}

void Bompiler::compile() {

}

void Bompiler::compile(PNode *node) {
  if (!node) {
    std::wcout << L"WTF\n";
    return;
  }
  wstring nodename = node->getName(), elemname;
  int par, z, q;
  std::wcout << L"NODENAME: " << nodename << '\n';
  par = 1;
  if (nodename == L"ADD") {
    compile(node->getChild(0));
    if (node->getChild(1)->getName() == L"INT") {
      _asmOutput << L" ADD EAX," << node->getChild(1)->getAttr(0) << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      auto var = node->getChild(1)->as<Var>();
      _asmOutput << L" ADD EAX,[" << genStackAddr(var) << "]" << endl;
    } else {
      _asmOutput << L" PUSH EAX";
      compile(node->getChild(1));
      _asmOutput << L" POP EBX";
      _asmOutput << L" ADD EAX,EBX" << endl;
    }
  } else if (nodename == L"ADDMOV") {
  } else if (nodename == L"ADDROF") {
  } else if (nodename == L"AND") {
    compile(node->getChild(0));
    if (node->getChild(1)->getName() == L"INT") {
      _asmOutput << L" AND EAX," << node->getChild(1)->getAttr(0) << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      _asmOutput << L" AND EAX,[" << node->getChild(1)->getAttr(0) << "]" << endl;
    } else {
      _asmOutput << L" PUSH EAX";
      compile(node->getChild(1));
      _asmOutput << L" POP EBX";
      _asmOutput << L" AND EAX,EBX" << endl;
    }
  } else if (nodename == L"ANDMOV") {
  } else if (nodename == L"ARG") {
  } else if (nodename == L"ASIZE") {
  } else if (nodename == L"BLOCK") {
    for (const auto &child : node->getChildren())
      compile(child);
  } else if (nodename == L"BREAK") {
  } else if (nodename == L"B") {
    for (const auto &child : node->getChildren())
      compile(child);
  } else if (nodename == L"CHAR") {
  } else if (nodename == L"CONDEXPR") {
  } else if (nodename == L"CONTINUE") {
  } else if (nodename == L"DECLSTAT") {
    for (const auto &child : node->getChildren())
      compile(child);
  } else if (nodename == L"DIVMOV") {
  } else if (nodename == L"EQU") {
  } else if (nodename == L"EXTRN") {
  } else if (nodename == L"FHEADER") {
  } else if (nodename == L"FPARAM") {
  } else if (nodename == L"FUNCCALL") {
    std::wstring funcName = node->getChild(0)->getAttr(0);
    auto fcall = node->as<FuncCall>();
    // TODO: Simplify!
    auto f = objs.findFunction(fcall);
    if (f || objs.isStdLibFunction(funcName)) { 
      if (objs.isStdLibFunction(funcName))
        objs.invokedLibraryFunctions.insert(funcName);

      // Push parms onto the stack in reverse order
      for (const auto& arg : fcall->getArgs(true)) {
        std::wcout << L"ARG type: " << arg->getName() << '\n';
        if (arg->argType() == L"VAR") {
          _asmOutput << L" PUSH DWORD [" << genStackAddr(arg->getVar()) << L"]\n";
        } else if (arg->argType() == L"INT") {
          _asmOutput << L" PUSH [" << arg->getVar()->getAttr(0) << L"]\n";
        } else if (arg->argType() == L"STRING") {
          // TODO: Implement string passing
          auto literalNode = arg->getChild(0);
          _asmOutput << L" PUSH DWORD " << objs.getOrCreateLiteral(literalNode->getAttr(0)) << endl;
          // compile(arg.getNode()->getChild(0));
        }
      }
      _asmOutput << L" CALL " << funcName << '\n';

      // Caller clean-up convention, remove parameters from stack
      // Result is in eax
      _asmOutput << L" ADD ESP," << fcall->nargs() * 4 << endl;

    } else {
    
//      throw L"Error, functio name " + f->name() + L" not found";
    }
  } else if (nodename == L"FUNCDEF") {
    auto f = node->as<BFunction>();
    objs.addFunction(f);
    // TODO: Check why public doesn't work
    _asmOutput << L" global " << f->name() << endl;
    _asmOutput << f->name() << ":" << endl;
    _asmOutput << L" PUSH EBP" << endl
               << L" MOV EBP,ESP" << endl
               << L" SUB ESP," << f->name() << L"_len" << endl;
    for (const auto & child : node->getChildren())
      compile(child);
    header << L"%define " << f->name() << L"_len " << f->getBlock()->varCnt() * 4 << endl;
    // Standard exit sequence
    _asmOutput << L" MOV ESP,EBP" << endl
               << L" POP EBP" << endl
               << L" RET 0" << endl;  // RET 0 because the caller cleans up the stack
  } else if (nodename == L"GARRDEF") {
  } else if (nodename == L"GOTO") {
    std::wstring labelName = node->getAttr(0);
    if (!objs.labelExists(labelName)) {
      state = State::FAIL;
      return;
    }
    _asmOutput << L" jmp " + GOTO_PREFIX + node->getAttr(0) << L":\n";
  } else if (nodename == L"GREATEREQUTHAN") {
  } else if (nodename == L"GREATERTHAN") {
  } else if (nodename == L"GVARDEF") {
  } else if (nodename == L"IFELSE") {
  } else if (nodename == L"IF") {
  } else if (nodename == L"INDEX") {
  } else if (nodename == L"INIT") {
  } else if (nodename == L"INT") {
    _asmOutput << L" MOV EAX," << node->getAttrs()[0] << endl;
  } else if (nodename == L"ISEQUMOV") {
  } else if (nodename == L"ISGREATEREQUMOV") {
  } else if (nodename == L"ISGREATERMOV") {
  } else if (nodename == L"ISLESSEQUMOV") {
  } else if (nodename == L"ISLESSMOV") {
  } else if (nodename == L"ISNEQUMOV") {
  } else if (nodename == L"LABEL") {
    // TODO: Test
    std::wstring labelName = node->getAttr(0);
    if (objs.labelExists(labelName)) {
      state = State::FAIL;
      return;
    }
    _asmOutput << L" " << GOTO_PREFIX << labelName << L":\n";
    objs.labels.emplace_back(node);
  } else if (nodename == L"LARRDEF") {
  } else if (nodename == L"LESSEQUTHAN") {
  } else if (nodename == L"LESSTHAN") {
  } else if (nodename == L"LSHIFT") {
  } else if (nodename == L"LSHIFTMOV") {
  } else if (nodename == L"LVARDEF") {
    // header << L"%define " << f.name() + L"_" + varName << L" EBP - " << varId * 4 << endl;
  } else if (nodename == L"MOD") {
  } else if (nodename == L"MODMOV") {
  } else if (nodename == L"MOV") {
    auto lhs = node->getChild(0);
    auto rhs = node->getChild(1);
    if (lhs->getName() == L"VAR") {
      if (rhs->getName() == L"INT") {
        _asmOutput << L" MOV DWORD [" << genStackAddr(lhs->as<Var>()) << L"],"
                   << rhs->getAttr(0) << endl;
      } else if (rhs->getName() == L"VAR") {
        _asmOutput << L" MOV EAX, [" << genStackAddr(lhs->as<Var>()) << L"]" << endl;
        _asmOutput << L" MOV [" << genStackAddr(rhs->as<Var>()) << L"],EAX" << endl;
      } else {
        compile(rhs);
        _asmOutput << L" MOV [" << lhs->getAttr(0) << L"],EAX" << endl;
      }
    } else {
      if (rhs->getName() == L"INT") {
        compile(lhs);
        _asmOutput << L" MOV DWORD [EBX]," << rhs->getAttr(0) << endl;
      } else if (rhs->getName() == L"VAR") {
        compile(lhs);
        _asmOutput << L" MOV EAX, [" << rhs->getAttr(0) << L"]" << endl;
        _asmOutput << L" MOV [EBX],EAX" << endl;
      } else {
        compile(rhs);
        _asmOutput << L" PUSH EAX" << endl;
        compile(lhs);
        _asmOutput << L" POP EAX" << endl;
        _asmOutput << L" MOV [EBX],EAX" << endl;
      }
    }
  } else if (nodename == L"MUL") {
    compile(node->getChild(0));
    if (node->getChild(1)->getName() == L"INT") {
      _asmOutput << L" MUL EAX," << node->getChild(1)->getAttr(0) << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      _asmOutput << L" MUL EAX,[" << genStackAddr(node->getChild(1)->as<Var>()) << "]" << endl;
    } else {
      _asmOutput << L" PUSH EAX";
      compile(node->getChild(1));
      _asmOutput << L" POP EBX";
      _asmOutput << L" MUL EAX,EBX" << endl;
    }
  } else if (nodename == L"MULTMOV") {
  } else if (nodename == L"NEQU") {
  } else if (nodename == L"ONUMBER") {
  } else if (nodename == L"OR") {
    compile(node->getChild(0));
    if (node->getChild(1)->getName() == L"INT") {
      _asmOutput << L" OR EAX," << node->getChild(1)->getAttr(0) << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      _asmOutput << L" OR EAX,[" << genStackAddr(node->getChild(1)->as<Var>()) << "]" << endl;
    } else {
      _asmOutput << L" PUSH EAX";
      compile(node->getChild(1));
      _asmOutput << L" POP EBX";
      _asmOutput << L" OR EAX,EBX" << endl;
    }
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
    auto litMacro = objs.getOrCreateLiteral(node->getAttr(0));
    std::wcout << L"LIT MACRO: " << litMacro << L" " << node->getAttr(0) << L"\n";
  } else if (nodename == L"SUB") {
    // TODO: Check for commutativity
    compile(node->getChild(0));
    if (node->getChild(1)->getName() == L"INT") {
      _asmOutput << L" SUB EAX," << node->getChild(1)->getAttr(0) << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      _asmOutput << L" SUB EAX,[" << genStackAddr(node->getChild(1)->as<Var>()) << "]" << endl;
    } else {
      _asmOutput << L" PUSH EAX";
      compile(node->getChild(1));
      _asmOutput << L" POP EBX";
      _asmOutput << L" SUB EAX,EBX" << endl;
    }
  } else if (nodename == L"SUBMOV") {
  } else if (nodename == L"SWITCH") {
  } else if (nodename == L"UMINUS") {
  } else if (nodename == L"UNEG") {
  } else if (nodename == L"UNOT") {
  } else if (nodename == L"UPLUS") {
  } else if (nodename == L"VAR") {
    // TODO: Handle var not found
    auto var = reinterpret_cast<Var*>(node);
    _asmOutput << L" MOV EAX, [" << genStackAddr(var) << "]" << endl;
  } else if (nodename == L"WHILE") {
  } else if (nodename == L"XOR") {
    compile(node->getChild(0));
    if (node->getChild(1)->getName() == L"INT") {
      _asmOutput << L" XOR EAX," << node->getChild(1)->getAttr(0) << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      _asmOutput << L" XOR EAX,[" << node->getChild(1)->getAttr(0) << "]" << endl;
    } else {
      _asmOutput << L" PUSH EAX";
      compile(node->getChild(1));
      _asmOutput << L" POP EBX";
      _asmOutput << L" XOR EAX,EBX" << endl;
    }
  } else if (nodename == L"XORMOV ") {
  }
}

std::wstring Bompiler::asmStr() { 
  return header.str() + data.str() + L"\nsection .text\n" + _asmOutput.str();
}

void Bompiler::generateDataSection() {
  data << L" section .data\n";
  for (const auto& stringLiteral : objs.getStringLiterals()) {
    data << stringLiteral.second << L": db " << stringLiteral.first << L", 0\n";
  }
}

void Bompiler::generateHeader() {
  for (const auto& libFun : objs.invokedLibraryFunctions)
    header << L" extern " << libFun << L"\n";
  header << L" global main\n";
}

