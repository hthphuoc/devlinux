#include <stdio.h>
#include "strutils.h"

int main()
{
    char str1[100] = "  Hello World  ";
    char str2[100] = "Hello World";
    char numStr1[] = "12345";
    char numStr2[] = "12a45";
    long number;

    printf("=== Testing str_trim ===\n");
    printf("Before trim: '%s'\n", str1);
    str_trim(str1);
    printf("After trim:  '%s'\n\n", str1);

    printf("=== Testing str_reverse ===\n");
    printf("Before reverse: %s\n", str2);
    str_reverse(str2);
    printf("After reverse:  %s\n\n", str2);

    printf("=== Testing str_to_int ===\n");
    if (str_to_int(numStr1, &number) != -1) {
        printf("'%s' -> %ld\n", numStr1, number);
    } else {
        printf("'%s' is not a valid integer\n", numStr1);
    }

    if (str_to_int(numStr2, &number) != -1) {
        printf("'%s' -> %ld\n", numStr2, number);
    } else {
        printf("'%s' is not a valid integer\n", numStr2);
    }

    return 0;
}