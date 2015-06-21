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
 * tokenize_quotes - Get quotes from line and return part
 * by part. Argument line is whole line, lstart is part
 * before quotes and argument lend is part after quotes.
 */
char* tokenize_quotes(char *line, char *lstart, char *lend) 
{
    /* Parts to parse */
    char *quote;

    /* Check correct line */
    if (!strsrc(line, "\"")) 
        return NULL;

    /* Tokenize quotes */
    lstart = strtok(line, "\"");
    quote = strtok(NULL, "\"");
    lend = strtok(NULL, "\"");

    return quote;
}


/* 
 * translate_alphabet - Translate alpabhet from georgian to english.
 * Agument line is parsed file line in which we want to translate.
 */
char* translate_alphabet(char * line)
{
    char *quote, *lstart, *lend;
    static char retline[LINE_MAX];
    int i;

    /* Check correct line */
    if (strsrc(line, "\"") > 0) 
    {
        /* Tokenize quotes */
        lstart = strtok(line, "\"");
        quote = strtok(NULL, "\"");
        lend = strtok(NULL, "\"");

        /* Translate start part */
        for(i = 0; i < KEYMAP_SIZE; i++)
            lstart = strrep(lstart, geo_keymap[i], en_keymap[i]);

        /* Translate end part */
        for(i = 0; i < KEYMAP_SIZE; i++)
            lend = strrep(lend, geo_keymap[i], en_keymap[i]);

        /* Join start, quote and end */
        sprintf(retline, "%s\"%s\"%s", lstart, quote, lend);
    }
    else 
    {
        /* Translate each key in alphabet */
        for(i = 0; i < KEYMAP_SIZE; i++)
            line = strrep(line, geo_keymap[i], en_keymap[i]);

        strcpy(retline, line);
    }

    return retline;
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
 * parse_functions - Translate functions from georgian to english.
 * Agument line is parsed file line in which we want to translate.
 */
char* parse_functions(char * line)
{
    char *func, *fname, *ret, *type;
    char getline[MAXMSG];
    char rep[MAXMSG];
    char newrep[MAXMSG];
    char *out;

    /* Check valid line */
    if (strsrc(line, "ფუნქცია") <= 0 || strsrc(line, "ცარიელი") > 0)
        return line;

    strcpy(getline, line);

    /* Parse line */
    func = strtok(line, " ");
    fname = strtok(NULL, " ");
    ret = strtok(NULL, " ");
    type = strtok(NULL, " ");
    sscanf(type, "%32[^(](", type);

    /* Create recept */ 
    sprintf(rep, "%s %s %s %s", func, fname, ret, type);
    sprintf(newrep, "%s %s", type, fname);
    out = strrep(getline, rep, newrep);

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
    out = strrep(out, GX_EQUAL, "==");
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
    out = strrep(out, GX_STRUCT, "struct");
    out = strrep(out, GX_MAIN, "main");
    out = strrep(out, GX_VOID, "void");
    out = strrep(out, GX_NULL, "NULL");
    out = strrep(out, GX_EXIT, "exit");
    out = strrep(out, GX_FUNCTION, "");

    /* Returns */
    out = strrep(out, GX_RETURN, "return");
    out = strrep(out, GX_RETINT, "int");
    out = strrep(out, GX_RETSTRING, "string");
    out = strrep(out, GX_RETDOUBLE, "double");
    out = strrep(out, GX_RETVOID, "void");

    return out;
}