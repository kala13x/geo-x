/*
 *  utils/crypts.h
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * This source includes crypt operations on strings.
 * Use GCC for compilation.
 */


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * simple_decrypt - Simple dencryption of string which was recently
 * crypted with simple_crypt. Argument str is stryng which we want 
 * to encrypt. Return value is encrypted string.
 */
char* simple_decrypt(char *str);


/*
 * simple_crypt - Simple encryption of string. Function takes string, 
 * encrypts it with hex key and returns as char pointer. Argument str
 * is stryng which we want to encrypt. Return value is encrypted string.
 */
char* simple_crypt(char *str);


#ifdef _OPENSSL_MD5_
/* 
 * md5_crypt - Generate 32bit MDd key with OpenSSL MD5 function. Argument 
 * str is string which we want to crypt and return value is char pointer 
 * of the crypted string. Crypted string with strcrypt, can not be decrypted.
 */
char* md5_crypt(char *str);


/* 
 * rand_md5_crypt - Generate random 32bit MD5 key with OpenSSL 
 * MD5 function. Argument str is string which we want to crypt 
 * and return value is char pointer of the crypted string. 
 * Crypted string with strcrypt, can not be decrypted.
 */
char* rand_md5_crypt(char *str);
#endif


/*
 * strcrypt - Crypt string with gnu c crypt library.
 * Argument str is string which we want to crypt and
 * return value is char pointer of the crypted string.
 * Crypted string with strcrypt, can not be decrypted.
 */
char* strcrypt(char* str);


/*
 * rand_crypt - Crypt string with gnu c crypt library. Functyon encrypts string 
 * with random seedchars, so result will be diiferent on evey use with some string. 
 * Argument str is string which we want to crypt and return value is char pointer 
 * of the crypted string. Crypted string with strcrypt, can not be decrypted.
 */
char* rand_crypt(char* str);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif