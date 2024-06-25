#ifndef HANDLERS_QUARTOS_HPP
#define HANDLERS_QUARTOS_HPP

#include <vector>

#include "../quarto.hpp"
#include "./files.hpp"

class Quartos {
private:
	std::vector<Quarto*> quartos;

	FileHandler fileHandler;

	Quarto *_loadQuarto(unsigned int numero, float valorDiaria, unsigned int guests, bool status);
public:
	Quartos(bool load);
	~Quartos();

	void load();

	const size_t getTotal() const;

	const Quarto* criarQuarto(unsigned int numero, float valorDiaria, unsigned int guests);
	const Quarto* getQuarto  (unsigned int numero) const;
	void          setStatus  (unsigned int numero, bool status);
	void		  setStatus  (const Quarto *quarto, bool status);
	const bool	  getStatus  (unsigned int numero) const;
	
	const std::vector<Quarto*> getRoomsByCapacity(unsigned int capacity);
};

#endif