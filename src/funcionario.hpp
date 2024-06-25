#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP

#include <string>

#include "pessoa.hpp"

class Funcionario: public Pessoa {//definição da classe Funcionário herdando da classe Pessoa
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
    );//construtor da classe

    const std::string getCargo()   const;
    const float       getSalario() const;
    //retornos de constantes para somente leitura

    void setSalario(float salario); //método para definir o salário do funcionário
};

#endif