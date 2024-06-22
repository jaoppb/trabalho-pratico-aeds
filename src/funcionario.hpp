#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP

#include <string>

#include "pessoa.hpp"

class Funcionario: public Pessoa {
private:    
    std::string cargo;
    float salario;

public:
    Funcionario(
        unsigned int codigo,
        unsigned int telefone,
        std::string nome,
        std::string cargo,
        float salario
    );

    const std::string getCargo()   const;
    const float       getSalario() const;

    void setSalario(float salario);
};

#endif