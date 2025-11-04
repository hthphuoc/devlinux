#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "strutils.h"

void str_reverse(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len/2; i ++)
    {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

void str_trim(char *str)
{
    int head = 0, tail = 0;
    int len = strlen(str);
    while (str[head] == ' ') head ++;
    while (str[len - tail - 1] == ' ') tail ++; 
    len = strlen(str) - head - tail;
    memmove(str, str + head, len);
    str[len] = '\0';

}

int str_to_int(const char *str, long *result)
{
    char *endptr = NULL;
    long val = strtol(str, &endptr, 10);

    if (strlen(str) == strlen(endptr)) return -1;
    if ( (strlen(endptr) > 1) || (strlen(endptr) == 1 && !isspace((unsigned char)*endptr)) ) return -1;
    *result = val;
    return 0;
}