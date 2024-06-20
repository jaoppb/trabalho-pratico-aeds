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

	int   getNumero() const;
	int   getQuantidadeDeHospedes() const;
	float getDiaria() const;
	bool  getStatus() const;

	void setQuantidadeDeHospedes(int hospedes);
	void setDiaria(float diaria);
	void setStatus(bool status);
};

class Quartos {
private:
	std::vector<Quarto*> quartos;
public:
	Quartos();
	~Quartos();
	const Quarto* criarQuarto(int numero, float valorDiaria);
	const Quarto* getQuarto  (int numero) const;
	void          setStatus  (int numero, bool status);
	const bool	  getStatus  (int numero) const;
};

#endif