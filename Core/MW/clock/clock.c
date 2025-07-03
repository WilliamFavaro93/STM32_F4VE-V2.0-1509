/*
 * clock.c
 *
 *  Created on: 25 apr 2025
 *      Author: William
 */

#include "clock.h"
#include "time.h"

time_t time_;
struct tm *t;

void clock_set_datetime(uint32_t year)
{
	time_ = time(NULL);

    t->tm_year = year - 1900;  // Year since 1900
    t->tm_mon = 3;             // April (months start from 0)
    t->tm_mday = 25;
    t->tm_hour = 14;
    t->tm_min = 30;
    t->tm_sec = 0;

    time_ = mktime(t);
}

void clock_tick_s()
{
	time_++;
	t = localtime(&time_);
}

uint8_t clock_get_seconds()
{
	return t->tm_sec;
}
