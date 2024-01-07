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


TDate convertUnixTimestampToDate(unsigned int timestamp) {
	TDate result;
	result.day = 1;
	result.month = 1;
	result.year = 1970;
	int total_days = timestamp / 86400;
	char days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	for (; result.month <= 12; result.month++) {
		if (result.month == 2) {
			if ((result.year % 4 == 0) && (result.year % 100 != 0 || result.year % 400 == 0))
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

// TODO Task 4
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
	TDateTimeTZ result;
	return result;
}

// TODO Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ) {
	return 0;
}

// TODO Task 6
void printDateTimeTZ(TDateTimeTZ datetimetz) {
}
