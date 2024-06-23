#include "global.hpp"

Quartos  *quartosHandler  = new Quartos();
Estadias *estadiasHandler = new Estadias();
Pessoas  *pessoasHandler  = new Pessoas();

time_t getCurrentTimestamp() { return difftime(std::time(0), timezone); }