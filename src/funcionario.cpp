#include <stdexcept>

#include "funcionario.hpp"

//class Funcionario
Funcionario::Funcionario( 
    unsigned int codigo,
    unsigned int telefone,
    std::string nome,
    std::string cargo,
    float salario
    ): Pessoa(codigo, telefone, nome), cargo(cargo) {
    if(salario < 0) throw std::runtime_error("O salario nao pode ser negativo");
    this -> salario = salario;
}

const std::string Funcionario::getCargo()  const { return this->cargo; }
const float Funcionario::getSalario() const { return this->salario; }
void Funcionario::setSalario(float salario) { this->salario = salario; }