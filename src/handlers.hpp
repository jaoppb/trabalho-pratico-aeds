#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include <vector>

#include "pessoa.hpp"
#include "cliente.hpp"
#include "funcionario.hpp"

class Pessoas {
private:
    std::vector<Pessoa*> pessoas;
    unsigned int nextCode;

	Pessoa *_getPessoa(unsigned int code) const;
public:
    Pessoas();
    ~Pessoas();

    const Cliente     *cadastrarCliente   (unsigned int telefone, std::string nome, std::string endereco);
    const Funcionario *cadastrarFuncionaro(unsigned int telefone, std::string nome, std::string cargo, float salario);

    const Pessoa      *getPessoa	 (unsigned int code) const;
    const Cliente     *getCliente	 (unsigned int code) const;
    const Funcionario *getFuncionario(unsigned int code) const;
};

#include "estadia.hpp"

class Estadias {
private:
	std::vector<Estadia*> estadias;
	unsigned int nextCode;

	const bool checkEstadia(Estadia *novaEstadia);
public:
	Estadias();
	~Estadias();

	const Estadia* agendarEstadia(std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto);
};

#include "quarto.hpp"

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