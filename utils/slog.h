/*
 *  utils/slog.h
 *
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * slog is advanced logging library
 */


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/* Definations for version info */
#define SLOGVERSION_MAX  1
#define SLOGVERSION_MIN  3
#define SLOGBUILD_NUM    67

/* Loging flags */
#define SLOG_LIVE   1
#define SLOG_INFO   2
#define SLOG_WARN   3
#define SLOG_DEBUG  4
#define SLOG_ERROR  5
#define SLOG_FATAL  6
#define SLOG_NONE   7

/* Flags */
typedef struct {
    const char* fname;
    int level;
    int to_file;
} slog_flags;


/* 
 * Get library version. Function returns version and build number of slog 
 * library. Return value is char pointer. Argument min is flag for output 
 * format. If min is 1, function returns version in full  format, if flag 
 * is 0 function returns only version numbers, For examle: 1.0.52.
-*/
const char* slog_version(int min);


/*
 * Initialize slog library. Function parses config file and reads log 
 * level and save to file flag from config. First argument is file name 
 * where log will be saved and second argument conf is config file path 
 * to be parsedand third argument lvl is log level for this message.
 */
void init_slog(const char* fname, const char *conf, int lvl);


/*
 * Retunr string in slog format. Function takes arguments 
 * and returns string in slog format without printing and 
 * saveing in file. Return value is char pointer.
 */
char* ret_slog(const char *msg, ...);


/*
 * slog - Log exiting process. Function takes arguments and saves 
 * log in file if LOGTOFILE flag is enabled from config. Otherwise 
 * it just prints log without saveing in file. Argument level is 
 * logging level and flag is slog flags defined in slog.h header.
 */
void slog(int level, int flag, const char *msg, ...);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif
