#include <stdexcept>

#include "quarto.hpp"

//Class Quarto

Quarto::Quarto(int numero, float valorDiaria):
	quantidadeDeHospedes(0), status(false) {
	if(numero 	   <  0) throw std::runtime_error("O número do quarto precisa ser zero ou positivo");
	if(valorDiaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
	this -> numero = numero;
	this -> diaria = valorDiaria;
}

int   Quarto::getNumero() 				const { return this -> numero; }
int   Quarto::getQuantidadeDeHospedes() const { return this -> quantidadeDeHospedes; }
float Quarto::getDiaria() 				const { return this -> diaria; }
bool  Quarto::getStatus() 				const { return this -> status; }

void Quarto::setDiaria(float diaria) {
	if(diaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
	this -> diaria = diaria;
}

void Quarto::setQuantidadeDeHospedes(int hospedes) {
	if(quantidadeDeHospedes < 0) throw std::runtime_error("Não é possível ter quantidade de hospédes negativo.");
	this -> quantidadeDeHospedes = hospedes;
}
void Quarto::setStatus(bool status) { this -> status = status; }

//Class Quartos

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