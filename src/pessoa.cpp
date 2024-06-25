#include <string>

#include "pessoa.hpp"

//class Pessoa
Pessoa::Pessoa(unsigned int codigo, std::string telefone, std::string nome)://implementação do construtor da classe Pessoa
    codigo(codigo), telefone(telefone), nome(nome) {}//inicializador dos atributos

Pessoa::~Pessoa() {}

const unsigned int Pessoa::getCodigo()   const { return this->codigo; }
const std::string  Pessoa::getTelefone() const { return this->telefone; }
const std::string  Pessoa::getNome()     const { return this->nome; }
//constantes para retorno em modo de leitura somente