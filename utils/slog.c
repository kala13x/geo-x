/*
 *  utils/slog.c
 *
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * slog is advanced logging library
 */


#include "stdinc.h"
#include "systime.h"
#include "files.h"
#include "color.h"
#include "slog.h"

/* Max buffer size of message */
#define MAXMSG 8196

/* Flags */
static slog_flags slg;


/* 
 * Get library version. Function returns version and build number of slog 
 * library. Return value is char pointer. Argument min is flag for output 
 * format. If min is 1, function returns version in full  format, if flag 
 * is 0 function returns only version numbers, For examle: 1.3.0
-*/
const char* slog_version(int min)
{
    static char verstr[128];

    /* Version short */
    if (min) sprintf(verstr, "%d.%d.%d", 
        SLOGVERSION_MAX, SLOGVERSION_MIN, SLOGBUILD_NUM);

    /* Version long */
    else sprintf(verstr, "%d.%d build %d (%s)", 
        SLOGVERSION_MAX, SLOGVERSION_MIN, SLOGBUILD_NUM, __DATE__);

    return verstr;
}


/*
 * log_to_file - Save log in file. Argument aut is string which
 * we want to log. Argument fname is log file path and mdate is 
 * SystemDate structure variable, we need it to create filename.
 */
void log_to_file(char *out, const char *fname, SystemDate *mdate) 
{
    /* Used variables */
    char filename[PATH_MAX];

    /* Create log filename with date */
    sprintf(filename, "%s-%02d-%02d-%02d.log", 
        fname, mdate->year, mdate->mon, mdate->day);

    /* Log to file */
    file_add_line(filename, out);
}


/*
 * parse_config - Parse config file. Argument cfg_name is path 
 * of config file name to be parsed. Function opens config file 
 * and parses LOGLEVEL and LOGTOFILE flags from it.
 */
int parse_config(const char *cfg_name)
{
    /* Used variables */
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int ret = 1;

    /* Open file pointer */
    file = fopen(cfg_name, "r");
    if(file == NULL) return 1;

    /* Line-by-line read cfg file */
    while ((read = getline(&line, &len, file)) != -1) 
    {
        /* Find level in file */
        if(strstr(line, "LOGLEVEL") != NULL) 
        {
            /* Get log level */
            slg.level = atoi(line+8);
            ret = 0;
        }
        else if(strstr(line, "LOGTOFILE") != NULL) 
        {
            /* Get log level */
            slg.to_file = atoi(line+9);
            ret = 0;
        }
    } 

    /* Cleanup */
    if (line) free(line);
    fclose(file);

    return ret;
}


/*
 * Retunr string in slog format. Function takes arguments 
 * and returns string in slog format without printing and 
 * saveing in file. Return value is char pointer.
 */
char* ret_slog(const char *msg, ...) 
{
    /* Used variables */
    static char output[MAXMSG];
    char string[MAXMSG];
    SystemDate mdate;

    /* initialise system date */
    get_system_date(&mdate);

    /* Read args */
    va_list args;
    va_start(args, msg);
    vsprintf(string, msg, args);
    va_end(args);

    /* Generate output string with date */
    sprintf(output, "%02d.%02d.%02d-%02d:%02d:%02d - %s", 
        mdate.year, mdate.mon, mdate.day, mdate.hour, 
        mdate.min, mdate.sec, string);

    /* Return output */
    return output;
}


/*
 * slog - Log exiting process. Function takes arguments and saves 
 * log in file if LOGTOFILE flag is enabled from config. Otherwise 
 * it just prints log without saveing in file. Argument level is 
 * logging level and flag is slog flags defined in slog.h header.
 */
void slog(int level, int flag, const char *msg, ...) 
{
    /* Used variables */
    SystemDate mdate;
    char string[MAXMSG];
    char prints[MAXMSG];
    char *output;

    /* Initialise system date */
    get_system_date(&mdate);

    /* Read args */
    va_list args;
    va_start(args, msg);
    vsprintf(string, msg, args);
    va_end(args);

    /* Check logging levels */
    if(level <= slg.level) 
    {
        /* Handle flags */
        switch(flag) {
            case 1:
                sprintf(prints, "[მიმდინარე]  %s", string);
                break;
            case 2:
                sprintf(prints, "[%s] %s", strclr(1, "ინფორმაცია"), string);
                break;
            case 3:
                sprintf(prints, "[%s] %s", strclr(3, "გაფრთხილება"), string);
                break;
            case 4:
                sprintf(prints, "[%s] %s", strclr(4, "დებაგი"), string);
                break;
            case 5:
                sprintf(prints, "[%s] %s", strclr(2, "შეცდომა"), string);
                break;
            case 6:
                sprintf(prints, "[%s] %s", strclr(2, "ფატალური"), string);
                break;
            case 7:
                sprintf(prints, "%s", string);
                break;
            default:
                break;
        }

        /* Print output */
        printf("%s", ret_slog("%s\n", prints));

        /* Save log in file */
        if (slg.to_file) 
        {
            output = ret_slog("%s\n", string);
            log_to_file(output, slg.fname, &mdate);
        }
    }
}


/*
 * Initialize slog library. Function parses config file and reads log 
 * level and save to file flag from config. First argument is file name 
 * where log will be saved and second argument conf is config file path 
 * to be parsedand third argument lvl is log level for this message.
 */
void init_slog(const char* fname, const char* conf, int lvl) 
{
    slg.level = lvl;
    slg.fname = fname;
    slg.to_file = 0;

    /* Parse config file */
    if (parse_config(conf)) 
    {
        slog(0, SLOG_WARN, "LOGLEVEL and/or LOGTOFILE flag is not set from config.");

        return;
    }
}
