#ifndef QUARTO_HPP
#define QUARTO_HPP

#include <vector>

class Quarto {
private:
	int numero;
	int quantidadeDeHospedes;
	float diaria;
	bool status;

public:
	Quarto(int numero, float diaria);

	const int   getNumero() const;
	const int   getQuantidadeDeHospedes() const;
	const float getDiaria() const;
	const bool  getStatus() const;

	void setQuantidadeDeHospedes(int hospedes);
	void setDiaria(float diaria);
	void setStatus(bool status);
};

#endif