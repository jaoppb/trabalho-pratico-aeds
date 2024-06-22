#include "cliente.hpp"

//class Cliente

Cliente::Cliente(//construtor da class Cliente que recebe como parametro duas strings para nome e endereco
    unsigned int codigo,
    unsigned int telefone,
    std::string nome,
    std::string endereco
    ): Pessoa(codigo, telefone, nome), endereco(endereco) {}

std::string Cliente::getEndereco() const { return this->endereco; }