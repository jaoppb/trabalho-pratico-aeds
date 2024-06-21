#ifndef ESTADIA_HPP
#define ESTADIA_HPP

#include <chrono>
#include <string>
#include <vector>

class Estadia {
private:
	unsigned int codigo;
	time_t dataEntrada;
	time_t dataSaida;
	int diarias;
	int codigoCliente;
	int numeroDoQuarto;
public:
	Estadia(unsigned int codigo, std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto);

	const int getDiarias() const;
};

class Estadias {
private:
	std::vector<Estadia*> estadias;
	unsigned int nextCode;
public:
	Estadias();
	~Estadias();

	const Estadia* agendarEstadia(std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto);
};

#endif