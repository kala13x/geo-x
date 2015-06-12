/*
 *  utils/strops.h
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * This source includes string operations.
 */


#include "stdinc.h"
#include "strops.h"
#include "errex.h"


/*
 * strsrc - Search string in another string. If string is 
 * found, function returns 1, else 0 or -1. Argument str is 
 * string to search and srch is string we want search for.
 */
int strsrc(char *str, char *srch)
{
    int lenstr = strlen(str);
    int lensrch = strlen(srch);
    int found = -1;
    int i, x;
 
    /* Search through each char in str */
    for (i = 0; i < lenstr; i++)
    {
        /* If first search item is valid then search str */
        if (srch[0] == str[i])
        {
            found = 1;

            /* Search the char array for search field */
            for (x = 1; x < lensrch; x++) 
                if (str[i+x] != srch[x]) found = 0;
 
            /* Return if found */
            if (found) return found;
        }
    }
 
    return found;
}

 
/*
 * strrep - Replace string with another string in whole buffer. Argument 
 * str is whole buffer, oldstr is string which we want to replace and 
 * newstr is new string which we want to save. Return value is whole 
 * buffer with replaced strings, it must be freed with free() after usage.
 */
char *strrep(const char *str, const char *oldstr, const char *newstr)
{
    char *ret;
    int i, count = 0;
    int newlen = strlen(newstr);
    int oldstrlen = strlen(oldstr);

    for (i = 0; str[i] != '\0'; i++)    
    {
        if (strstr(&str[i], oldstr) == &str[i]) 
        {
            count++;
            i += oldstrlen - 1;
        }
    }

    /* Allocate output buffer memory */
    ret = (char *)malloc(i + count * (newlen - oldstrlen));
    if (ret == NULL)
        exit_prog(1, "Can not allocate strrep buffer memory");

    i = 0;
    while (*str)
    {
        /* Compare the substring with the newstring */
        if (strstr(str, oldstr) == str)
        {
            /* Adding newlength to the new string */
            strcpy(&ret[i], newstr);
            i += newlen;
            str += oldstrlen;
        }
        else ret[i++] = *str++;
    }

    /* Null terminate */
    ret[i] = '\0';

    return ret;
}