#ifndef HANDLERS_PESSOAS_HPP
#define HANDLERS_PESSOAS_HPP

#include <vector>

#include "../pessoa.hpp"
#include "../cliente.hpp"
#include "../funcionario.hpp"
#include "./files.hpp"

class Pessoas {
private:
    std::vector<Pessoa*> pessoas;
    unsigned int nextCode;

    FileHandler fileHandler;

	Pessoa      *_getPessoa     (unsigned int code) const;
    Cliente     *_getCliente    (unsigned int code) const;
    Funcionario *_getFuncionario(unsigned int code) const;

    Cliente     *_loadCliente   (unsigned int code, unsigned int telefone, std::string nome, std::string endereco, unsigned int pontos);
    Funcionario *_loadFuncionaro(unsigned int code, unsigned int telefone, std::string nome, std::string cargo, float salario);
public:
    Pessoas(bool load);
    ~Pessoas();

    void load();

    const size_t getTotal() const;
    const size_t getTotalClients() const;
    const size_t getTotalEmployess() const;

    const Cliente     *cadastrarCliente   (unsigned int telefone, std::string nome, std::string endereco, unsigned int pontos);
    const Funcionario *cadastrarFuncionaro(unsigned int telefone, std::string nome, std::string cargo, float salario);

    const Pessoa      *getPessoa	 (unsigned int code) const;
    const Cliente     *getCliente	 (unsigned int code) const;
    const Funcionario *getFuncionario(unsigned int code) const;

    const std::vector<Pessoa*>      getPessoa     (std::string name) const;
    const std::vector<Cliente*>     getCliente	  (std::string name) const;
    const std::vector<Funcionario*> getFuncionario(std::string name) const;

    void addPontos(const Cliente *cliente, int diarias) const;

    std::vector<Pessoa*> pesquisarPessoaPorNome(const std::string& nome) const;
    Pessoa* pesquisarPessoaPorCodigo(unsigned int codigo) const;
};

#endif