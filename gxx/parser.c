/*
 *  compiler/parser.c
 * 
 *  Copyleft (C) 2015  Geo-X Team
 *
 * Source parser for იქ-C compilator. 
 */


/* Util includes */
#include "../utils/strops.h" 
#include "../utils/slog.h"

/* Local includes */
#include "stdinc.h"
#include "mdefs.h"

#define KEYMAP_SIZE 33


/* Full georgian alphabet keymap */
static char *geo_keymap[KEYMAP_SIZE] = {"ა", "ბ", "გ", "დ", "ე", "ვ", "ზ", "თ", "ი", 
                                        "კ", "ლ", "მ", "ნ", "ო", "პ", "ჟ", "რ", 
                                        "ს", "ტ", "უ", "ფ", "ქ", "ღ", "ყ", "შ", 
                                        "ჩ", "ც", "ძ", "წ", "ჭ", "ხ", "ჯ", "ჰ"};


/* English values for geo keymap */
static char *en_keymap[KEYMAP_SIZE] = {"a", "b", "g", "d", "e", "v", "z", "th", "i",
                                        "k", "l", "m", "n", "o", "p", "zh", "r",
                                        "s", "t", "u", "f", "q", "gh", "y", "sh",
                                        "ch", "c", "dz", "w", "wh", "x", "j", "h"};


/* 
 * translate_alphabet - Translate alpabhet from georgian to english.
 * Agument line is parsed file line in which we want to translate.
 */
char* translate_alphabet(char * line)
{
    int i;

    /* Translate each key in alphabet */
    for(i = 0; i < KEYMAP_SIZE; i++)
        line = strrep(line, geo_keymap[i], en_keymap[i]);

    return line;
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

    /* Defs/Incs */
    out = strrep(line, GX_INCLUDE, "#include");
    out = strrep(out, GX_DEFINE, "#define");

    /* Opers */
    out = strrep(out, GX_ELSE_IF, "else if");
    out = strrep(out, GX_FOREACH, "foreach");
    out = strrep(out, GX_WHILE, "while");
    out = strrep(out, GX_BREAK, "break");
    out = strrep(out, GX_EXLSE, "else");
    out = strrep(out, GX_FOR, "for");
    out = strrep(out, GX_DO, "do");
    out = strrep(out, GX_AS, "as");
    out = strrep(out, GX_IF, "if");

    /* Types */
    out = strrep(out, GX_UNSIGNED, "unsigned");
    out = strrep(out, GX_SIGNED, "signed");
    out = strrep(out, GX_DOUBLE, "double");
    out = strrep(out, GX_STRING, "char*");
    out = strrep(out, GX_SHORT, "short");
    out = strrep(out, GX_LONG, "long");
    out = strrep(out, GX_INT, "int");

    /* Others */
    out = strrep(out, GX_TYPEDEF, "typedef");
    out = strrep(out, GX_PRINT, "printf");
    out = strrep(out, GX_STRUCT, "struct");
    out = strrep(out, GX_MAIN, "main");
    out = strrep(out, GX_VOID, "void");
    out = strrep(out, GX_NULL, "NULL");
    out = strrep(out, GX_EXIT, "exit");
    out = strrep(out, GX_FUNCTION, "");

    return out;
}