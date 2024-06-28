#include <stdexcept>

#include "quarto.hpp"

//Class Quarto

/*
 * Construtor da classe Quarto
 *
 * Lança um erro caso `valorDiaria` seja 0 ou negativo.
 * 
 * Lança um erro caso `guests` seja 0
 *
 * Inicializa `status` como `false`
 * 
 * @param unsigned int numero
 * @param float		   valorDiaria
 * @param unsigned int guests(capacity)
 */
Quarto::Quarto(unsigned int numero, float valorDiaria, unsigned int guests):
	numero(numero), diaria(valorDiaria), quantidadeDeHospedes(guests), status(false) {
	if(valorDiaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
	if(guests == 0) throw std::runtime_error("A capacidade do quarto precisa ser maior que zero.");
}

/*
 * Construtor da classe Quarto
 *
 * Lança um erro caso `valorDiaria` seja 0 ou negativo.
 * 
 * @param unsigned int numero
 * @param float		   valorDiaria
 * @param unsigned int guests(capacity)
 * @param bool		   status
 */
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

// getters da classe Quarto
const int   Quarto::getNumero() 				const { return this -> numero; }
const int   Quarto::getQuantidadeDeHospedes() const { return this -> quantidadeDeHospedes; }
const float Quarto::getDiaria() 				const { return this -> diaria; }
const bool  Quarto::getStatus() 				const { return this -> status; }

// setters da classe Quarto
void Quarto::setDiaria(float diaria) {
	if(diaria <= 0) throw std::runtime_error("O preço da Diária precisa ser positivo");
	this -> diaria = diaria;
}
void Quarto::setQuantidadeDeHospedes(unsigned int hospedes) {
	if(quantidadeDeHospedes < 0) throw std::runtime_error("Não é possível ter quantidade de hospédes negativo.");
	this -> quantidadeDeHospedes = hospedes;
}
void Quarto::setStatus(bool status) { this -> status = status; }