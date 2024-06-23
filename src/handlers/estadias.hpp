#ifndef HANDLERS_ESTADIAS_HPP
#define HANDLERS_ESTADIAS_HPP

#include <vector>

#include "../estadia.hpp"

class Estadias {
private:
	std::vector<Estadia*> estadias;
	unsigned int nextCode;

	const bool _checkEstadia(Estadia *novaEstadia);
	float _darBaixa(Estadia *estadia);
	Estadia *_getEstadia(unsigned int code);
public:
	Estadias();
	~Estadias();

	const Estadia* agendarEstadia(std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto);
	float darBaixa(unsigned int code);
};

#endif