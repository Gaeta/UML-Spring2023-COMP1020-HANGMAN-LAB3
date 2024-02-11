#include <string.h> // for strcpy and strlen
#include <ctype.h> // for isspace
#include <stdio.h> // for fgetc, ungetc, and fwrite 
#include <stdlib.h> // for malloc, free, and realloc
#include "my_string.h"


typedef struct My_string {
    int size;
    int capacity;
    char* data;
} My_string;

MY_STRING my_string_init_default(void) {
    My_string* pString = malloc(sizeof(My_string));
    if (!pString) return NULL;

    pString->size = 0;
    pString->capacity = 7; // default capacity
    pString->data = malloc(sizeof(char) * pString->capacity);
    if (!pString->data) {
        free(pString);
        return NULL;
    }
    pString->data[0] = '\0'; // initializes to empty string
    return (MY_STRING)pString;
}

MY_STRING my_string_init_c_string(const char* c_string) {
    if (!c_string) return NULL; // handle NULL input

    int length = strlen(c_string);
    My_string* pString = malloc(sizeof(My_string));
    if (!pString) return NULL;

    pString->capacity = length + 1; // plus null terminator
    pString->size = length;
    pString->data = malloc(sizeof(char) * pString->capacity);
    if (!pString->data) {
        free(pString);
        return NULL;
    }
    strcpy(pString->data, c_string);
    return (MY_STRING)pString;
}

void my_string_destroy(MY_STRING* phMy_string) {
    if (phMy_string && *phMy_string) {
        My_string* pString = (My_string*)*phMy_string;
        free(pString->data);
        free(pString);
        *phMy_string = NULL;
    }
}

int my_string_get_capacity(MY_STRING hMy_string) {
    if (!hMy_string) return 0;
    My_string* pString = (My_string*)hMy_string;
    return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string) {
    if (!hMy_string) return 0;
    My_string* pString = (My_string*)hMy_string;
    return pString->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
    if (!hLeft_string || !hRight_string) return 0;

    My_string* pLeft = (My_string*)hLeft_string;
    My_string* pRight = (My_string*)hRight_string;

    return strcmp(pLeft->data, pRight->data);
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
    My_string* pString = (My_string*)hMy_string;
    int ch;
    int readChars = 0;

    pString->size = 0; // reset size to 0

    // printf("-C Read %d characters\n", readChars);

    while(isspace(ch = fgetc(fp)) && ch != EOF); // skip leading whitespace

    // printf("-B Read %d characters\n", readChars);

    // printf("ch: %c : EOF?: %s\n", ch, ch == EOF ? "yes" : "no");
    if (ch == EOF) return FAILURE; // no characters to read
    // printf("-A Read %d characters\n", readChars);

    if (ch != EOF && !isspace(ch)) {
        pString->data[pString->size++] = ch;
        readChars++;
    }
    
    // printf("A Read %d characters\n", readChars);

    while(((ch = fgetc(fp)) != EOF && !isspace(ch))) {
        if (pString->size >= pString->capacity) {
            pString->capacity *= 2;
            char* temp = realloc(pString->data, pString->capacity);

            pString->data = temp;
        }

        pString->data[pString->size++] = ch;

        readChars++;

    }

    // printf("B Read %d characters\n", readChars);

    if(isspace(ch)) {
        ungetc(ch, fp);
    }

    // printf("C Read %d characters\n", readChars);

    pString->data[pString->size] = '\0'; // null-terminate the string

    // printf("D Read %d characters\n", readChars);
    // printf("E readchars (%d) > 0 (S/F): %d\n", readChars, readChars > 0 ? SUCCESS : FAILURE);
    return readChars > 0 ? SUCCESS : FAILURE;
}

// Simplified my_string_insertion function
Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
    My_string* pString = (My_string*)hMy_string;

    // Write the string data to the file
    int written = fwrite(pString->data, sizeof(char), pString->size, fp);

    if (written < pString->size) 
        return FAILURE;
    
    return SUCCESS;
}