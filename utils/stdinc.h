/*
 *  utils/stdinc.h
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * Standart includes.
 */


/* C includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <crypt.h>
#include <time.h>


/* Linux includes */
#include <netinet/in.h>
#include <sys/utsname.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>


/* Dependency includes */
#ifdef _OPENSSL_MD5_
#include <openssl/md5.h>
#endif