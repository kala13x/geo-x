/*
 *  compiler/keymap.h
 * 
 *  Copyleft (C) 2015  Geo-X Team
 *
 * This header includes world key maps for იქ-C compilator. 
 */


#include "mdefs.h"


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


/* Gx worlds map */
static char *gx_world_map[WORLDMAP_SIZE] = {GX_INCLUDE, GX_DEFINE, GX_ELSE_IF, GX_ELSE, 
            GX_IF, GX_WHILE, GX_FOR, GX_FOREACH, GX_DO, GX_BREAK, GX_GIVEVALUE, 
            GX_EQUAL, GX_AS, GX_INT, GX_LONG, GX_SHORT, GX_STRING, GX_DOUBLE, GX_SIGNED, 
            GX_UNSIGNED, GX_TYPEDEF, GX_STRUCT, GX_MAIN, GX_VOID, GX_NULL, GX_EXIT, 
            GX_FUNCTION, GX_RETURN, GX_RETINT, GX_RETSTRING, GX_RETDOUBLE, GX_RETVOID};


/* C worlds map */
static char *gxc_world_map[WORLDMAP_SIZE] = {"#include", "#define", "else if", "else", "if", 
            "while", "for", "foreach", "do", "break", "=", "==", "as", "int", "long", "short", 
            "char*", "double", "signed", "unsigned", "typedef", "struct", "main", "void", 
            "NULL", "exit(0)", "", "return", "int", "char*", "double", "void"};