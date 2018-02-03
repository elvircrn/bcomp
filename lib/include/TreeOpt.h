/**
 * Used for PraseTree-level optimizations.
 */
#ifndef BOMPILER_TREEOPT_H
#define BOMPILER_TREEOPT_H

#include "ParseTree.h"
#include "Int.h"

namespace bompiler {
ParseTree arithOpt(ParseTree tree);
bool canEval(PNode *node);
PNode* arithOpt(PNode *node);
Int* arithEval(PNode *node);
}

#endif //BOMPILER_TREEOPT_H
