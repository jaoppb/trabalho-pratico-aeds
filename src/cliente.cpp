#include "cliente.hpp"
#include <stdexcept>


Cliente::Cliente(
    unsigned int codigo,
    unsigned int telefone,
    unsigned int pontos,
    std::string nome,
    std::string endereco
    ): Pessoa(codigo, telefone, nome), endereco(endereco), pontos(pontos) {
    if (pontos < 0) {
        throw std::invalid_argument("Pontos nao podem ser negativos");
    }
    if (endereco.empty()) {
        throw std::invalid_argument("Endereco nao pode ser vazio");
    }
}

const int Cliente::getPontos() const { return this->pontos; }

void Cliente::addPontos(int diarias) {
    if (diarias < 0) {
        throw std::invalid_argument("Diarias não podem ser negativas");
    }
    this->pontos += diarias * 10;
}

std::string Cliente::getEndereco() const { return this->endereco; }

void Cliente::setEndereco(std::string endereco) {
    if (endereco.empty()) {
        throw std::invalid_argument("Endereco nao pode ser vazio");
    }
    this->endereco = endereco;
}