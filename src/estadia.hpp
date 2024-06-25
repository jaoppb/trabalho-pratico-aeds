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

	Estadia(
		unsigned int codigo,
		time_t dataEntrada,
		time_t dataSaida,
		unsigned int codigoCliente,
		unsigned int numeroDoQuarto
	);

	const int	   getCodigo() 		 const;
	const int 	   getDiarias() 	 const;
	const Cliente *getCliente()		 const;
	const Quarto  *getQuarto() 		 const;
	const time_t   getCheckInDate()  const;
	const time_t   getCheckOutDate() const;
};

#endif