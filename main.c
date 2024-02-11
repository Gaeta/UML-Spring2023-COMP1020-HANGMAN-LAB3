#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
    MY_STRING hMy_string = NULL;
    FILE* fp;

    hMy_string = my_string_init_default();
    fp = fopen("dictionary.txt", "r");

    if (fp == NULL) {
        printf("File not found\n");
        my_string_destroy(&hMy_string);
        exit(1);
    }

    while (my_string_extraction(hMy_string, fp) == SUCCESS) {
        // printf("bob\n");
        // Only print the word if it has exactly 5 characters
        if (my_string_get_size(hMy_string) == 5) {
            // printf("Cake\n");
            my_string_insertion(hMy_string, stdout);
            printf("\n"); // Print a new line after each word
        }

        // printf("James\n");
    }

    // printf("Mercy\n");

    // Clean up
    my_string_destroy(&hMy_string);
    fclose(fp);
    
    return 0;
}