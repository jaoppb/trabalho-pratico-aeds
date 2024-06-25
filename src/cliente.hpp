#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <vector>

#include "pessoa.hpp"

class Cliente: public Pessoa {//classe Cliente Herdando da classe Pessoa
private:
    std::string endereco;
    unsigned int pontos;

public:
    Cliente(
        unsigned int codigo,
        unsigned int pontos,
        std::string telefone,
        std::string nome,
        std::string endereco
    );//construtor da classe Cliente

    const int getPontos() const;//retorna o numero de pontos somente para leitura

    void addPontos(int diarias);//método para adicionar pontos ao cliente com base no número de diárias

    std::string getEndereco() const;//retorna o endereço do cliente para somente leitura

    void setEndereco(std::string endereco);//método para definir o endereço do cliente
};

#endif