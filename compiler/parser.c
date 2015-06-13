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
    char *out;
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
    out = strrep(out, "ფ", "f");
    out = strrep(out, "ქ", "q");
    out = strrep(out, "ღ", "gh");
    out = strrep(out, "ყ", "y");
    out = strrep(out, "შ", "sh");
    out = strrep(out, "ჩ", "ch");
    out = strrep(out, "ძ", "dz");
    out = strrep(out, "წ", "w");
    out = strrep(out, "ხ", "x");
    out = strrep(out, "ჯ", "j");
    out = strrep(out, "ჰ", "h");

    return line;
}


/* 
 * parse_basic_types - Parse basic types from line. 
 * Argument line is line which we want to parse.
 */
char* parse_basic_types(char * line)
{
    char dubline[MAXMSG];
    char *out;
    char *array[100];
    char *array2[10];
    int i2 = 0, i = 0;
    
    bzero(dubline, sizeof(dubline));
    strcpy(dubline, line);
    
    /* Parse with space */
    array[i] = strtok(dubline," ");
    while(array[i]!=NULL) array[++i] = strtok(NULL," ");
    
    /* Parse with equal simbol */
    array2[i2] = strtok(array[i-1],"=");
    while(array2[i2]!=NULL)
    {
       array2[++i2] = strtok(NULL,"=");
       slog(0,SLOG_LIVE,"%s -> %d",array2[i2-1],(i2-1));
    }

    /* C-fy parsed types in line */
    out = strrep(line, array2[0], translate_alphabet(array2[0]));
    out = strrep(out, GX_STRING, "char");
    out = strrep(out, GX_INT, "int");
    out = strrep(out, GX_SIGNED, "signed");
    out = strrep(out, GX_UNSIGNED, "unsigned");
    out = strrep(out, GX_SHORT, "short");
    out = strrep(out, GX_LONG, "long");
    out = strrep(out, GX_DOUBLE, "double");

    return out;
}