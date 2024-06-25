#include <stdexcept>

#include "quartos.hpp"

Quartos::Quartos(bool load): quartos({}), fileHandler("./data/quartos.bin") {
	if(load) this->load();
}

void Quartos::load() {
	this->fileHandler.open();
	while(!this->fileHandler.isEOF()) {
		unsigned int number, guests;
		float valorDiaria;
		bool status;

		this->fileHandler.read((void*)&number, 		sizeof(number));
		this->fileHandler.read((void*)&valorDiaria, sizeof(valorDiaria));
		this->fileHandler.read((void*)&guests, 		sizeof(guests));
		this->fileHandler.read((void*)&status, 		sizeof(status));
		
		this->_loadQuarto(number, valorDiaria, guests, status);
	}
	this->fileHandler.close();
}

Quartos::~Quartos() {
	this->fileHandler.clear();
	this->fileHandler.open();
	for(Quarto *quarto: this->quartos) {
		unsigned int number = quarto->getNumero(),
					 guests = quarto->getQuantidadeDeHospedes();
		float valorDiaria	= quarto->getDiaria();
		bool status			= quarto->getStatus();

		this->fileHandler.write((void*)&number, 	 sizeof(number));
		this->fileHandler.write((void*)&valorDiaria, sizeof(valorDiaria));
		this->fileHandler.write((void*)&guests, 	 sizeof(guests));
		this->fileHandler.write((void*)&status, 	 sizeof(status));

		delete quarto;
	}
	this->fileHandler.close();
}

Quarto *Quartos::_loadQuarto(unsigned int numero, float valorDiaria, unsigned int guests, bool status) {
	Quarto *quarto = new Quarto(numero, valorDiaria, guests, status);
	this->quartos.push_back(quarto);
	return quarto;
}

const Quarto* Quartos::criarQuarto(unsigned int numero, float valorDiaria) {
	int length = this -> quartos.size();
	for(int i = 0; i < length; i++) {
		if(this -> quartos[i] -> getNumero() == numero) throw std::runtime_error("Um quarto com esse número já existe");
	}

	Quarto *quarto = new Quarto(numero, valorDiaria);
	this -> quartos.push_back(quarto);
	return quarto;
}

const Quarto* Quartos::getQuarto(unsigned int numero) const {
	if(numero < 0) throw std::runtime_error("O número do quarto precisa ser zero ou positivo");

	for(int i = this -> quartos.size() - 1; i >= 0; i--) {
		if(this -> quartos[i] -> getNumero() == numero) return this -> quartos[i];
	}

	throw std::runtime_error("Quarto não encontrado");
}

void Quartos::setStatus(unsigned int numero, bool status) {
	if(numero < 0) throw std::runtime_error("O número do quarto não pode ser negativo");

	for(int i = this -> quartos.size() - 1; i >= 0; i--) {
		Quarto *quarto = this -> quartos[i];
		if(quarto -> getNumero() == numero) {
			quarto -> setStatus(status);
			return;
		}
	}

	throw std::runtime_error("Número do quarto inválido");
}

void Quartos::setStatus(const Quarto *quarto, bool status) {
	this -> setStatus(quarto -> getNumero(), status);
}

const bool Quartos::getStatus(unsigned int numero) const {
	return this -> getQuarto(numero) -> getStatus();

	throw std::runtime_error("Número do quarto inválido");
}