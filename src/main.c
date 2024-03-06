#include <lex.h>

#include <stdio.h>


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
    for (int i=0; i<count; i++)
        printf("%.*s\n", toks[i].string_length, toks[i].string);

    fclose(fp);
    return 0;
}
