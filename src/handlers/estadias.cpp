#include <stdexcept>

#include "estadias.hpp"

Estadias::Estadias(): estadias({}) {
	this -> nextCode = 0;
}

Estadias::~Estadias() {
	for(Estadia *estadia: this -> estadias) {
		delete estadia;
	}
}

const bool Estadias::_checkEstadia(Estadia *novaEstadia) {
	const uint roomNumber = novaEstadia -> getQuarto() -> getNumero();
	for(const Estadia *estadia: this -> estadias) {
		if(estadia -> getQuarto() -> getNumero() != roomNumber) continue;

		if(!((estadia -> getCheckOutDate() < novaEstadia -> getCheckInDate()) ||
			  novaEstadia -> getCheckOutDate() < estadia -> getCheckInDate())) return false;
	}

	return true;
}

const Estadia* Estadias::agendarEstadia(
	std::string dataEntrada,
	std::string dataSaida,
	int codigoCliente,
	int numeroDoQuarto) {
	Estadia *estadia = new Estadia(this -> nextCode, dataEntrada, dataSaida, codigoCliente, numeroDoQuarto);
	if(!this -> _checkEstadia(estadia)) {
		delete estadia;
		throw std::runtime_error("Alguma estádia já agendada conflita com a nova estádia.");
	}
	
	this -> estadias.push_back(estadia);
	this -> nextCode++;
	return estadia;
}