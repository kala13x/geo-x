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
 * orig is whole buffer, rep is string which we want to replace and with 
 * is new string which we want to save. Return value is whole buffer with 
 * replaced strings, it must be freed with free() after usage.
 */
char *strrep(char *orig, char *rep, char *with) 
{
    int len_rep, len_with, len_front, count;
    char *result;
    char *ins;
    char *tmp;

    /* Initialize variables */
    if (!orig) return NULL;
    if (!rep) rep = "";
    len_rep = strlen(rep);
    if (!with) with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)) != NULL; ++count) {
        ins = tmp + len_rep;
    }

    /* Alocate string buffer size */
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    
    return result;
}