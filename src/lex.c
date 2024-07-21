#define TOTAL_TOKS 20
#define WORD_SIZE 10

#include <lex.h>

#include <ctype.h>
#include <stdlib.h>
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
        if (ch == ' ')
		{
            while (ch == ' ')
                ch = fgetc(fp);
            fseek(fp, -1, SEEK_CUR);

            toks[i].string = word;
            toks[i].string_length = j;
            word = (char*)malloc(WORD_SIZE*sizeof(char));
            j=0;
            i++;
        }
        else if (is_in(ch, scope_designators, 4) != 0)
		{
            if (j != 0)
			{
                toks[i].string = word;
                toks[i].string_length = j;
                word = (char*)malloc(WORD_SIZE*sizeof(char));
                j=0;
                i++;
            }
            char *scope_token = (char*)malloc(sizeof(char));
            scope_token[0] = ch;
            toks[i].string = scope_token;
            toks[i].string_length = 1;
            toks[i].type = 2;
            j=0;
            i++;
        }
        else if (ch == '\n' || ch == EOF)
		{
            continue;
        }
        else
        {
            if (j == WORD_SIZE)
                word = (char*)realloc(word, (j/WORD_SIZE+1)*WORD_SIZE*sizeof(char));
            if (isdigit(ch) && j==0)
                toks[i].type = 0;
            if (isalpha(ch) && j==0)
                toks[i].type = 1;
            word[j] = ch;
            j++;
        }
    } while (ch != EOF);

    *out_ntokens = i;
    return toks;
}
