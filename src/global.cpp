#include "global.hpp"

Quartos  *quartosHandler  = nullptr;
Estadias *estadiasHandler = nullptr;
Clientes *clientesHandler = nullptr;

void initiliazeGlobals() {
	quartosHandler = new Quartos();
	estadiasHandler = new Estadias();
	clientesHandler = new Clientes();
}

void terminateGlobals() {
	delete quartosHandler;
	delete estadiasHandler;
	delete clientesHandler;
}