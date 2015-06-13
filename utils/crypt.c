/*
 *  utils/crypt.c
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * This source includes crypt operations on strings.
 * Use GCC for compilation.
 */


#include "stdinc.h"
#include "systime.h"
#include "crypt.h"


/*
 * simple_decrypt - Simple dencryption of string which was recently
 * crypted with simple_crypt. Argument str is stryng which we want 
 * to encrypt. Return value is encrypted string.
 */
char* simple_decrypt(char *str) 
{
    /* Used variables */
    char* decrypted;
    unsigned int i;
    int key = 0xFACA;

    /* Decrypt */
    for(i=0;i<strlen(str);++i)
    {
        str[i] = str[i] + key;
    }
    decrypted = strdup(str);

    return decrypted;
}


/*
 * simple_crypt - Simple encryption of string. Function takes string, 
 * encrypts it with hex key and returns as char pointer. Argument str
 * is stryng which we want to encrypt. Return value is encrypted string.
 */
char* simple_crypt(char *str)
{
    /* Used variables */
    unsigned int i;
    int key = 0xFACA;
    char *crypted;

    /* Crypt */
    for(i=0;i<strlen(str);++i)
    {
        str[i] = str[i] - key;
    }
    crypted = strdup(str);

    return crypted;
}


#ifdef _OPENSSL_MD5_
/* 
 * md5_crypt - Generate 32bit MDd key with OpenSSL MD5 function. Argument 
 * str is string which we want to crypt and return value is char pointer 
 * of the crypted string. Crypted string with strcrypt, can not be decrypted.
 */
char* md5_crypt(char *str)
{
    /* Used variables */
    char *out = (char*)malloc(33);
    unsigned char digest[16];
    MD5_CTX context;
    int i;

    /* Initialise md5 context */    
    MD5_Init(&context);
    MD5_Update(&context, str, strlen(str));

    /* Get integer representation of the hash */
    MD5_Final(digest, &context);

    /* Pass hash around as a string */
    for(i = 0; i < 16; ++i)
        sprintf(&out[i*2], "%02x", (unsigned int)digest[i]);

    return out;
}


/* 
 * rand_md5_crypt - Generate random 32bit MD5 key with OpenSSL 
 * MD5 function. Argument str is string which we want to crypt 
 * and return value is char pointer of the crypted string. 
 * Crypted string with strcrypt, can not be decrypted.
 */
char* rand_md5_crypt(char *str)
{
    /* Used variables */
    char *out;
    SystemDate mdate;

    /* Get system time */
    get_system_date(&mdate);

    /* Write system time in string for crypt */
    sprintf(str, "%s%02d%02d%02d%02d%02d", 
        str, mdate.day, mdate.mon, 
        mdate.year, mdate.min, mdate.sec);

    /* Encrypt string */
    out = md5_crypt(str);

    return out;
}
#endif


/*
 * strcrypt - Crypt string with gnu c crypt library.
 * Argument str is string which we want to crypt and
 * return value is char pointer of the crypted string.
 * Crypted string with strcrypt, can not be decrypted.
 */
char* strcrypt(char* str)
{
    /* Used Variables */
    unsigned long seed[2];
    char *crypted;
    int i;

    /* Salt */
    char salt[] = "$1$..............";

    /* Seedchars */
    const char *const seedchars = 
    "./0123456789ABCDEFGHIJKLMNOPQRST"                                
    "UVWXYZabcdefghijklmnopqrstuvwxyz";

    /* Generate a (not very) random seed */
    seed[0] = 1920 * 69 * 13;
    seed[1] = 3321 ^ (seed[0] >> 14 & 0x30000);

    /* Turn it into printable characters from ‘seedchars’ */
    for (i = 0; i < 8; i++)
        salt[3+i] = seedchars[(seed[i/5] >> (i%5)*6) & 0x3f];

    /* Encrypt it */
    crypted = crypt(str, salt);

    /* Remove salt */
    sscanf(crypted, "$1$.SY4.tn.$%[^:]:", crypted);

    return crypted;
}


/*
 * rand_crypt - Crypt string with gnu c crypt library. Functyon encrypts string 
 * with random seedchars, so result will be diiferent on evey use with some string. 
 * Argument str is string which we want to crypt and return value is char pointer 
 * of the crypted string. Crypted string with strcrypt, can not be decrypted.
 */
char* rand_crypt(char* str)
{
    /* Used variables */
    char *out;
    SystemDate mdate;

    /* Get system time */
    get_system_date(&mdate);

    /* Write system time in string for crypt */
    sprintf(str, "%s%02d%02d%02d%02d%02d", 
        str, mdate.day, mdate.mon, 
        mdate.year, mdate.min, mdate.sec);

    /* Encrypt string */
    out = strcrypt(str);

    return out;
}
