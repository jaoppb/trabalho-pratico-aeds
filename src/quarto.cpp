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

const int   Quarto::getNumero() 				const { return this -> numero; }
const int   Quarto::getQuantidadeDeHospedes() const { return this -> quantidadeDeHospedes; }
const float Quarto::getDiaria() 				const { return this -> diaria; }
const bool  Quarto::getStatus() 				const { return this -> status; }

void Quarto::setDiaria(float diaria) {
	if(diaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
	this -> diaria = diaria;
}

void Quarto::setQuantidadeDeHospedes(int hospedes) {
	if(quantidadeDeHospedes < 0) throw std::runtime_error("Não é possível ter quantidade de hospédes negativo.");
	this -> quantidadeDeHospedes = hospedes;
}
void Quarto::setStatus(bool status) { this -> status = status; }