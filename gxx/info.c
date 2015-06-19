/*
 *  utils/info.c
 *
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * Get additional information about library
 */


#include "../utils/slog.h"
#include "stdinc.h"
#include "info.h"


/* 
 * lib_version - Get library version. Function returns 
 * version, build number and build date of application. 
 * Return value is char pointer.
 */
const char* lib_version()
{
    static char str[128];
    sprintf(str, "%d.%d ბილდი %d (%s)", 
        VERSION_MAX, VERSION_MIN, BUILD_NUMBER, __DATE__);

    return str;
}


/* 
 * lib_version_short - Get library version. Function returns only
 * version, build number of application without additional strings. 
 * Return value is char pointer. For example: 1.0.32
 */
const char* lib_version_short()
{
    static char str[128];
    sprintf(str, "%d.%d.%d", 
        VERSION_MAX, VERSION_MIN, BUILD_NUMBER);

    return str;
}


/* 
 * greet - Print greeting message. Function returns program 
 * name, version, build number and build date. Argument 
 * p_name is program name from which we want to greet users. 
 */
void greet(char *p_name)
{
    printf("======================================================\n");
    printf("%s ვერსია: %s\n", p_name, lib_version());
    printf("======================================================\n");
}


/*
 * Usage - Print usage information of compilator.
 * Argument fname is name of executable compiler. 
 */
void usage(char *fname) 
{
    printf("\nგამოყყენების წესები: %s [-i <ფაილი>] [-o <ფაილი>] [-s] [-h]\n", fname);
    printf("წესების განმარტება:\n");
    printf("   -i <ფაილი>      # საწყისი კოდის ფაილის სახელი\n");
    printf("   -o <ფაილი>      # დაკომპლირებული/გამშვები ფაილის სახელი\n");
    printf("   -s              # შეინახე C ენაში გადათარგმნილი ფაილი\n");
    printf("   -h              # დაბეჭდე ვერსია და გამოყენების წესები\n");
    printf("\n");

}


/*
 * print_system_info - Get and print operating system information
 * such as system name, release, version, hardware identifier and etc.
 */
void print_system_info() 
{
    struct utsname udata;

    /* Get sys information */
    if (!uname(&udata))
    {
        slog(0, SLOG_INFO, "სისტემა: %s", udata.sysname);
        slog(0, SLOG_INFO, "ჰოსტი: %s", udata.nodename);
        slog(0, SLOG_INFO, "რელიზი: %s", udata.release);
        slog(0, SLOG_INFO, "ვერსია: %s", udata.version);
        slog(0, SLOG_INFO, "მანქანა: %s", udata.machine);

        #ifdef _GNU_SOURCE
        slog(0, SLOG_INFO, "დომეინი: %s", udata.domainname);
        #endif
    }
}