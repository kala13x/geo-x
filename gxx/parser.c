/*
 *  compiler/parser.c
 * 
 *  Copyleft (C) 2015  Geo-X Team
 *
 * Source parser for იქ-C compilator. 
 */


#include "../utils/strops.h" 
#include "../utils/slog.h"
#include "stdinc.h"
#include "mdefs.h"


/* 
 * translate_alphabet - Translate alpabhet from georgian to english.
 * Agument line is parsed file line in which we want to translate.
 */
char* translate_alphabet(char * line)
{
    static char *out = NULL;
    out = strrep(line, "ა", "a");
    out = strrep(out, "ბ", "b");
    out = strrep(out, "გ", "g");
    out = strrep(out, "დ", "d");
    out = strrep(out, "ე", "e");
    out = strrep(out, "ვ", "v");
    out = strrep(out, "ზ", "z");
    out = strrep(out, "თ", "t");
    out = strrep(out, "ი", "i");
    out = strrep(out, "კ", "k");
    out = strrep(out, "ლ", "l");
    out = strrep(out, "მ", "m");
    out = strrep(out, "ნ", "n");
    out = strrep(out, "ო", "o");
    out = strrep(out, "პ", "p");
    out = strrep(out, "ჟ", "zh");
    out = strrep(out, "რ", "r");
    out = strrep(out, "ს", "s");
    out = strrep(out, "ტ", "t");
    out = strrep(out, "უ", "u");
    out = strrep(out, "ფ", "f");
    out = strrep(out, "ქ", "q");
    out = strrep(out, "ღ", "gh");
    out = strrep(out, "ყ", "y");
    out = strrep(out, "შ", "sh");
    out = strrep(out, "ჩ", "ch");
    out = strrep(out, "ც", "c");
    out = strrep(out, "ძ", "dz");
    out = strrep(out, "წ", "w");
    out = strrep(out, "ხ", "x");
    out = strrep(out, "ჯ", "j");
    out = strrep(out, "ჰ", "h");

    return out;
}


/* 
 * parse_includes - Parse include definitions from source.
 * Argument line is line from source code we want to parse.
 */
char* parse_includes(char * line)
{    
    char *ret = NULL;
    char *out = NULL;
    char *inc = NULL;
    char include[64];
    char getline[MAXMSG];

    /* Check valid line */
    if (strsrc(line, "შემოიღე") <= 0)
        return line;

    /* Get include */
    strcpy(getline, line);
    inc = strtok(line, " ");
    ret = strtok(NULL, " ");

    /* Translate to english */
    out = translate_alphabet(ret);
    bzero(include, sizeof(include));
    sprintf(include, "<%s.h>", out);

    /* Reolace */
    out = strrep(getline, ret, include);

    return out;
}


/* 
 * parse_includes - Parse reserved words from source code.
 * Argument line is line from source code we want to parse.
 */
char* parse_reserved(char * line) 
{
    static char *out = NULL;
    out = strrep(line, GX_STRING, "char*");
    out = strrep(out, GX_INT, "int");
    out = strrep(out, GX_SIGNED, "signed");
    out = strrep(out, GX_UNSIGNED, "unsigned");
    out = strrep(out, GX_DOUBLE, "double");
    out = strrep(out, GX_SHORT, "short");
    out = strrep(out, GX_LONG, "long");
    out = strrep(out, GX_FOR, "for");
    out = strrep(out, GX_WHILE, "while");
    out = strrep(out, GX_DO, "do");
    out = strrep(out, GX_FOREACH, "foreach");
    out = strrep(out, GX_AS, "as");
    out = strrep(out, GX_FUNCTION, "");
    out = strrep(out, GX_BREAK, "break");
    out = strrep(out, GX_IF, "if");
    out = strrep(out, GX_EXLSE, "else");
    out = strrep(out, GX_ELSE_IF, "else if");
    out = strrep(out, GX_INCLUDE, "#include");
    out = strrep(out, GX_DEFINE, "#define");
    out = strrep(out, GX_MAIN, "main");
    out = strrep(out, GX_VOID, "void");
    out = strrep(out, GX_NULL, "NULL");
    out = strrep(out, GX_EXIT, "exit");
    out = strrep(out, GX_PRINT, "printf");

    out = translate_alphabet(out);

    return out;
}