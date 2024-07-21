#include <stdio.h>

#include <lex.h>
#include <semantic.h>

void traverse(struct ast *node)
{
    if (node == NULL)
	{
        return;
    }
    else
    {
        traverse(node->children);
        printf("%.*s\n", node->node_val_size, node->node_val);
        traverse(node->sibling);
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc > 1)
	{
        fp = fopen(argv[1], "r");
        if (fp == NULL)
            return 1;
    }
    else
    {
        return 1;
    }

    int count;
    token *toks = get_tokens(fp, &count);
    struct ast *code = convert_to_ast(toks, count);

    traverse(code);

    fclose(fp);
    return 0;
}
