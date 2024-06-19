#include "quarto.hpp"

Quarto::Quarto(int numero, int valorDiaria):
	numero(numero),
	quantidadeDeHospedes(0),
	diaria(valorDiaria),
	status(false) {}

int Quarto::getNumero() const { return this -> numero; }
int Quarto::getQuantidadeDeHospedes() const { return this -> quantidadeDeHospedes; }
float Quarto::getDiaria() const { return this -> diaria; }
bool Quarto::getStatus() const { return this -> status; }

void Quarto::setDiaria(float diaria) { this -> diaria = diaria; }
void Quarto::setQuantidadeDeHospedes(int hospedes) { this -> quantidadeDeHospedes = hospedes; }
void Quarto::setStatus(bool status) { this -> status = status; }