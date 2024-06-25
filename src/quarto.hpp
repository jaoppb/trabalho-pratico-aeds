#ifndef QUARTO_HPP
#define QUARTO_HPP

#include <vector>

class Quarto {
private:
	unsigned int numero;
	unsigned int quantidadeDeHospedes;
	float diaria;
	bool status;

public:
	Quarto(unsigned int numero, float diaria);
	Quarto(
		unsigned int numero,
		float valorDiaria,
		unsigned int guests,
		bool status
	);

	const int   getNumero() const;
	const int   getQuantidadeDeHospedes() const;
	const float getDiaria() const;
	const bool  getStatus() const;

	void setQuantidadeDeHospedes(unsigned int hospedes);
	void setDiaria(float diaria);
	void setStatus(bool status);
};

#endif