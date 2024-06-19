#include <stdexcept>

#include "quarto.hpp"

Quarto::Quarto(int numero, float valorDiaria):
	quantidadeDeHospedes(0), status(false) {
	if(numero < 0) throw std::runtime_error("O número do quarto precisa ser positivo");
	if(valorDiaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
	this -> numero = numero;
	this -> diaria = valorDiaria;
}

int Quarto::getNumero() const { return this -> numero; }
int Quarto::getQuantidadeDeHospedes() const { return this -> quantidadeDeHospedes; }
float Quarto::getDiaria() const { return this -> diaria; }
bool Quarto::getStatus() const { return this -> status; }

void Quarto::setDiaria(float diaria) { this -> diaria = diaria; }
void Quarto::setQuantidadeDeHospedes(int hospedes) { this -> quantidadeDeHospedes = hospedes; }
void Quarto::setStatus(bool status) { this -> status = status; }