#ifndef QUARTO_HPP
#define QUARTO_HPP

class Quarto {
private:
	int numero;
	int quantidadeDeHospedes;
	float diaria;
	bool status;

public:
	Quarto(int numero, int diaria);

	int getNumero() const;
	int getQuantidadeDeHospedes() const;
	float getDiaria() const;
	bool getStatus() const;

	void setQuantidadeDeHospedes(int hospedes);
	void setDiaria(float diaria);
	void setStatus(bool status);
};

#endif