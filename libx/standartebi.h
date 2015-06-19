/* 
 * libx/standartebi.h
 * 
 *  Copyleft (C)  Geo-X Team
 * 
 * სტანდარტული შემოტანები.
 */


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAXMSG 8196


/* 
 * We dont need \n while printing
 *
 * TODO: remove from header and create 
 * shared dinamic linced library
 */
void dabewhde(const char *msg, ...) 
{
    /* Used variables */
    char string[MAXMSG];

    /* Read args */
    va_list args;
    va_start(args, msg);
    vsprintf(string, msg, args);
    va_end(args);

    /* Print string */
    printf("%s\n", string);
}