#include "util.h"
#include "TreeOpt.h"
#include "Bompiler.h"
#include "Scanner.h"
#include "Parser.h"
#include "BFunction.h"
#include "CodeGen.h"
#include "names.h"

#include <FuncCall.h>
#include <Var.h>
#include <fstream>
#include <While.h>

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
  std::wcout << L"Parser error cnt: " << parser.errors->count << '\n';
  if (parser.errors->count) {
    state = State::FAIL;
    return;
  }

  std::wcout << parser.ParseList << '\n';

  std::wcout << L"Expression:\n" << parser.ParseList << endl;

  pt = ParseTree(parser.ParseList, 0);
  std::wcout << endl;
  compile(pt.getRoot());
  pt.print();
  generateDataSection();
  generateHeader();

  state = State::SUCCESS;
  std::wofstream fout("asmbuff.asm", ios_base::out);
  fout << asmStr() << '\n';
}

bompiler::Bompiler::State bompiler::Bompiler::getState() {
  return state;
}

void Bompiler::compile() {

}

void Bompiler::genArithOp(PNode *node, const std::wstring &op) {
  compile(node->getChild(0));
  if (node->getChild(1)->getName() == L"INT") {
    _asmOutput << L" " << op << " EAX," << node->getChild(1)->getAttr(0) << endl;
  } else if (node->getChild(1)->getName() == L"VAR") {
    auto var = node->getChild(1)->as<Var>();
    _asmOutput << L" " << op << " EAX,[" << genStackAddr(var) << "]" << endl;
  } else {
    _asmOutput << L" PUSH EAX" << endl;
    compile(node->getChild(1));
    _asmOutput << L" POP EBX" << endl;
    _asmOutput << L" ADD EAX,EBX" << endl;
  }
}

