#include <stdlib.h>
#include <string.h>

#include <lex.h>
#include <semantic.h>


void create_tree(ast *parent, token *toks, int position, int token_count)
{
    if (position == token_count)
        return;

    if (toks[position].string[0] == '(')
	{
        create_tree(parent, toks, position+1, token_count);
        int stack=1, i=1;
        while (stack!=0 && position+i<token_count)
		{
            if (toks[position+i].string[0] == '(')
                stack++;
            if (toks[position+i].string[0] == ')')
                stack--;
            i++;
        }
        create_tree(parent, toks, position+i, token_count);
    }
    else if (toks[position].string[0] == ')')
	{
    }
    else
    {
        ast *tree_node = (ast*)malloc(sizeof(ast));
        tree_node->node_val = toks[position].string;
        tree_node->node_val_size = toks[position].string_length;
        tree_node->parent = parent;

        // first child
        if (parent->children == NULL)
            parent->children = tree_node;

        // set new sibling
        ast *tmp = parent->children;
        while (tmp->sibling != NULL)
            tmp = tmp->sibling;
        if (tmp != tree_node)
            tmp->sibling = tree_node;

        // token is operator so create operands as children else create sibling
        if (toks[position-1].string[0] == '(')
            create_tree(tree_node, toks, position+1, token_count);
        else
            create_tree(parent, toks, position+1, token_count);
    }
}

ast* convert_to_ast(token *toks, int token_count)
{
    ast *tree_root = (ast*)malloc(sizeof(ast));

    tree_root->parent = NULL;
    tree_root->sibling = NULL;
    tree_root->node_val = "root";
    tree_root->node_val_size = 4;

    create_tree(tree_root, toks, 0, token_count);

    return tree_root;
}
