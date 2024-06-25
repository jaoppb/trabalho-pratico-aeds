#include <cmath>
#include <stdexcept>
#include <iostream>

#include "estadia.hpp"
#include "utils.hpp"
#include "global.hpp"

//Class Estadia

Estadia::Estadia(
	unsigned int codigo,
	std::string dataEntrada,
	std::string dataSaida,
	unsigned int codigoCliente,
	unsigned int numeroDoQuarto
): codigo(codigo) {
	this -> dataEntrada = parseDate(dataEntrada + " - 14:00:00");
	this -> dataSaida   = parseDate(dataSaida   + " - 12:00:00");

	if(this -> dataSaida <= this -> dataEntrada) throw std::runtime_error("A data de saida precisa ser no minimo um dia apos a data de entrada");

	this -> diarias = ceil(difftime(this -> dataSaida, this -> dataEntrada) / (24.0f * 60.0f * 60.0f));

	this -> cliente = pessoasHandler -> getCliente(codigoCliente);
	this -> quarto  = quartosHandler -> getQuarto(numeroDoQuarto);
}

Estadia::Estadia(
	unsigned int codigo,
	time_t dataEntrada,
	time_t dataSaida,
	unsigned int codigoCliente,
	unsigned int numeroDoQuarto
): codigo(codigo), dataEntrada(dataEntrada), dataSaida(dataSaida) {
	if(this -> dataSaida <= this -> dataEntrada) throw std::runtime_error("A data de saida precisa ser no minimo um dia apos a data de entrada");

	this -> diarias = ceil(difftime(this -> dataSaida, this -> dataEntrada) / (24.0f * 60.0f * 60.0f));

	this -> cliente = pessoasHandler -> getCliente(codigoCliente);
	this -> quarto  = quartosHandler -> getQuarto(numeroDoQuarto);
}

const int	   Estadia::getCodigo()		  const { return this -> codigo; }
const int	   Estadia::getDiarias() 	  const { return this -> diarias; }
const Cliente* Estadia::getCliente()	  const { return this -> cliente; }
const Quarto*  Estadia::getQuarto()  	  const { return this -> quarto; }
const time_t   Estadia::getCheckInDate()  const { return this -> dataEntrada; }
const time_t   Estadia::getCheckOutDate() const { return this -> dataSaida; }