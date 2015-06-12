/*
 *  utils/color.h
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * This library includes color operations with strings such es
 * colorize string and color print in cli. Color values are:
 * 
 *  0 - Normal
 *  1 - Green
 *  2 - Red
 *  3 - Yellow
 *  4 - Blue
 *  5 - Nagenta
 *  6 - Cyan
 *  7 - White
 */


#include "stdinc.h"
#include "color.h"

/* Supported colors */
#define CLR_NORM     "\x1B[0m"
#define CLR_RED      "\x1B[31m"
#define CLR_GREEN    "\x1B[32m"
#define CLR_YELLOW   "\x1B[33m"
#define CLR_BLUE     "\x1B[34m"
#define CLR_NAGENTA  "\x1B[35m"
#define CLR_CYAN     "\x1B[36m"
#define CLR_WHITE    "\x1B[37m"
#define CLR_RESET    "\033[0m"

/* Max size of string */
#define MAXMSG 8196


/*
 * strclr - Colorize string. Function takes color value and string 
 * and returns colorized string as char pointer. First argument clr 
 * is color value (if it is invalid, function retunrs NULL) and second 
 * is string with va_list of arguments which one we want to colorize.
 */
char* strclr(int clr, char* str, ...) 
{
    /* String buffers */
    static char output[MAXMSG];
    char string[MAXMSG];

    /* Read args */
    va_list args;
    va_start(args, str);
    vsprintf(string, str, args);
    va_end(args);

    /* Handle colors */
    switch(clr) 
    {
        case 0:
            sprintf(output, "%s%s%s", CLR_NORM, string, CLR_RESET);
            break;
        case 1:
            sprintf(output, "%s%s%s", CLR_GREEN, string, CLR_RESET);
            break;
        case 2:
            sprintf(output, "%s%s%s", CLR_RED, string, CLR_RESET);
            break;
        case 3:
            sprintf(output, "%s%s%s", CLR_YELLOW, string, CLR_RESET);
            break;
        case 4:
            sprintf(output, "%s%s%s", CLR_BLUE, string, CLR_RESET);
            break;
        case 5:
            sprintf(output, "%s%s%s", CLR_NAGENTA, string, CLR_RESET);
            break;
        case 6:
            sprintf(output, "%s%s%s", CLR_CYAN, string, CLR_RESET);
            break;
        case 7:
            sprintf(output, "%s%s%s", CLR_WHITE, string, CLR_RESET);
            break;
        default:
            return NULL;
    }

    /* Return output */
    return output;
}


/*
 * printclr - Function takes color value and 
 * string and prints colorized string with printf.
 * First argument clr is color value and second is string
 * with va_list of arguments which one we want to print.
 */
void printclr(int clr, char* str, ...) 
{
    /* Used variables */
    char string[MAXMSG];
    char* colorized;

    /* Read args */
    va_list args;
    va_start(args, str);
    vsprintf(string, str, args);
    va_end(args);

    /* Print colorized string */
    colorized = strclr(clr, string);
    if (colorized != NULL) 
        printf("%s", colorized);
}


/*
 * randclr - Random colorize. Function returns colorized string 
 * with random color. Argument str is string with va_list of 
 * arguments  which one we want to colorize with random color.
 */
char* randclr(char* str, ...) 
{
    /* Used variables */
    char string[MAXMSG];
    char* colorized;

    /* Read args */
    va_list args;
    va_start(args, str);
    vsprintf(string, str, args);
    va_end(args);

    /* Print random color */
    srand(time(NULL));
    int r = rand() % 8;
    colorized = strclr(r, string);

    return colorized;
}


/*
 * printrclr - Print random colorized string. Function prints 
 * string with random color. Argument str is string with va_list 
 * of arguments  which one we want to print with random color.
 */
void printrclr(char* str, ...) 
{
    /* Used variables */
    char string[MAXMSG];
    char* colorized;

    /* Read args */
    va_list args;
    va_start(args, str);
    vsprintf(string, str, args);
    va_end(args);

    /* Get random color */
    colorized = randclr(string);
    if (colorized != NULL) 
        printf("%s", colorized);
}