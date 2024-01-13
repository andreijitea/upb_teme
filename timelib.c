#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"


TTime convertUnixTimestampToTime(unsigned int timestamp) {
	TTime result;

	result.sec = timestamp % 60;
	result.min = (timestamp / 60) % 60;
	result.hour = (timestamp / 3600) % 24;

	return result;
}


TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
	TDate result;
	result.day = 1;
	result.month = 1;
	result.year = 1970;
	int total_days = timestamp / 86400;
	char days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	for (; result.month <= 12; result.month++) {
		total_days -= days_in_month[result.month];
		if (total_days < 0)
			break;
		
		if (result.month == 12) {
			result.month = 0;
			result.year++;
		}
	}
	result.day += days_in_month[result.month] + total_days;

	return result;
}

int isLeapYear(int year) {
	return ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0));
}

TDate convertUnixTimestampToDate(unsigned int timestamp) {
	TDate result;
	result.day = 1;
	result.month = 1;
	result.year = 1970;
	int total_days = timestamp / 86400;
	char days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	for (; result.month <= 12; result.month++) {
		if (result.month == 2) {
			if (isLeapYear(result.year))
				total_days -= 29;
			else
				total_days -= 28;
		} else {
			total_days -= days_in_month[result.month];
			if (total_days < 0)
				break;
		
			if (result.month == 12) {
				result.month = 0;
				result.year++;
			}
		}

	}
	result.day += days_in_month[result.month] + total_days;

	return result;
}


TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
	TDateTimeTZ result;
	timestamp += timezones[timezone_index].utc_hour_difference * 3600;
	result.date = convertUnixTimestampToDate(timestamp);
	result.time = convertUnixTimestampToTime(timestamp);
	
	result.tz = &timezones[timezone_index];

	return result;
}

// TODO Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ datetimetz) {
	char days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	unsigned int timestamp = 0;

	for (int y = 1970; y < datetimetz.date.year; y++) {
		if (isLeapYear(y))
			timestamp += 366 * 86400;
		else
			timestamp += 365 * 86400;
	}
	for (int m = 1; m < datetimetz.date.month; m++) {
		timestamp += days_in_month[m] * 86400;
		if (m == 2 && isLeapYear(datetimetz.date.year))
			timestamp += 86400;
	}
	for (int d = 1; d < datetimetz.date.day; d++) {
		timestamp += 86400;
	}
	timestamp += datetimetz.time.hour * 3600 + datetimetz.time.min * 60 + datetimetz.time.sec;
	timestamp -= datetimetz.tz->utc_hour_difference * 3600;
	return timestamp;
}


void printDateTimeTZ(TDateTimeTZ datetimetz) {
	char months[12][20] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie", "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
	printf("%d %s %d, %d:%d:%d %s (UTC%+d)\n", datetimetz.date.day,
											months[datetimetz.date.month-1],
											datetimetz.date.year,
											datetimetz.time.hour,
											datetimetz.time.min,
											datetimetz.time.sec,
											datetimetz.tz->name,
											datetimetz.tz->utc_hour_difference);
}
