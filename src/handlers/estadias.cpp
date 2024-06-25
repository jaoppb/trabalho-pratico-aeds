#include <stdexcept>
#include <iostream>

#include "../global.hpp"
#include "estadias.hpp"

Estadias::Estadias(bool load): estadias({}), fileHandler("./data/estadias.bin") {
	if(load) this->load();
}

void Estadias::load() {
	this->fileHandler.open();
	if(this->fileHandler.isEOF()) this->nextCode = 0;
	else this->fileHandler.read((void*)&this->nextCode, sizeof(this->nextCode));

	while(!this->fileHandler.isEOF()) {
		unsigned int code, clientCode, roomNumber;
		time_t checkInDate, checkOutDate;

		this->fileHandler.read((void*)&code		   , sizeof(code));
		this->fileHandler.read((void*)&checkInDate , sizeof(checkInDate));
		this->fileHandler.read((void*)&checkOutDate, sizeof(checkOutDate));
		this->fileHandler.read((void*)&clientCode  , sizeof(clientCode));
		this->fileHandler.read((void*)&roomNumber  , sizeof(roomNumber));

		try {
			this->_loadEstadia(code, checkInDate, checkOutDate, clientCode, roomNumber);
		} catch(std::runtime_error &err) {
			std::cout << err.what() << std::endl;
		}
	}
	this->fileHandler.close();
}

Estadias::~Estadias() {
	this->fileHandler.clear();
	this->fileHandler.open();
	this->fileHandler.write((void*)&this->nextCode, sizeof(this->nextCode));
	for(Estadia *estadia: this -> estadias) {
		unsigned int code 		= estadia->getCodigo(),
					 clientCode = estadia->getCliente()->getCodigo(),
					 roomNumber = estadia->getQuarto()->getNumero();
		time_t checkInDate  = estadia->getCheckInDate(),
			   checkOutDate = estadia->getCheckOutDate();

		this->fileHandler.write((void*)&code		, sizeof(code));
		this->fileHandler.write((void*)&checkInDate , sizeof(checkInDate));
		this->fileHandler.write((void*)&checkOutDate, sizeof(checkOutDate));
		this->fileHandler.write((void*)&clientCode  , sizeof(clientCode));
		this->fileHandler.write((void*)&roomNumber  , sizeof(roomNumber));
		delete estadia;
	}
	this->fileHandler.close();
}

const bool Estadias::_checkEstadia(Estadia *novaEstadia) {
	const int roomNumber = novaEstadia -> getQuarto() -> getNumero();
	for(const Estadia *estadia: this -> estadias) {
		if(estadia -> getQuarto() -> getNumero() != roomNumber) continue;

		if(!((estadia -> getCheckOutDate() < novaEstadia -> getCheckInDate()) ||
			  novaEstadia -> getCheckOutDate() < estadia -> getCheckInDate())) return false;
	}

	return true;
}

float Estadias::_darBaixa(Estadia *estadia) {
	time_t current_tm = getCurrentTimestamp();
	if (current_tm >= estadia -> getCheckInDate() && 
		current_tm <= estadia -> getCheckOutDate() + 10 * 60 * 60)
		quartosHandler -> setStatus(estadia -> getQuarto(), false);
	pessoasHandler -> addPontos(estadia -> getCliente(), estadia -> getDiarias());
	return estadia -> getQuarto() -> getDiaria() * estadia -> getDiarias();
}

Estadia *Estadias::_getEstadia(unsigned int code) {
	for(Estadia *estadia: this -> estadias) {
		if(estadia -> getCodigo() == code) return estadia;
	}
	return nullptr;
}

Estadia *Estadias::_loadEstadia(
	unsigned int code,
	time_t checkInDate,
	time_t checkOutDate,
	unsigned int clientCode,
	unsigned int roomNumber
) {
	Estadia *estadia = new Estadia(code, checkInDate, checkOutDate, clientCode, roomNumber);
	this -> estadias.push_back(estadia);
	return estadia;
}

const Estadia* Estadias::agendarEstadia(
	std::string dataEntrada,
	std::string dataSaida,
	int codigoCliente,
	int numeroDoQuarto) {
	time_t current_tm = getCurrentTimestamp();
	Estadia *estadia = new Estadia(this -> nextCode, dataEntrada, dataSaida, codigoCliente, numeroDoQuarto);
	if(current_tm >= estadia -> getCheckInDate() + 10 * 60 * 60) {
		delete estadia;
		throw std::runtime_error("A data de entrada precisa ser pelo menos o dia atual");
	}

	if(!this -> _checkEstadia(estadia)) {
		delete estadia;
		throw std::runtime_error("Alguma estádia já agendada conflita com a nova estádia.");
	}
	
	if (estadia -> getCheckInDate()  <= current_tm &&
		estadia -> getCheckOutDate() >= current_tm)
		quartosHandler -> setStatus(numeroDoQuarto, true);
	this -> estadias.push_back(estadia);
	this -> nextCode++;
	return estadia;
}

float Estadias::darBaixa(unsigned int code) {
	Estadia *estadia = this -> _getEstadia(code);
	if(estadia == nullptr) throw std::runtime_error("Estadia não encontrada");
	return this -> _darBaixa(estadia);
}