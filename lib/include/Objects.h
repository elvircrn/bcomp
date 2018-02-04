#ifndef BOMPILER_OBJECTS_H
#define BOMPILER_OBJECTS_H

#include "ParseTree.h"
#include "BFunction.h"
#include "optional.hpp"
#include "FuncCall.h"
#include "names.h"

#include <vector>
#include <map>
#include <set>

namespace bompiler {
class Objects {
  std::vector<BFunction*> functions;
  std::map<std::wstring, std::wstring> stringLiterals;
  std::set<std::wstring> libraryFunctions = { L"printf" };
  int genLabelCnt;

public:
  std::set<std::wstring> invokedLibraryFunctions;
  std::vector<PNode*> labels; 

  Objects();

  bool labelExists(const std::wstring &label) const; 
  bompiler::BFunction* addFunction(bompiler::BFunction *f); 
  bompiler::BFunction* findFunction(bompiler::FuncCall *fcall); 
  std::wstring getOrCreateLiteral(const std::wstring&); 
  std::wstring createAndGetLabel(); 
  inline std::wstring getLastLabel() const {
    return bompiler::LABEL_PREFIX + std::to_wstring(genLabelCnt - 1);
  }
  inline std::map<std::wstring, std::wstring> getStringLiterals() const { return stringLiterals; }; 

  // TODO: No idea how to handle this properly, but it works
  inline bool isStdLibFunction(const std::wstring &funcName) const {
    return libraryFunctions.find(funcName) != libraryFunctions.end();
  }
};
}

#endif //BOMPILER_OBJECTS_H
