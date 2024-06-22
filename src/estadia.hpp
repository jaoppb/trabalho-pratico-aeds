#ifndef ESTADIA_HPP
#define ESTADIA_HPP

#include <chrono>
#include <string>
#include <vector>

#include "cliente.hpp"
#include "quarto.hpp"

class Estadia {
private:
	unsigned int codigo;
	time_t dataEntrada;
	time_t dataSaida;
	unsigned int diarias;
	const Cliente* cliente;
	const Quarto* quarto;
public:
	Estadia(
		unsigned int codigo,
		std::string dataEntrada,
		std::string dataSaida,
		unsigned int codigoCliente,
		unsigned int numeroDoQuarto
	);

	const int 	  getDiarias() 		const;
	const Quarto *getQuarto() 		const;
	const time_t  getCheckInDate()  const;
	const time_t  getCheckOutDate() const;
};

class Estadias {
private:
	std::vector<Estadia*> estadias;
	unsigned int nextCode;

	const bool checkEstadia(Estadia *novaEstadia);
public:
	Estadias();
	~Estadias();

	const Estadia* agendarEstadia(std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto);
};

#endif