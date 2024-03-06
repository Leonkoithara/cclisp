#define TOTAL_TOKS 20
#define WORD_SIZE 10

#include <lex.h>

#include <ctype.h>
#include <malloc.h>
#include <stdio.h>


int is_in(char ch, char *arr, int arr_len)
{
    for (int i=0; i<arr_len; i++)
	{
        if (ch == arr[i])
            return ch;
    }

    return 0;
}

token *get_tokens(FILE *fp, int *out_ntokens)
{
    token *toks = (token*)malloc(TOTAL_TOKS*sizeof(token));
    char ch;
    char *word = (char*)malloc(WORD_SIZE*sizeof(char));
    int i=0, j=0;
    char scope_designators[4] = { '(', '{', ')', '}' };
    do
    {
        ch = fgetc(fp);
        if (ch == ' ' || ch == EOF)
		{
            // TODO: remove all whitespaces after this
            toks[i].string = word;
            toks[i].string_length = j;
            word = (char*)malloc(WORD_SIZE*sizeof(char));
            j=0;
            i++;
        }
        else if (is_in(ch, scope_designators, 4) != 0)
		{
        }
        else
        {
            if (j == WORD_SIZE)
                word = (char*)realloc(word, (j/WORD_SIZE+1)*WORD_SIZE*sizeof(char));
            if (isdigit(ch))
                toks[i].type = 0;
            if (isalpha(ch))
                toks[i].type = 1;
            word[j] = ch;
            j++;
        }
    } while (ch != EOF);

    *out_ntokens = i;
    return toks;
}
