/**
* Name: Keghvart Hagopian
* Lab/task: Scanner2
* Date: 10-4-17
**/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number_of_rows;
    int number_of_columns;
    char **table;
} TRANS_TABLE_TYPE;


typedef enum {
    INVALID_TOKEN = 0,
    NUMBERTOKEN,
    IDENTTOKEN,
    ASSIGNMENT,
    SEMICOLON,
    LPAREN,
    RPAREN,
    ADDOP,
    MULTOP,
    REPEAT,
    PRINT,
    END_OF_INPUT_TOKEN
} TOKEN_TYPE;

typedef struct token {
    TOKEN_TYPE type;
    char *strVal;
} TOKEN;

TOKEN *Scanner2(TRANS_TABLE_TYPE *st);
extern char *char2str;

#define BUF_SIZE 128
#define MAX_LINE_LENGTH 256
