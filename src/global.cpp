#include "global.hpp"

/*
 * Handlers globais para gerenciamento dos quartos, pessoas e estadias
 */

Quartos  *quartosHandler  = new Quartos(true);
Pessoas  *pessoasHandler  = new Pessoas(true);
Estadias *estadiasHandler = new Estadias(true);