void Bompiler::compile(PNode *node) {
  if (!node) {
    std::wcout << L"WTF\n";
    return;
  }
  wstring nodename = node->getName(), elemname;
  int par, z, q;
  par = 1;
  if (nodename == L"ADD") {
    genArithOp(node, nodename);
  } else if (nodename == L"ADDMOV") {
  } else if (nodename == L"ADDROF") {
    auto var = node->getChild(0);
    _asmOutput << L" LEA EAX, " << deref(genStackAddr(var->as<Var>())) << endl;
    // _asmOutput << L" MOV EAX, " << genStackAddr(var->as<Var>()) << endl;
  } else if (nodename == L"AND") {
    genArithOp(node, nodename);
  } else if (nodename == L"ANDMOV") {
  } else if (nodename == L"ARG") {
    auto arg = node->as<BArgument>();
    if (arg->argType() == L"VAR") {
      _asmOutput << L" PUSH DWORD [" << genStackAddr(arg->getVal()->as<Var>()) << L"]\n";
    } else if (arg->argType() == L"INT") {
      _asmOutput << L" PUSH " << arg->getVal()->as<Int>()->getVal() << L"\n";
    } else if (arg->argType() == L"STRING") {
      // TODO: Test string passing
      auto literalNode = arg->getChild(0);
      _asmOutput << L" PUSH DWORD " << objs.getOrCreateLiteral(literalNode->getAttr(0)) << endl;
      // compile(arg.getNode()->getChild(0));
    } else {
      std::wcout << arg->getName() << '\n';
      compile(arg->getVal());
      _asmOutput << L" PUSH EAX" << endl;
    }
  } else if (nodename == L"ASIZE") {
  } else if (nodename == L"BLOCK") {
    for (const auto &child : node->getChildren())
      compile(child);
  } else if (nodename == L"BREAK") {
    auto whileNode = node->getAncestorByName(L"WHILE");

    // Error: If node is null, then continue is not valid
    if (!whileNode) {
      // TODO: Do error handling here
    }

    _asmOutput << L" GOTO " << whileNode->as<While>()->getBreakLabel() << '\n';
  } else if (nodename == L"B") {
    for (const auto &child : node->getChildren())
      compile(child);
  } else if (nodename == L"CHAR") {
    // TODO: Chars are converted to int during construction of ParseTree, so this branch
    // never gets executed.
  } else if (nodename == L"CONDEXPR") {
  } else if (nodename == L"CONTINUE") {
    auto whileNode = node->getAncestorByName(L"WHILE");

    // Error: If node is null, then continue is not valid
    if (!whileNode) {
      // TODO: Do error handling here
    }

    _asmOutput << L" GOTO " << whileNode->as<While>()->getLoopLabel() << '\n';
  } else if (nodename == L"DECLSTAT") {
    for (const auto &child : node->getChildren())
      compile(child);
  } else if (nodename == L"DIV") {
    compile(node->getChild(0));
    if (node->getChild(1)->getName() == L"INT") {
      _asmOutput << L" MOV EDX, 0" << endl
                 << L" MOV ECX, " << node->getChild(1)->getAttr(0) << endl
                 << L" DIV ECX" << endl; 
    } else if (node->getChild(1)->getName() == L"VAR") {
      _asmOutput << L" MOV EDX, 0" << endl
                 << L" DIV DWORD [" << genStackAddr(node->getChild(1)->as<Var>()) << "]" << endl;
    } else {
      _asmOutput << L" PUSH EAX" << endl;
      compile(node->getChild(1));
      _asmOutput << L" POP EBX" << endl;
      _asmOutput << L" DIV EBX" << endl;
    }
  } else if (nodename == L"DIVMOV") {
  } else if (nodename == L"EQU") {
    compile(node->getChild(0));
    objs.createAndGetLabel();
    if (node->getChild(1)->getName() == L"INT") {
      auto condFalse = objs.createAndGetLabel();
      auto condTrue = objs.createAndGetLabel();
      _asmOutput << L" CMP EAX," << node->getChild(1)->getAttr(0) << endl
                 << L" JNE " << condFalse << endl
                 << L" XOR EAX, EAX" << endl
                 << L" INC EAX" << endl
                 << L" JMP " << condTrue << endl
                 << condFalse << ':' << endl
                 << L" XOR EAX, EAX" << endl
                 << condTrue << ':' << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      auto var = node->getChild(1)->as<Var>();
      auto condTrue = objs.createAndGetLabel();
      auto condFalse = objs.createAndGetLabel();
      _asmOutput << L" CMP EAX," << deref(genStackAddr(var)) << endl
                 << L" JNE " << condFalse << endl
                 << L" XOR EAX, EAX" << endl
                 << L" INC EAX" << endl
                 << L" JMP " << condTrue << endl
                 << condFalse << ':' << endl
                 << L" XOR EAX, EAX" << endl
                 << condTrue << ':' << endl;
    } else {
      _asmOutput << L" PUSH EAX" << endl;
      compile(node->getChild(1));
      _asmOutput << L" POP EBX" << endl
                 << L" ADD EAX,EBX" << endl;
    } 
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
      // TODO: Consider moving this logic down the tree
      for (const auto &arg : fcall->getArgs(true))
        compile(arg);

      // Caller clean-up convention, remove parameters from stack
      // Result is in eax
      _asmOutput << L" CALL " << funcName << '\n';
      _asmOutput << L" ADD ESP," << fcall->nargs() * 4 << endl;
    } else {
      // TODO: Error handle function not found
      // throw L"Error, functio name " + f->name() + L" not found";
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

    for (const auto &child : node->getChildren())
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
    compile(node->getChild(0));
    objs.createAndGetLabel();
    if (node->getChild(1)->getName() == L"INT") {
      auto condFalse = objs.createAndGetLabel();
      auto condTrue = objs.createAndGetLabel();
      _asmOutput << L" CMP EAX," << node->getChild(1)->getAttr(0) << endl
                 << L" JLE " << condFalse << endl
                 << L" XOR EAX, EAX" << endl
                 << L" INC EAX" << endl
                 << L" JMP " << condTrue << endl
                 << condFalse << ':' << endl
                 << L" XOR EAX, EAX" << endl
                 << condTrue << ':' << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      auto var = node->getChild(1)->as<Var>();
      auto condTrue = objs.createAndGetLabel();
      auto condFalse = objs.createAndGetLabel();
      _asmOutput << L" CMP EAX," << deref(genStackAddr(var)) << endl
                 << L" JLE " << condFalse << endl
                 << L" XOR EAX, EAX" << endl
                 << L" INC EAX" << endl
                 << L" JMP " << condTrue << endl
                 << condFalse << ':' << endl
                 << L" XOR EAX, EAX" << endl
                 << condTrue << ':' << endl;
    } else {
      _asmOutput << L" PUSH EAX" << endl;
      compile(node->getChild(1));
      _asmOutput << L" POP EBX" << endl
                 << L" ADD EAX,EBX" << endl;
    }
  } else if (nodename == L"GVARDEF") {
  } else if (nodename == L"IF") { 
    // The condition
    compile(node->getChild(0)); 
    auto label = objs.createAndGetLabel(); 
    _asmOutput << " CMP EAX, 0\n"
               << " JZ " << label << '\n';
    // Code block to be executed if the condition is true
    compile(node->getChild(1));
    _asmOutput << label << ":\n";
  } else if (nodename == L"IFELSE") {
    // The condition
    compile(node->getChild(0)); 
    auto label = objs.createAndGetLabel(); 
    _asmOutput << " CMP EAX, 0\n"
               << " JZ " << label << '\n';
    // Code block to be executed if the condition is true
    compile(node->getChild(1));
    _asmOutput << label << ":\n";
    // Code block to be executed if the condition is false
    compile(node->getChild(2));
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
    compile(node->getChild(0));
    objs.createAndGetLabel();
    if (node->getChild(1)->getName() == L"INT") {
      auto condFalse = objs.createAndGetLabel();
      auto condTrue = objs.createAndGetLabel();
      _asmOutput << L" CMP EAX," << node->getChild(1)->getAttr(0) << endl
                 << L" JGE " << condFalse << endl
                 << L" XOR EAX, EAX" << endl
                 << L" INC EAX" << endl
                 << L" JMP " << condTrue << endl
                 << condFalse << ':' << endl
                 << L" XOR EAX, EAX" << endl
                 << condTrue << ':' << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      auto var = node->getChild(1)->as<Var>();
      auto condTrue = objs.createAndGetLabel();
      auto condFalse = objs.createAndGetLabel();
      _asmOutput << L" CMP EAX," << deref(genStackAddr(var)) << endl
                 << L" JGE " << condFalse << endl
                 << L" XOR EAX, EAX" << endl
                 << L" INC EAX" << endl
                 << L" JMP " << condTrue << endl
                 << condFalse << ':' << endl
                 << L" XOR EAX, EAX" << endl
                 << condTrue << ':' << endl;
    } else {
      _asmOutput << L" PUSH EAX" << endl;
      compile(node->getChild(1));
      _asmOutput << L" POP EBX" << endl
                 << L" ADD EAX,EBX" << endl;
    }
  } else if (nodename == L"LSHIFT") {
  } else if (nodename == L"LSHIFTMOV") {
  } else if (nodename == L"LVARDEF") {
    // header << L"%define " << f.name() + L"_" + varName << L" EBP - " << varId * 4 << endl;
  } else if (nodename == L"MOD") {
    compile(node->getChild(0));
    if (node->getChild(1)->getName() == L"INT") {
      _asmOutput << L" MOV EDX, 0" << endl
                 << L" MOV ECX, " << node->getChild(1)->getAttr(0) << endl
                 << L" DIV ECX" << endl
                 << L" MOV EAX, EDX" << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      _asmOutput << L" MOV EDX, 0" << endl
                 << L" DIV DWORD [" << genStackAddr(node->getChild(1)->as<Var>()) << "]" << endl
                 << L" MOV EAX, EDX" << endl;
    } else {
      _asmOutput << L" PUSH EAX" << endl;
      compile(node->getChild(1));
      _asmOutput << L" POP EBX" << endl;
      _asmOutput << L" DIV EBX" << endl;
    }
  } else if (nodename == L"MODMOV") {
  } else if (nodename == L"MOV") {
    auto lhs = node->getChild(0);
    auto rhs = node->getChild(1);
    if (lhs->getName() == L"VAR") {
      auto lvar = lhs->as<Var>();
      if (rhs->getName() == L"INT") {
        _asmOutput << L" MOV DWORD [" << genStackAddr(lvar) << L"],"
                   << rhs->getAttr(0) << endl;
      } else if (rhs->getName() == L"VAR") {
        _asmOutput << L" MOV EAX, [" << genStackAddr(lvar) << L"]" << endl;
        _asmOutput << L" MOV [" << genStackAddr(rhs->as<Var>()) << L"],EAX" << endl;
      } else if (rhs->getName() == L"ONUMBER") {
        _asmOutput << L" MOV DWORD [" << genStackAddr(lvar) << L"], 0" << endl;
      }else {
        compile(rhs);
        _asmOutput << L" MOV [" << genStackAddr(lvar) << L"],EAX" << endl;
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
      _asmOutput << L" MUL " << node->getChild(1)->getAttr(0) << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      _asmOutput << L" MUL DWORD [" << genStackAddr(node->getChild(1)->as<Var>()) << "]" << endl;
    } else {
      _asmOutput << L" PUSH EAX" << endl;
      compile(node->getChild(1));
      _asmOutput << L" POP EBX" << endl;
      _asmOutput << L" MUL EBX" << endl;
    }
  } else if (nodename == L"MULTMOV") {
  } else if (nodename == L"NEQU") {
    compile(node->getChild(0));
    objs.createAndGetLabel();
    if (node->getChild(1)->getName() == L"INT") {
      auto condFalse = objs.createAndGetLabel();
      auto condTrue = objs.createAndGetLabel();
      _asmOutput << L" CMP EAX," << node->getChild(1)->getAttr(0) << endl
                 << L" JE " << condFalse << endl
                 << L" XOR EAX, EAX" << endl
                 << L" INC EAX" << endl
                 << L" JMP " << condTrue << endl
                 << condFalse << ':' << endl
                 << L" XOR EAX, EAX" << endl
                 << condTrue << ':' << endl;
    } else if (node->getChild(1)->getName() == L"VAR") {
      auto var = node->getChild(1)->as<Var>();
      auto condTrue = objs.createAndGetLabel();
      auto condFalse = objs.createAndGetLabel();
      _asmOutput << L" CMP EAX," << deref(genStackAddr(var)) << endl
                 << L" JE " << condFalse << endl
                 << L" XOR EAX, EAX" << endl
                 << L" INC EAX" << endl
                 << L" JMP " << condTrue << endl
                 << condFalse << ':' << endl
                 << L" XOR EAX, EAX" << endl
                 << condTrue << ':' << endl;
    } else {
      _asmOutput << L" PUSH EAX" << endl;
      compile(node->getChild(1));
      _asmOutput << L" POP EBX" << endl
                 << L" ADD EAX,EBX" << endl;
    } 
  } else if (nodename == L"ONUMBER") {
  } else if (nodename == L"OR") {
    genArithOp(node, nodename);
  } else if (nodename == L"ORMOV") {
  } else if (nodename == L"POSTDEC") {
    auto var = node->getChild(0)->as<Var>();
    _asmOutput << " MOV EAX, DWORD " << deref(genStackAddr(var)) << endl
               << " DEC DWORD " << deref(genStackAddr(var)) << endl;
  } else if (nodename == L"POSTINC") {
    auto var = node->getChild(0)->as<Var>();
    _asmOutput << " MOV EAX, DWORD " << deref(genStackAddr(var)) << endl
               << " INC DWORD " << deref(genStackAddr(var)) << endl;
  } else if (nodename == L"PREDEC") {
    auto var = node->getChild(0)->as<Var>();
    _asmOutput << " DEC DWORD " << deref(genStackAddr(var)) << endl;
  } else if (nodename == L"PREINC") {
    auto var = node->getChild(0)->as<Var>();
    _asmOutput << " INC DWORD " << deref(genStackAddr(var)) << endl
               << " MOV EAX, DWORD " << deref(genStackAddr(var)) << endl;
  } else if (nodename == L"PTR") {
  } else if (nodename == L"RETURN") {
    _asmOutput << L" MOV ESP,EBP" << endl
               << L" POP EBP" << endl
               << L" RET 0" << endl;  // RET 0 because the caller cleans up the stack
  } else if (nodename == L"RETURNPARAM") {
    // TODO: Figure out a more generic way to do this
    auto param = node->getChild(0);
    compile(param);
    _asmOutput << L" MOV ESP,EBP" << endl
               << L" POP EBP" << endl
               << L" RET 0" << endl;  // RET 0 because the caller cleans up the stack
  } else if (nodename == L"RSHIFT") {
  } else if (nodename == L"RSHIFTMOV") {
  } else if (nodename == L"SAMEAS") {
  } else if (nodename == L"STRING") {
    auto litMacro = objs.getOrCreateLiteral(node->getAttr(0));
    std::wcout << L"LIT MACRO: " << litMacro << L" " << node->getAttr(0) << L"\n";
  } else if (nodename == L"SUB") {
    genArithOp(node, nodename);
  } else if (nodename == L"SUBMOV") {
  } else if (nodename == L"SWITCH") {
  } else if (nodename == L"UMINUS") {
  } else if (nodename == L"UNEG") {
  } else if (nodename == L"UNOT") {
  } else if (nodename == L"UPLUS") {
  } else if (nodename == L"VAR") {
    // TODO: Handle var not found
    auto var = reinterpret_cast<Var *>(node);
    _asmOutput << L" MOV EAX, [" << genStackAddr(var) << "]" << endl;
  } else if (nodename == L"WHILE") { 
    auto condition = node->getChild(0);
    auto block     = node->getChild(1);

    auto loopLabel  = objs.createAndGetLabel();
    auto breakLabel = objs.createAndGetLabel();

    node->as<While>()->setLabels(loopLabel, breakLabel);

    _asmOutput << loopLabel << L":\n";

    // After compiling the condition node, the condition result is now in EAX
    compile(condition);
    _asmOutput << " CMP EAX, 0\n"
               << " JZ " << breakLabel << '\n';

    compile(block);

    _asmOutput << " JMP " << loopLabel << '\n';

    _asmOutput << breakLabel << L":\n";
  } else if (nodename == L"XOR") {
    genArithOp(node, nodename);
  } else if (nodename == L"XORMOV ") {
  }
}

std::wstring Bompiler::asmStr() {
  return header.str() + data.str() + L"\nsection .text\n" + _asmOutput.str();
}

void Bompiler::generateDataSection() {
  data << L" section .data\n";
  for (const auto &stringLiteral : objs.getStringLiterals()) {
    data << stringLiteral.second << L": db " << stringLiteral.first << L", 0\n";
  }
}

void Bompiler::generateHeader() {
  for (const auto &libFun : objs.invokedLibraryFunctions)
    header << L" extern " << libFun << L"\n";
  header << L" global main\n";
}

