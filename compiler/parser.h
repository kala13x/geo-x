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
 * parse_basic_types - Parse basic types from line. 
 * Argument line is line which we want to parse.
 */
char* parse_basic_types(char * line);
/**
*
*/
char * parser_route(char * line);
/*
*
*/
char * parse_include(char * line);

/* For include header in CPP code */
#ifdef __cplusplus
}
#endif