/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
 */

/*
 * @* Implementation
 *
 * @+ Atoms
 *
 * @- date
 * Internally, we store date as the (possibly negative) number of days
 * since the start of the calendar. Oddly, since I (later) learned
 * that the year 0 did no exist, this defines the start of the
 * calendar to be Jan 1 of the year -1 (in other words, a -- positive
 * -- year component of a date is equal to the number of years that
 * have passed since the start of the calendar).
 */
#ifndef _MONETTIME_H_
#define _MONETTIME_H_

#include "gdk.h"
#include "mal.h"
#include "mal_exception.h"

#include <time.h>

#ifdef HAVE_FTIME
#include <sys/timeb.h>		/* ftime */
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>		/* gettimeofday */
#endif

#define YEAR_MIN		(-4712)	/* 4713 BC */
#define YEAR_MAX		(YEAR_MIN+(1<<21)/12)

typedef int date;
#define date_nil		((date) int_nil)
#define is_date_nil(X)	((X) == date_nil)

/*
 * @- daytime
 * Daytime values are also stored as the number of milliseconds that
 * passed since the start of the day (i.e. midnight).
 */
typedef lng daytime;
#define daytime_nil		((daytime) lng_nil)
#define is_daytime_nil(X) ((X) == daytime_nil)
/* it should never overflow */

/*
 * @- timestamp
 * Timestamp is implemented as a record that contains a date and a time (GMT).
 */
typedef lng timestamp;
#define timestamp_nil	((timestamp) {lng_nil})
#define is_timestamp_nil(X)	((X) == timestamp_nil)

mal_export ssize_t daytime_tz_fromstr(const char *buf, size_t *len, daytime **ret, bool external);
mal_export ssize_t timestamp_tz_fromstr(const char *buf, size_t *len, timestamp **ret, bool external);
mal_export str MTIMEcurrent_timestamp(timestamp *t);
mal_export str MTIMEcurrent_date(date *d);
mal_export str MTIMEcurrent_time(daytime *t);
mal_export str MTIMEnil2date(date *ret, const void *src);
mal_export str MTIMEdate2date(date *ret, const date *src);
mal_export str MTIMEdaytime2daytime(daytime *ret, const daytime *src);
mal_export str MTIMEsecs2daytime(daytime *ret, const lng *src);
mal_export str MTIMEsecs2daytime_bulk(bat *ret, bat *bid);
mal_export str MTIMEtimestamp2timestamp(timestamp *ret, const timestamp *src);
mal_export void MTIMEreset(void);
mal_export str MTIMEprelude(void *ret);
mal_export str MTIMEepilogue(void *ret);
mal_export str MTIMEsynonyms(void *ret, const bit *allow);
mal_export str MTIMEmonth_from_str(int *ret, const char * const *month);
mal_export str MTIMEmonth_to_str(str *ret, const int *month);
mal_export str MTIMEday_from_str(int *ret, const char * const *day);
mal_export str MTIMEday_to_str(str *ret, const int *day);
mal_export str MTIMEdate_date(date *d, const date *s);
mal_export str MTIMEdate_fromstr(date *ret, const char * const *s);
mal_export str MTIMEdate_create(date *ret, const int *year, const int *month, const int *day);
mal_export str MTIMEdaytime_create(daytime *ret, const int *hour, const int *min, const int *sec, const int *msec);
mal_export str MTIMEtimestamp_fromstr(timestamp *ret, const char * const *d);
mal_export str MTIMEtimestamp_create(timestamp *ret, const date *d, const daytime *t);
mal_export str MTIMEtimestamp_create_from_date(timestamp *ret, const date *d);
mal_export str MTIMEtimestamp_create_from_date_bulk(bat *ret, bat *bid);
mal_export str MTIMEdate_extract_year(int *ret, const date *v);
mal_export str MTIMEdate_extract_quarter(int *ret, const date *v);
mal_export str MTIMEdate_extract_month(int *ret, const date *v);
mal_export str MTIMEdate_extract_day(int *ret, const date *v);
mal_export str MTIMEdate_extract_dayofyear(int *ret, const date *v);
mal_export str MTIMEdate_extract_weekofyear(int *ret, const date *v);
mal_export str MTIMEdate_extract_dayofweek(int *ret, const date *v);
mal_export str MTIMEdaytime_extract_hours(int *ret, const daytime *v);
mal_export str MTIMEdaytime_extract_minutes(int *ret, const daytime *v);
mal_export str MTIMEdaytime_extract_seconds(int *ret, const daytime *v);
mal_export str MTIMEdaytime_extract_sql_seconds(int *ret, const daytime *v);
mal_export str MTIMEdaytime_extract_milliseconds(int *ret, const daytime *v);
mal_export str MTIMEtimestamp_extract_daytime(daytime *ret, const timestamp *t);
mal_export str MTIMEtimestamp_extract_daytime_bulk(bat *ret, bat *bid);
mal_export str MTIMEtimestamp_extract_date(date *ret, const timestamp *t);
mal_export str MTIMEtimestamp_extract_date_bulk(bat *ret, bat *bid);
mal_export str MTIMEdate_addyears(date *ret, const date *v, const int *delta);
mal_export str MTIMEdate_adddays(date *ret, const date *v, const int *delta);
mal_export str MTIMEdate_addmonths(date *ret, const date *v, const int *delta);
mal_export str MTIMEdate_submonths(date *ret, const date *v, const int *delta);
mal_export str MTIMEdate_diff(int *ret, const date *v1, const date *v2);
mal_export str MTIMEdate_diff_bulk(bat *ret, const bat *bid1, const bat *bid2);
mal_export str MTIMEtimestamp_add(timestamp *ret, const timestamp *v, const lng *msec);
mal_export str MTIMEdaytime_diff(lng *ret, const daytime *v1, const daytime *v2);
mal_export str MTIMEtimestamp_diff(lng *ret, const timestamp *v1, const timestamp *v2);
mal_export str MTIMEtimestamp_diff_bulk(bat *ret, const bat *bid1, const bat *bid2);
mal_export str MTIMEepoch2lng(lng *res, const timestamp *ts);
mal_export str MTIMEepoch_bulk(bat *ret, bat *bid);

