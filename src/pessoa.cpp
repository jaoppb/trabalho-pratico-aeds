#include <string>

#include "pessoa.hpp"

//class Pessoa
Pessoa::Pessoa(unsigned int codigo, unsigned int telefone, std::string nome):
    codigo(codigo), telefone(telefone), nome(nome) {}

Pessoa::~Pessoa() {}

const unsigned int        Pessoa::getCodigo()   const { return this->codigo; }
const unsigned int        Pessoa::getTelefone() const { return this->telefone; }
const std::string Pessoa::getNome()     const { return this->nome; }