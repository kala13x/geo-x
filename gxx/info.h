/*
 *  utils/info.h
 *
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * Get additional information about library
 */


#define VERSION_MAX     0
#define VERSION_MIN     4
#define BUILD_NUMBER    31


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/* 
 * lib_version - Get library version. Function returns 
 * version, build number and build date of application. 
 * Return value is char pointer.
 */
const char* lib_version();


/* 
 * lib_version_short - Get library version. Function returns only
 * version, build number of application without additional strings. 
 * Return value is char pointer. For example: 1.0.32
 */
const char* lib_version_short();


/* 
 * greet - Print greeting message. Function returns program 
 * name, version, build number and build date. Argument 
 * p_name is program name from which we want to greet users. 
 */
void greet(char *p_name);


/*
 * Usage - Print usage information of compilator.
 * Argument fname is name of executable compiler. 
 */
void usage(char *fname);


/*
 * print_system_info - Get and print operating system information
 * such as system name, release, version, hardware identifier and etc.
 */
 void print_system_info();


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif