#ifndef BOMPILER_OBJECTS_H
#define BOMPILER_OBJECTS_H

#include "ParseTree.h"
#include "BFunction.h"
#include "optional.hpp"
#include "FuncCall.h"

#include <vector>


namespace bompiler {
class Objects {
  std::vector<BFunction> functions;
public:
  std::vector<PNode*> labels;

  bool labelExists(const std::wstring &label) const;

  bompiler::BFunction& addFunction(const bompiler::BFunction &f);

  std::experimental::optional<BFunction&> findFunction(const bompiler::FuncCall &fcall);

};
}

#endif //BOMPILER_OBJECTS_H
