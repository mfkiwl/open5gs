/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ogs-core.h"
#include "core/abts.h"

/* 2002-09-14 12:05:36.186711 -25200 [257 Sat]. */
static ogs_time_t now = 1032030336186711L;
/* 2012-08-11 16:00:55.151600 -14400 [224 Sat] DST */
static ogs_time_t leap_year_now = 1344715255151600L;

#define STR_SIZE 100

static void test_now(abts_case *tc, void *data)
{
    struct timeval tv;
    time_t timediff;
    time_t current;
    time_t os_now;

    ogs_gettimeofday(&tv);
    current = tv.tv_sec;
    time(&os_now);

    timediff = os_now - current;
    ABTS_ASSERT(tc, "ogs_gettimeofday() and time() do not agree",
            (timediff > -2) && (timediff < 2));
}

static void test_gmtstr(abts_case *tc, void *data)
{
    char buf[OGS_TIME_ISO8601_FORMATTED_LENGTH];
    struct tm xt;

    ogs_gmtime(ogs_time_sec(now), &xt);
    ogs_strftime(buf, OGS_TIME_ISO8601_FORMATTED_LENGTH,
            OGS_TIME_ISO8601_FORMAT, &xt);
    ABTS_STR_EQUAL(tc, "2002-09-14T19:05:36+0000", buf);
}

static void test_get_gmt(abts_case *tc, void *data)
{
    int rv;
    struct tm xt;
    ogs_time_t imp;
    int64_t hr_off_64;

    ogs_gmtime(ogs_time_sec(now), &xt);
    rv = ogs_time_get(&imp, &xt, ogs_time_usec(now));
    ABTS_TRUE(tc, rv == OGS_OK);
    hr_off_64 = (int64_t) xt.tm_gmtoff * OGS_USEC_PER_SEC;
    ABTS_TRUE(tc, now + hr_off_64 == imp);
}

static void test_get_lt(abts_case *tc, void *data)
{
    int rv;
    struct tm xt;
    ogs_time_t imp;
    int64_t hr_off_64;

    ogs_localtime(ogs_time_sec(now), &xt);
    rv = ogs_time_get(&imp, &xt, ogs_time_usec(now));
    ABTS_TRUE(tc, rv == OGS_OK);
    hr_off_64 = (int64_t) xt.tm_gmtoff * OGS_USEC_PER_SEC;
    ABTS_TRUE(tc, now + hr_off_64 == imp);
}

static void test_imp_gmt(abts_case *tc, void *data)
{
    int rv;
    struct tm xt;
    ogs_time_t imp;

    ogs_gmtime(ogs_time_sec(now), &xt);
    rv = ogs_time_gmt_get(&imp, &xt, ogs_time_usec(now));
    ABTS_TRUE(tc, rv == OGS_OK);
    ABTS_TRUE(tc, now == imp);
}

static void test_strftime(abts_case *tc, void *data)
{
    struct tm tm;
    char str[STR_SIZE+1];
    time_t now = (time_t)1542100786;

    ogs_gmtime(now, &tm);
    ogs_strftime(str, sizeof str, "%Y/%m/%d %H:%M:%S", &tm);
    ABTS_STR_EQUAL(tc, "2018/11/13 09:19:46", str);

    ogs_localtime(now, &tm);
    ogs_strftime(str, sizeof str, "%Y/%m/%d %H:%M:%S", &tm);
#if 0 /* FIXME */
    ABTS_STR_EQUAL(tc, "2018/11/13 18:19:46", str);
#endif
}

abts_suite *test_time(abts_suite *suite)
{
    suite = ADD_SUITE(suite)

    abts_run_test(suite, test_now, NULL);
    abts_run_test(suite, test_gmtstr, NULL);
    abts_run_test(suite, test_get_gmt, NULL);
    abts_run_test(suite, test_get_lt, NULL);
    abts_run_test(suite, test_imp_gmt, NULL);
    abts_run_test(suite, test_strftime, NULL);

    return suite;
}
