/*
 *  compiler/parser.c
 * 
 *  Copyleft (C) 2015  Geo-X Team
 *
 * Source parser for იქ-C compilator. 
 */


#include "stdinc.h"
#include "mdefs.h"
#include "../utils/strops.h" 
#include "../utils/slog.h" 
char * translate(char * line)
{
    line = strrep(line, "ა", "a");
    line = strrep(line, "ბ", "b");
    line = strrep(line, "გ", "g");
    line = strrep(line, "დ", "d");
    line = strrep(line, "ე", "e");
    line = strrep(line, "ვ", "v");
    line = strrep(line, "ზ", "z");
    line = strrep(line, "თ", "t");
    line = strrep(line, "ი", "i");
    line = strrep(line, "კ", "k");
    line = strrep(line, "ლ", "l");
    line = strrep(line, "მ", "m");
    line = strrep(line, "ნ", "n");
    line = strrep(line, "ო", "o");
    line = strrep(line, "პ", "p");
    line = strrep(line, "ჟ", "zh");
    line = strrep(line, "რ", "r");
    line = strrep(line, "ს", "s");
    line = strrep(line, "ტ", "t");
    line = strrep(line, "ფ", "f");
    line = strrep(line, "ქ", "q");
    line = strrep(line, "ღ", "gh");
    line = strrep(line, "ყ", "y");
    line = strrep(line, "შ", "sh");
    line = strrep(line, "ჩ", "ch");
    line = strrep(line, "ძ", "dz");
    line = strrep(line, "წ", "w");
    line = strrep(line, "ხ", "x");
    line = strrep(line, "ჯ", "j");
    line = strrep(line, "ჰ", "h");

    return line;

}
char * parseBasicTypes(char * line)
{
    char * out;
    char * array[100];
    char dubLine[512];
    bzero(dubLine, sizeof(dubLine));
    strcpy(dubLine,line);
    int i=0;
    array[i] = strtok(dubLine," ");
    while(array[i]!=NULL)
    {
       array[++i] = strtok(NULL," ");
    }

    char * array2[10];
    int i2=0;
    array2[i2] = strtok(array[i-1],"=");
    while(array2[i2]!=NULL)
    {
       array2[++i2] = strtok(NULL,"=");
       slog(0,SLOG_LIVE,"%s -> %d",array2[i2-1],(i2-1));
    }


    out = strrep(line,(char *) array2[0],translate(array2[0]));
    out = strrep(out, (char *) gx_string, "char");
    out = strrep(out, (char *) gx_int, "int");
    out = strrep(out, (char *) gx_signed, "signed");
    out = strrep(out, (char *) gx_unsigned, "unsigned");
    out = strrep(out, (char *) gx_short, "short");
    out = strrep(out, (char *) gx_long, "long");
    out = strrep(out, (char *) gx_double, "double");

    return out;
}