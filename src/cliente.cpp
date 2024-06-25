#include "cliente.hpp"
#include <stdexcept>


Cliente::Cliente(//implementação do construtor da classe Cliente
    unsigned int codigo,
    unsigned int pontos,
    std::string telefone,
    std::string nome,
    std::string endereco
    ): Pessoa(codigo, telefone, nome), endereco(endereco), pontos(pontos) {//inicialização dos atributos herdados da classe Pessoa e também da prórpia classe Cliente
    if (pontos < 0) {
        throw std::invalid_argument("Pontos nao podem ser negativos");//verificação para ver se os pontos são negativos, caso sejam, um erro é lançado
    }
    if (endereco.empty()) {
        throw std::invalid_argument("Endereco nao pode ser vazio");//verificação para ver se o endereço esta vázio, caso esteja, um erro é lançado
    }
}

const int Cliente::getPontos() const { return this->pontos; }//implementação do método que retorna o número de pontos do cliente

void Cliente::addPontos(int diarias) {//implementação do método para adicionar pontos ao cliente com base nas diárias
    if (diarias < 0) {
        throw std::invalid_argument("Diarias não podem ser negativas");//verificação para ver se as diárias estão negativas
    }
    this->pontos += diarias * 10;//adição dos pontos ao cliente
}

std::string Cliente::getEndereco() const { return this->endereco; }//implementação do método que retorna o endereço do cliente

void Cliente::setEndereco(std::string endereco) {
    if (endereco.empty()) {
        throw std::invalid_argument("Endereco nao pode ser vazio");
    }
    this->endereco = endereco;//definição do novo endereço 
}