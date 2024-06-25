#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <string>

time_t parseDate(std::string date);

time_t getCurrentTimestamp();

void toLower(std::string &str);

void handleTimestamp(int *result, time_t timestamp);

#endif