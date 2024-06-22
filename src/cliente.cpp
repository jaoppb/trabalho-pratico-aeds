#include "cliente.hpp"

//class Cliente

Cliente::Cliente(
    unsigned int codigo,
    unsigned int telefone,
    unsigned int pontos,
    std::string nome,
    std::string endereco
    ): Pessoa(codigo, telefone, nome), endereco(endereco), pontos(0) {}

int Cliente::getPontos() { return this-> pontos; }

void Cliente::addPontos(int diarias) { this->pontos += diarias*10; }

std::string Cliente::getEndereco() const { return this->endereco; }

void Cliente::setEndereco(std::string endereco)    { this->endereco = endereco; }