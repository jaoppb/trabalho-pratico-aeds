#ifndef HANDLERS_QUARTOS_HPP
#define HANDLERS_QUARTOS_HPP

#include <vector>

#include "../quarto.hpp"

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