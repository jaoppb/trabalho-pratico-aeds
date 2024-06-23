#ifndef HANDLERS_PESSOAS_HPP
#define HANDLERS_PESSOAS_HPP

#include <vector>

#include "../pessoa.hpp"
#include "../cliente.hpp"
#include "../funcionario.hpp"

class Pessoas {
private:
    std::vector<Pessoa*> pessoas;
    unsigned int nextCode;

	Pessoa      *_getPessoa     (unsigned int code) const;
    Cliente     *_getCliente    (unsigned int code) const;
    Funcionario *_getFuncionario(unsigned int code) const;
public:
    Pessoas();
    ~Pessoas();

    const Cliente     *cadastrarCliente   (unsigned int telefone, std::string nome, std::string endereco, unsigned int pontos);
    const Funcionario *cadastrarFuncionaro(unsigned int telefone, std::string nome, std::string cargo, float salario);

    const Pessoa      *getPessoa	 (unsigned int code) const;
    const Cliente     *getCliente	 (unsigned int code) const;
    const Funcionario *getFuncionario(unsigned int code) const;

    void addPontos(const Cliente *cliente, int diarias) const;
};

#endif