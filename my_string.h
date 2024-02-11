#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdlib.h> // for size_t
#include <stdio.h>

// Renames void* to MY_STRING for better readability and abstraction
typedef struct My_string* MY_STRING;
typedef enum { FAILURE, SUCCESS } Status;

// Initializes a default MY_STRING object
// Precondition: None
// Postcondition: Returns a handle to a new MY_STRING object with default state, or NULL on failure
MY_STRING my_string_init_default(void);

// Initializes a MY_STRING object from a C-string
// Precondition: c_string is a valid null-terminated string
// Postcondition: Returns a handle to a new MY_STRING object containing the same characters as c_string, or NULL on failure
MY_STRING my_string_init_c_string(const char* c_string);

// Destroys a MY_STRING object
// Precondition: phMy_string is the address of a valid MY_STRING object or NULL
// Postcondition: The memory for the MY_STRING object is reclaimed by the system and the handle is set to NULL
void my_string_destroy(MY_STRING* phMy_string);

// Returns a copy of the integer value of the object's capacity
// Precondition: hMy_string is the handle of a valid My_string object
// Postcondition: Returns a copy of the integer value of the object's capacity
int my_string_get_capacity(MY_STRING hMy_string);

// Returns a copy of the integer value of the object's size
// Precondition: hMy_string is the handle of a valid My_string object
// Postcondition: Returns a copy of the integer value of the object's size
int my_string_get_size(MY_STRING hMy_string);

// Compares two My_string objects lexicographically
// Precondition: hLeft_string and hRight_string are valid My_string objects
// Postcondition: Returns an integer less than zero if hLeft_string is smaller,
// zero if they are equal, and greater than zero if hLeft_string is bigger
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: hMy_string will be the handle of a string object that contains
// the next string from the file stream fp according to the following rules.
// 1) Leading whitespace will be ignored.
// 2) All characters (after the first non-whitespace character is obtained
// and included) will be added to the string until a stopping condition
// is met. The capacity of the string will continue to grow as needed
// until all characters are stored.
// 3) A stopping condition is met if we read a whitespace character after
// we have read at least one non-whitespace character or if we reach
// the end of the file.
// Function will return SUCCESS if a non-empty string is read successfully.
// and failure otherwise. Remember that the incoming string may aleady
// contain some data and this function should replace the data but not
// necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE* fp);
//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Writes the characters contained in the string object indicated
// by the handle hMy_string to the file stream fp.
// Function will return SUCCESS if it successfully writes the string and
// FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE* fp);


#endif // MY_STRING_H