mal_export str MTIMEtimestamp_year(int *ret, const timestamp *t);
mal_export str MTIMEtimestamp_quarter(int *ret, const timestamp *t);
mal_export str MTIMEtimestamp_month(int *ret, const timestamp *t);
mal_export str MTIMEtimestamp_day(int *ret, const timestamp *t);
mal_export str MTIMEtimestamp_hours(int *ret, const timestamp *t);
mal_export str MTIMEtimestamp_minutes(int *ret, const timestamp *t);
mal_export str MTIMEtimestamp_seconds(int *ret, const timestamp *t);
mal_export str MTIMEtimestamp_sql_seconds(int *ret, const timestamp *t);
mal_export str MTIMEtimestamp_milliseconds(int *ret, const timestamp *t);
mal_export str MTIMEsql_year(int *ret, const int *t);
mal_export str MTIMEsql_month(int *ret, const int *t);
mal_export str MTIMEsql_day(lng *ret, const lng *t);
mal_export str MTIMEsql_hours(int *ret, const lng *t);
mal_export str MTIMEsql_minutes(int *ret, const lng *t);
mal_export str MTIMEsql_seconds(int *ret, const lng *t);

mal_export str MTIMEdate_sub_sec_interval_wrap(date *ret, const date *t, const int *sec);
mal_export str MTIMEdate_sub_msec_interval_lng_wrap(date *ret, const date *t, const lng *msec);
mal_export str MTIMEdate_add_sec_interval_wrap(date *ret, const date *t, const int *sec);
mal_export str MTIMEdate_add_msec_interval_lng_wrap(date *ret, const date *t, const lng *msec);
mal_export str MTIMEtimestamp_sub_msec_interval_lng_wrap(timestamp *ret, const timestamp *t, const lng *msec);
mal_export str MTIMEtimestamp_sub_month_interval_wrap(timestamp *ret, const timestamp *t, const int *months);
mal_export str MTIMEtimestamp_add_month_interval_wrap(timestamp *ret, const timestamp *t, const int *months);
mal_export str MTIMEtimestamp_sub_month_interval_lng_wrap(timestamp *ret, const timestamp *t, const lng *months);
mal_export str MTIMEtimestamp_add_month_interval_lng_wrap(timestamp *ret, const timestamp *t, const lng *months);
mal_export str MTIMEtime_sub_msec_interval_wrap(daytime *ret, const daytime *t, const lng *msec);
mal_export str MTIMEtime_add_msec_interval_wrap(daytime *ret, const daytime *t, const lng *msec);
mal_export str MTIMEdaytime_fromstr(daytime *ret, const char * const *s);
mal_export str MTIMEmsecs(lng *ret, const int *d, const int *h, const int *m, const int *s, const int *ms);
mal_export str MTIMEmsec(lng *r);
mal_export str MTIMEdaytime1(daytime *ret, const int *h);
mal_export str MTIMEdaytime2(daytime *ret, const int *h, const int *m);
mal_export str MTIMEdaytime3(daytime *ret, const int *h, const int *m, const int *s);
mal_export str MTIMEunix_epoch(timestamp *ret);
mal_export str MTIMEepoch2int(int *res, const timestamp *ts);
mal_export str MTIMEtimestamp(timestamp *ret, const int *sec);
mal_export str MTIMEtimestamplng(timestamp *ret, const lng *sec);
mal_export str MTIMEtimestamp_bulk(bat *ret, bat *bid);
mal_export str MTIMEtimestamp_lng(timestamp *ret, const lng *msec);
mal_export str MTIMEtimestamp_lng_bulk(bat *ret, bat *bid);
mal_export ssize_t date_fromstr(const char *buf, size_t *len, date **d, bool external);
mal_export ssize_t date_tostr(str *buf, size_t *len, const date *val, bool external);
mal_export ssize_t daytime_fromstr(const char *buf, size_t *len, daytime **ret, bool external);
mal_export ssize_t daytime_tostr(str *buf, size_t *len, const daytime *val, bool external);
mal_export ssize_t timestamp_fromstr(const char *buf, size_t *len, timestamp **ret, bool external);
mal_export ssize_t timestamp_tostr(str *buf, size_t *len, const timestamp *val, bool external);

