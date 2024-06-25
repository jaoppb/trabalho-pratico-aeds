#ifndef HANDLERS_ESTADIAS_HPP
#define HANDLERS_ESTADIAS_HPP

#include <vector>

#include "../estadia.hpp"
#include "files.hpp"

class Estadias {
private:
	std::vector<Estadia*> estadias;
	unsigned int nextCode;
	FileHandler fileHandler;

	const bool _checkEstadia(Estadia *novaEstadia);
	float _darBaixa(Estadia *estadia);
	Estadia *_getEstadia(unsigned int code);
	Estadia *_loadEstadia(
		unsigned int code,
		time_t checkInDate,
		time_t checkOutDate,
		unsigned int clientCode,
		unsigned int roomNumber
	);
public:
	Estadias(bool load);
	~Estadias();

	void load();

	const size_t getTotal() const;

	const Estadia* agendarEstadia(std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto);
	float darBaixa(unsigned int code);
	const Estadia* getEstadia(unsigned int code);
	const std::vector<Estadia*> getEstadia(std::string date);

	const std::vector<Estadia*> getEstadias(unsigned int clientCode);
	const std::vector<Estadia*> getEstadiasByRoom(unsigned int roomNumber);
};

#endif