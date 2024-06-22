#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <vector>

#include "pessoa.hpp"

class Cliente: public Pessoa {
private:
    std::string endereco;

public:
    Cliente(
        unsigned int codigo,
        unsigned int telefone,
        std::string nome,
        std::string endereco
    );

    std::string getEndereco() const;

    void setEndereco(std::string endereco) { this->endereco = endereco; };
};

#endif