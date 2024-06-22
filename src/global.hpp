#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "quarto.hpp"
#include "estadia.hpp"
#include "cliente.hpp"

extern Quartos  *quartosHandler;
extern Estadias *estadiasHandler;
extern Clientes *clientesHandler;

void initiliazeGlobals();

void terminateGlobals();

#endif