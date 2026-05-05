#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "compiler_utils.h"

/* Walks the AST and performs:
   - Type checking (with coercion hints)
   - Undeclared variable detection (with "did you mean?" suggestions)
   - Control-flow checks (break/continue only inside loops)
   - Function return-type validation
   Returns the DataType of the expression, or TYPE_UNKNOWN on error. */
DataType type_check(ASTNode *node);

/* Constant folding: walks the AST in-place and collapses
   constant sub-expressions. Returns the (possibly new) node. */
ASTNode *constant_fold(ASTNode *node);

/* TAC generation: walks the folded AST and emits TAC instructions.
   Returns the name of the result variable/temp, or NULL. */
char *codegen(ASTNode *node);

#endif