mal_export str MTIMEstr_to_date(date *d, const char * const *s, const char * const *format);
mal_export str MTIMEdate_to_str(str *s, const date *d, const char * const *format);
mal_export str MTIMEstr_to_time(daytime *d, const char * const *s, const char * const *format);
mal_export str MTIMEtime_to_str(str *s, const daytime *d, const char * const *format);
mal_export str MTIMEstr_to_timestamp(timestamp *d, const char * const *s, const char * const *format);
mal_export str MTIMEtimestamp_to_str(str *s, const timestamp *d, const char * const *format);

mal_export str MTIMEdate_extract_year_bulk(bat *ret, const bat *bid);
mal_export str MTIMEdate_extract_quarter_bulk(bat *ret, const bat *bid);
mal_export str MTIMEdate_extract_month_bulk(bat *ret, const bat *bid);
mal_export str MTIMEdate_extract_day_bulk(bat *ret, const bat *bid);


mal_export str MTIMEdaytime_extract_hours_bulk(bat *ret, const bat *bid);
mal_export str MTIMEdaytime_extract_minutes_bulk(bat *ret, const bat *bid);
mal_export str MTIMEdaytime_extract_seconds_bulk(bat *ret, const bat *bid);
mal_export str MTIMEdaytime_extract_sql_seconds_bulk(bat *ret, const bat *bid);
mal_export str MTIMEdaytime_extract_milliseconds_bulk(bat *ret, const bat *bid);

mal_export int TYPE_date;
mal_export int TYPE_daytime;
mal_export int TYPE_timestamp;

mal_export date MTIMEtodate(int year, int month, int day);
mal_export void MTIMEfromdate(date n, int *y, int *m, int *d);
mal_export daytime MTIMEtotime(int hour, int min, int sec, int msec);
mal_export void MTIMEfromtime(daytime n, int *hour, int *min, int *sec, int *msec);
mal_export timestamp MTIMEtotimestamp(int year, int month, int day, int hour, int min, int sec, int msec);
mal_export void MTIMEfromtimestamp(timestamp t, int *Y, int *M, int *D, int *h, int *m, int *s, int *ms);

mal_export str MTIMEanalyticalrangebounds(BAT *r, BAT *b, BAT *p, BAT *l, const void* restrict bound, int tp1, int tp2,
										  bool preceding, lng first_half);

#endif /* _MONETTIME_H_ */
