/*
 *  utils/systime.c
 *
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 * 
 * Working with date. Get system date, calculate leap year and etc.
 */


#include "stdinc.h"
#include "errex.h"
#include "systime.h"

/* Publics */
static sig_atomic_t alarm_counter;


/* 
 * alarm_handler - Handle alarm signal if and set up a 
 * timeout. Argument signal is timeout value in seconds.
 */
void alarm_handler(int signal) {
    alarm_counter++;
}


/* 
 * setup_alarm_handler - Set up an alarm handler
 * for control alarm timeouts in application.
 */
void setup_alarm_handler() 
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = alarm_handler;
    sa.sa_flags = 0;

    if (sigaction(SIGALRM, &sa, 0) < 0)
        exit_prog(1, "Can't establish signal handler");
}


/*
 * get_system_date - Intialize date with system date.
 * Argument is pointer of SystemDate structure.
 */
 void get_system_date(SystemDate *mdate) 
{
    time_t rawtime;
    struct tm *timeinfo;
    rawtime = time(NULL);
    timeinfo = localtime(&rawtime);

    /* Get System Date */
    mdate->year = timeinfo->tm_year+1900;
    mdate->mon = timeinfo->tm_mon+1;
    mdate->day = timeinfo->tm_mday;
    mdate->hour = timeinfo->tm_hour;
    mdate->min = timeinfo->tm_min;
    mdate->sec = timeinfo->tm_sec;
}


/*
 * get_leap_year - Check year is leap or not. 
 * Argument is year on which we want calculate.
 */
int get_leap_year(int year) 
{
    int ret;

    /* Get a leap year */
    if(year%4 == 0)
    {
        if(year%100 == 0)
        {
            if (year%400 == 0) ret = 1;
            else ret = 0;
        }
        else ret = 1;
    }
    else ret = 0;

    return ret;
}


/*
 * get_month_days - Intialize month days for year and calculate 
 * a leap year. Forst argument is pointer of MonthDays structure 
 * and second is year on which we want calculate.
 */
void get_month_days(MonthDays * mon, int year)
{
    /* Get a leap year */
    int leap = get_leap_year(year);
    if (leap) mon->month_days[2] = 28;
    else mon->month_days[2] = 29;

    /* Initialise month days */
    mon->month_days[0] = 31;
    mon->month_days[1] = 31;
    mon->month_days[3] = 31;
    mon->month_days[4] = 30;
    mon->month_days[5] = 31;
    mon->month_days[6] = 30;
    mon->month_days[7] = 31;
    mon->month_days[8] = 31;
    mon->month_days[9] = 30;
    mon->month_days[10] = 31;
    mon->month_days[11] = 30;
    mon->month_days[12] = 31;
}
