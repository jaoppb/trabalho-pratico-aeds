#include <stdexcept>

#include "quartos.hpp"

Quartos::Quartos(): quartos({}) {}

Quartos::~Quartos() {
	for(int i = this -> quartos.size() - 1; i >= 0; i--) {
		delete this -> quartos[i];
	}
}

const Quarto* Quartos::criarQuarto(int numero, float valorDiaria) {
	int length = this -> quartos.size();
	for(int i = 0; i < length; i++) {
		if(this -> quartos[i] -> getNumero() == numero) throw std::runtime_error("Um quarto com esse número já existe");
	}

	Quarto *quarto = new Quarto(numero, valorDiaria);
	this -> quartos.push_back(quarto);
	return quarto;
}

const Quarto* Quartos::getQuarto(int numero) const {
	if(numero < 0) throw std::runtime_error("O número do quarto precisa ser zero ou positivo");

	for(int i = this -> quartos.size() - 1; i >= 0; i--) {
		if(this -> quartos[i] -> getNumero() == numero) return this -> quartos[i];
	}

	throw std::runtime_error("Quarto não encontrado");
}

void Quartos::setStatus(int numero, bool status) {
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

const bool Quartos::getStatus(int numero) const {
	return this -> getQuarto(numero) -> getStatus();

	throw std::runtime_error("Número do quarto inválido");
}