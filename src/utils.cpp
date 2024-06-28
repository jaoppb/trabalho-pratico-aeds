#include <stdexcept>
#include <bits/stdc++.h>

#include "utils.hpp"

/*
 * @param int year
 *
 * @returns `true`  caso `year` seja bissexto
 * @returns `false` caso `year` não seja bissexto
 * 
 * @return bool
 */
bool _isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/*
 * Retorna a quantidade de dias do mês `month` no ano `year`
 *
 * @param int month (zero-index)
 * @param int year
 * 
 * @return int
 */
int _getMonthDays(int month, int year) {
	int monthDays[] = {
		31, _isLeapYear(year) ? 29 : 28,
		31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	return monthDays[month];
} 

/*
 * Retorna o timestamp relativo à string `date`
 *
 * @param std::string date
 * 
 * @return time_t
 */
time_t parseDate(std::string date) {
	std::tm time = {0};
	if ((strptime(date.c_str(), "%d/%m/%Y - %H:%M:%S", &time) == NULL &&
		 strptime(date.c_str(), "%d/%m/%Y"			 , &time) == NULL) ||
		time.tm_mday > _getMonthDays(time.tm_mon, time.tm_year + 1900))
		throw std::runtime_error("Data inválida");
	return difftime(std::mktime(&time), timezone);
}

/*
 * Retorna o `timestamp` do momento em que a função é chamada
 *
 * @return time_t
 */
time_t getCurrentTimestamp() { return difftime(std::time(0), timezone); }

/*
 * Transforma todos os caracteres maisuculos de str em minusculos
 *
 * @param std::string &str
 */
void toLower(std::string &str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

/*
 * Transforma o `timestamp` em uma string formatada como "dd/mm/aa"
 *
 * @param time_t timestamp
 * 
 * @return std::string
 */
std::string formatTimestamp(time_t timestamp) {
    char result[11];
    strftime(result, 11, "%d/%m/%y", localtime(&timestamp));
    return std::string(result);
}