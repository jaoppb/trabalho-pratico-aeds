#include <stdexcept>
#include <bits/stdc++.h>

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
	return difftime(std::mktime(&time), timezone);
}

time_t getCurrentTimestamp() { return difftime(std::time(0), timezone); }

void toLower(std::string &str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

#define MINUTES_SECONDS 60
#define HOURS_SECONDS 60 * MINUTES_SECONDS
#define DAY_SECONDS 24 * HOURS_SECONDS

/*
    Descrição: obtem quantos segundos aquele ano possui
    Entrada: ano (inteiro)
    Saída: segundos (inteiro)
*/
int _secondsOfYear(int year) {
    int seconds = DAY_SECONDS;
    if(_isLeapYear(year)) seconds *= 366;
    else seconds *= 365;
    return seconds;
}

/*
    Descrição: obtem quantos segundos tem aquele mês naquele determinado ano
    Entrada: mês (inteiro), ano (inteiro)
    Saída: segundos (inteiro)
*/
int _secondsOfMonth(int month, int year) {
    return _getMonthDays(month, year) * DAY_SECONDS;
}

/*
    Descrição: converte um timestamp em ano, mêses, horas, minutos e segundos
    Entrada: resultado (*int[6]), timestamp (inteiro)
    Resultado: armazena o resultado em um vetor de inteiros passado por referência
*/
void handleTimestamp(int *result, time_t timestamp) {
    // 0 - result
    // 1 - seconds
    // 2 - remaining
    int year[3] = {1970, 0, 0},
        month[3] = {0, 0, 0},
        day[3] = {0, 0, 0},
        hours[3] = {0, 0, 0},
        minutes[3] = {0, 0, 0},
        seconds = 0;

    while(year[1] <= timestamp - _secondsOfYear(year[0])) {
        year[1] += _secondsOfYear(year[0]);
        year[0]++;
    }
    result[0] = year[0];
    year[2] = year[1] == 0 ? timestamp : timestamp % year[1];    

    while(month[1] <= year[2] - _secondsOfMonth(month[0], year[0])) {
        month[1] += _secondsOfMonth(month[0], year[0]);
        month[0]++;
    }
    result[1] = month[0];
    month[2] = month[1] == 0 ? year[2] : year[2] % month[1];

    while(day[1] <= month[2] - DAY_SECONDS) {
        day[1] += DAY_SECONDS;
        day[0]++;
    }
    result[2] = day[0];
    day[2] = day[1] == 0 ? month[2] : month[2] % day[1];

    hours[2] = day[2] % HOURS_SECONDS;
    hours[1] = day[2] - hours[2];
    hours[0] = hours[1] / HOURS_SECONDS;
    result[3] = hours[0];

    minutes[2] = hours[2] % MINUTES_SECONDS;
    minutes[1] = hours[2] - minutes[2];
    minutes[0] = minutes[1] / MINUTES_SECONDS;
    result[4] = minutes[0];

    seconds = minutes[2];
    result[5] = seconds;
}