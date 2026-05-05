#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler_utils.h"
#include "semantic.h"

extern int yyparse();
extern ASTNode *root;

int main(int argc, char *argv[]) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║         Mini Compiler v2.0           ║\n");
    printf("║  Lexer · Parser · Semantic · TAC     ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    /* Initialise */
    push_scope();   /* global scope */
    tac_init();

    printf("Enter program (Ctrl+D when done):\n");
    printf("─────────────────────────────────\n");

    if (yyparse() != 0 || error_count > 0) {
        if (error_count > 0)
            fprintf(stderr, "\n%d error(s) found during parsing. "
                            "Please fix them and rerun.\n", error_count);
        return 1;
    }

    printf("\n✓ Parsing complete — no syntax errors.\n\n");

    /* ── Symbol table ── */
    print_symtab();

    /* ── AST ── */
    printf("=== Abstract Syntax Tree ===\n");
    print_ast(root, 0);
    printf("════════════════════════════\n\n");

    /* ── Constant folding ── */
    printf("=== Constant Folding Pass ===\n");
    int before_errors = error_count;
    root = constant_fold(root);
    if (error_count == before_errors)
        printf("  (no constant-fold warnings)\n");
    printf("═════════════════════════════\n\n");

    /* ── Semantic analysis (type checking) ── */
    printf("=== Semantic Analysis ===\n");
    before_errors = error_count;
    type_check(root);
    if (error_count == before_errors)
        printf("  ✓ No type errors.\n");
    else
        printf("  %d semantic error(s) found.\n", error_count - before_errors);
    printf("═════════════════════════\n\n");

    if (error_count > 0) {
        fprintf(stderr, "Compilation failed with %d error(s).\n", error_count);
        return 1;
    }

    /* ── TAC code generation ── */
    codegen(root);
    print_tac();

    printf("✓ Compilation successful.\n");

    pop_scope(); /* global scope */
    return 0;
}
