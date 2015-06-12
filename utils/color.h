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


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/*
 * strclr - Colorize string. Function takes color value and string 
 * and returns colorized string as char pointer. First argument clr 
 * is color value (if it is invalid, function retunrs NULL) and second 
 * is string with va_list of arguments which one we want to colorize.
 */
char* strclr(int clr, char* str, ...);


/*
 * printclr - Function takes color value and 
 * string and prints colorized string with printf.
 * First argument clr is color value and second is string
 * with va_list of arguments which one we want to print.
 */
void printclr(int clr, char* str, ...);


/*
 * randclr - Random colorize. Function returns colorized string 
 * with random color. Argument str is string with va_list of 
 * arguments  which one we want to colorize with random color.
 */
char* randclr(char* str, ...);


/*
 * printrclr - Print random colorized string. Function prints 
 * string with random color. Argument str is string with va_list 
 * of arguments  which one we want to print with random color.
 */
void printrclr(char* str, ...);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif