#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "input_utils.h"

void strtrim(char *dest, const char *src)
{
    const char *start = src;
    const char *end;
    
    while (*start && isspace((unsigned char)*start)) 
    {
        start++;
    }

    if (*start == '\0') 
    {
        
        dest[0] = '\0';
        return;
    }
    
    end = start + strlen(start) - 1;
    
    while (end > start && isspace((unsigned char)*end)) 
    {
        end--;
    }
    
    size_t len = end - start + 1;
    memcpy(dest, start, len);
    dest[len] = '\0';
}