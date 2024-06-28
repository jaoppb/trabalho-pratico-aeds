#include <cmath>
#include <stdexcept>
#include <iostream>

#include "../src/estadia.hpp"
#include "../src/utils.hpp"
#include "../src/global.hpp"

//Class Estadia

/*
 * Construtor da classe Estadia
 *
 * A data de entrada é considerada as 14:00:00; e
 * A data de saída é considerada às 12:00:00
 * 
 * Um erro é lançado caso a data de saída seja no mesmo dia ou anterior
 * à data de entrada.
 * 
 * @param unsigned int codigo
 * @param std::string  dataEntrada
 * @param std::string  dataSaida
 * @param unsigned int codigoCliente
 * @param unsigned int numeroDoQuarto
 */
Estadia::Estadia(
	unsigned int codigo,
	std::string dataEntrada,
	std::string dataSaida,
	unsigned int codigoCliente,
	unsigned int numeroDoQuarto
): codigo(codigo) {
	if(dataEntrada.find(" - 14:00:00") == std::string::npos) dataEntrada += " - 14:00:00";
	if(dataSaida  .find(" - 12:00:00") == std::string::npos) dataSaida   += " - 12:00:00"; 	
	this -> dataEntrada = parseDate(dataEntrada);
	this -> dataSaida   = parseDate(dataSaida);

	if(this -> dataSaida <= this -> dataEntrada) throw std::runtime_error("A data de saida precisa ser no minimo um dia apos a data de entrada");

	this -> diarias = ceil(difftime(this -> dataSaida, this -> dataEntrada) / (24.0f * 60.0f * 60.0f));

	this -> cliente = pessoasHandler -> getCliente(codigoCliente);
	this -> quarto  = quartosHandler -> getQuarto(numeroDoQuarto);
}

/*
 * Mesmo construtor porém recebe a data de entrada e de saída diretamente
 * como timestamp
 * 
 * @param unsigned int codigo
 * @param time_t	   dataEntrada
 * @param time_t	   dataSaida
 * @param unsigned int codigoCliente
 * @param unsigned int numeroDoQuarto
 */
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

// getters da classe
const int	   Estadia::getCodigo()		  const { return this -> codigo; }
const int	   Estadia::getDiarias() 	  const { return this -> diarias; }
const Cliente* Estadia::getCliente()	  const { return this -> cliente; }
const Quarto*  Estadia::getQuarto()  	  const { return this -> quarto; }
const time_t   Estadia::getCheckInDate()  const { return this -> dataEntrada; }
const time_t   Estadia::getCheckOutDate() const { return this -> dataSaida; }