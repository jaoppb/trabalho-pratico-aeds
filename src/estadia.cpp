#include <cmath>
#include <stdexcept>

#include "estadia.hpp"
#include "utils.hpp"

Estadia::Estadia(
	unsigned int codigo,
	std::string dataEntrada,
	std::string dataSaida,
	unsigned int codigoCliente,
	unsigned int numeroDoQuarto
): codigo(codigo), codigoCliente(codigoCliente), numeroDoQuarto(numeroDoQuarto) {
	this -> dataEntrada = parseDate(dataEntrada + " - 14:00:00");
	this -> dataSaida   = parseDate(dataSaida   + " - 12:00:00");

	if(this -> dataSaida <= this -> dataEntrada) throw std::runtime_error("A data de saída precisa ser no mínimo um dia após a data de entrada");

	this -> diarias = ceil(difftime(this -> dataSaida, this -> dataEntrada) / (24.0f * 60.0f * 60.0f));
}

const int Estadia::getDiarias() const { return this -> diarias; }

Estadias::Estadias(): estadias({}) {
	this -> nextCode = 0;
}

Estadias::~Estadias() {
	for(Estadia *estadia: this -> estadias) {
		delete estadia;
	}
}

const Estadia* Estadias::agendarEstadia(std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto) {
	Estadia *estadia = new Estadia(this -> nextCode, dataEntrada, dataSaida, codigoCliente, numeroDoQuarto);
	this -> nextCode++;

	return estadia;
}