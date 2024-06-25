#include <stdexcept>

#include "../global.hpp"
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