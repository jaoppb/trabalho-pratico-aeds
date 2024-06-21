#include <stdexcept>
#include <iostream>

#include "utils.hpp"

bool _isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int _getMonthDays(int month, int year) {
	int monthDays[] = {
		31, _isLeapYear(year) ? 29 : 28,
		31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	return monthDays[month];
} 

time_t parseDate(std::string date) {
	std::tm time = {0};
	if ((strptime(date.c_str(), "%d/%m/%Y - %H:%M:%S", &time) == NULL &&
		 strptime(date.c_str(), "%d/%m/%Y"			 , &time) == NULL) ||
		time.tm_mday > _getMonthDays(time.tm_mon, time.tm_year + 1900))
		throw std::runtime_error("Data inválida");

	return std::mktime(&time);
}