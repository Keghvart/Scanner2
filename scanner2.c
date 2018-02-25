/**
* Name: Keghvart Hagopian
* Lab/task: Scanner2
* Date: 10-4-17
**/
#include "scanner2.h"

TOKEN *ungottenToken = NULL;
char *char2str = "()=;*/%-+ \t\n";

int isKeyword(TOKEN *token, char *str) {
    if (strcmp(str, "repeat") == 0)
        token->type = REPEAT;
    else if (strcmp(str, "print") == 0)
        token->type = PRINT;
    else
        return 0;

    return 1;
}

TRANS_TABLE_TYPE *scan_init(FILE *trans_in_file) {
    TRANS_TABLE_TYPE *state_table = (TRANS_TABLE_TYPE *) malloc(sizeof(TRANS_TABLE_TYPE));

    if (trans_in_file == NULL) {
        printf("File was not found, please try again with a proper file.\n");
    }

    char temp;
    int row = 0;
    int col = 0;
    int i = 0;
    int j = 0;
    char buffer[MAX_LINE_LENGTH];
    // Calculate how many rows the table has
    while ((fgets(buffer, MAX_LINE_LENGTH, trans_in_file)) != NULL) {
        row++;
    }
    // Calculate how many columns the state table has
    for (i = 0; i < (strlen(buffer)); i++) {
        if (buffer[i] != ' ') {
            col++;
        }
    }
    // Setting the state table cols, rows, and creating the rows using malloc
    state_table->number_of_columns = col;
    state_table->number_of_rows = row;
    state_table->table = (char **) malloc(row * sizeof(char *));
    for (i = 0; i < row; i++) {
        state_table->table[i] = (char *) malloc(col * sizeof(char));
    }
    // Reset to go to the beginning of file.
    fseek(trans_in_file, 0L, SEEK_SET);
    // Creating the table by inputing the chars into the state table
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            temp = fgetc(trans_in_file);

            if (temp != ' ' && temp != '\n') {
                state_table->table[i][j] = temp;
            } else
                j--;
        }
    }
    free(trans_in_file);
    return state_table;
}

// Function used to get the respective column of the character
int getColumn(char c) {
    int index = 0;
    char *p;
    p = strchr(char2str, c);
    index = (int) (p - char2str);

    if (index < 0) {
        if (isdigit(c)) {
            return 12;
        } else if (isalpha(c)) {
            return 13;
        } else {
            return 14;
        }
    } else {
        return index;
    }
}

// Used to actually calculated the state and token of the input
TOKEN *Scanner2(TRANS_TABLE_TYPE *st) {

    if (ungottenToken != NULL) {
        TOKEN *tok = ungottenToken;
        ungottenToken = NULL;
        return tok;
    }
    // Temporary buffer for the identifiers and numbers
    char tempString[BUF_SIZE];

    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->type = INVALID_TOKEN;
    token->strVal = NULL;

    char c;
    int i = 0;
    int column = 0;
    int state = 0;
    int newState = 0;
    while (token->type == INVALID_TOKEN) {
        c = getchar();
        if (c == EOF) {
            free(token);
            return NULL;
        }
        column = getColumn(c);
        if (st->table[state][column] != 'a' && st->table[state][column] != 'e') {
            // Used to calculate the new state based upon input
            int newstate = (st->table[state][column] - '0') % 48;
            if (newstate > 0) {
                tempString[i++] = c;
            }

            state = newstate;
        } else if (st->table[state][column] == 'a') {
            ungetc(c, stdin); // put it back
            tempString[i] = '\0';
            if (!isKeyword(token, tempString)) {
                token->strVal = (char *) malloc(strlen(tempString) + 1);
                strcpy(token->strVal, tempString);
                switch (st->table[state][15]) { // Switch statement to check and see what token belongs to the input
                    case '(':
                        token->type = LPAREN;
                        break;
                    case ')':
                        token->type = RPAREN;
                        break;
                    case '=':
                        token->type = ASSIGNMENT;
                        break;
                    case ';':
                        token->type = SEMICOLON;
                        break;
                    case 'M':
                        token->type = MULTOP;
                        break;
                    case 'A':
                        token->type = ADDOP;
                        break;
                    case 'N':
                        token->type = NUMBERTOKEN;
                        break;
                    case 'I':
                        token->type = IDENTTOKEN;
                        break;
                    default:
                        token->type = INVALID_TOKEN;
                }
            }
            return token;
        }
    }
    return token;
}