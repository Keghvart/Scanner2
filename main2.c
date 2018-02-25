/**
* Name: Keghvart Hagopian
* Lab/task: Scanner2
* Date: 10-4-17
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner2.h"

TRANS_TABLE_TYPE *trans_table;
TRANS_TABLE_TYPE* scan_init(FILE *);

int main() {

    TRANS_TABLE_TYPE *trans_table;

    FILE *trans_in_file = fopen("C:\\Users\\user\\Desktop\\New folder\\thestatetable.txt", "r");
    TOKEN *token = NULL;

    if (trans_in_file == NULL) {
        exit(-1);
    }
    trans_table = scan_init(trans_in_file);
    char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "ADDOP", "MULTOP",
                         "REPEAT", "PRINT", "END_OF_INPUT"};

    printf("\n");
    while ((token = Scanner2(trans_table)) != NULL) {
        printf("{%s, %s}", token2str[token->type], (token->strVal != NULL) ? token->strVal : "");
    }
}