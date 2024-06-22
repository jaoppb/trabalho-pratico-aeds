#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <vector>

#include "pessoa.hpp"

class Cliente: public Pessoa {
private:
    std::string endereco;
    int pontos;

public:
    Cliente(
        unsigned int codigo,
        unsigned int telefone,
        unsigned int pontos,
        std::string nome,
        std::string endereco
    );

    int getPontos();

    void addPontos(int diarias);

    std::string getEndereco() const;

    void setEndereco(std::string endereco);
};

#endif