#include "global.hpp"

Quartos  *quartosHandler  = new Quartos(true);
Pessoas  *pessoasHandler  = new Pessoas(true);
Estadias *estadiasHandler = new Estadias(true);

time_t getCurrentTimestamp() { return difftime(std::time(0), timezone); }