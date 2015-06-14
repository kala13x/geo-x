/*
 *  compiler/parser.h
 * 
 *  Copyleft (C) 2015  Geo-X Team
 *
 * Header of source parser for იქ-C compilator. 
 */


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/* 
 * translate_alphabet - Translate alpabhet from georgian to english.
 * Agument line is parsed file line in which we want to translate.
 */
char* translate_alphabet(char * line);


/* 
 * parse_includes - Parse include definitions from source.
 * Argument line is line from source code we want to parse.
 */
char* parse_includes(char *line);


/* 
 * parse_includes - Parse reserved words from source code.
 * Argument line is line from source code we want to parse.
 */
char* parse_reserved(char * line);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif