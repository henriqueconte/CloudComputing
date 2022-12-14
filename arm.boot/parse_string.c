#include "parse_string.h"

// https://www.geeksforgeeks.org/c-program-to-compare-two-strings-without-using-strcmp-function/
int compareStrings(char* string1, char* string2) {
    int isEqual = 0;
 
    // Iterate a loop till the end
    // of both the strings
    while (*string1 != '\0' || *string2 != '\0') {
        if (*string1 == *string2) {
            string1++;
            string2++;
        }
 
        // If two characters are not same
        // print the difference and exit
        else if ((*string1 == '\0' && *string2 != '\0')
                 || (*string1 != '\0' && *string2 == '\0')
                 || *string1 != *string2) {
            isEqual = 1;
            return 0;
        }
    }
 
    // If two strings are exactly same
    if (isEqual == 0) {
        return 1;
    }
}