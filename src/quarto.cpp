#include <stdexcept>

#include "quarto.hpp"

//Class Quarto

Quarto::Quarto(unsigned int numero, float valorDiaria):
	numero(numero), diaria(valorDiaria), quantidadeDeHospedes(0), status(false) {
	if(valorDiaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
}

Quarto::Quarto(
	unsigned int numero,
	float valorDiaria,
	unsigned int guests,
	bool status):
	numero(numero),
	diaria(valorDiaria),
	quantidadeDeHospedes(guests),
	status(status) {
	if(valorDiaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
}

const int   Quarto::getNumero() 				const { return this -> numero; }
const int   Quarto::getQuantidadeDeHospedes() const { return this -> quantidadeDeHospedes; }
const float Quarto::getDiaria() 				const { return this -> diaria; }
const bool  Quarto::getStatus() 				const { return this -> status; }

void Quarto::setDiaria(float diaria) {
	if(diaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
	this -> diaria = diaria;
}

void Quarto::setQuantidadeDeHospedes(unsigned int hospedes) {
	if(quantidadeDeHospedes < 0) throw std::runtime_error("Não é possível ter quantidade de hospédes negativo.");
	this -> quantidadeDeHospedes = hospedes;
}
void Quarto::setStatus(bool status) { this -> status = status; }