#ifndef LEX
#define LEX

#include <stdio.h>


typedef struct
{
    char *string;
    int string_length;
    int type;           // 0 literal 1 operand
} token;

token* get_tokens(FILE *fp, int* out_ntokens);

#endif
