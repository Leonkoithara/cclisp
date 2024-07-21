#ifndef SEMANTIC
#define SEMANTIC

#include <lex.h>

struct ast
{
    struct ast* children;
    struct ast* parent;
    struct ast* sibling;
    char *node_val;
    int node_val_size;
};

typedef struct ast ast;


ast* convert_to_ast(token *toks, int token_count);

#endif
