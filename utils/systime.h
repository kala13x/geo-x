/*
 *  utils/systime.h
 *
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 * 
 * Working with date. Get system date, calculate leap year and etc.
 */


/* Date variables */
typedef struct {
    int year; 
    int mon; 
    int day;
    int hour;
    int min;
    int sec;
} SystemDate;


/* Month days */
typedef struct {
    int month_days[13];
} MonthDays;


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/* 
 * alarm_handler - Handle alarm signal if and set up a 
 * timeout. Argument signal is timeout value in seconds.
 */
void alarm_handler(int signal);


/* 
 * setup_alarm_handler - Set up an alarm handler
 * for control alarm timeouts in application.
 */
void setup_alarm_handler();


/*
 * get_system_date - Intialize date with system date.
 * Argument is pointer of SystemDate structure.
 */
 void get_system_date(SystemDate *mdate);


/*
 * get_leap_year - Check year is leap or not. 
 * Argument is year on which we want calculate.
 */
int get_leap_year(int year);


/*
 * get_month_days - Intialize month days for year and calculate 
 * a leap year. Forst argument is pointer of MonthDays structure 
 * and second is year on which we want calculate.
 */
void get_month_days(MonthDays * mon, int year);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif