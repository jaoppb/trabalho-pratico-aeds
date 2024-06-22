#include <stdexcept>

#include "funcionario.hpp"

//class Funcionario
Funcionario::Funcionario( //construtor da class Funcionario que recebe como parametro duas strings para nome e cargo e um real do tipo float para salario
    unsigned int codigo,
    unsigned int telefone,
    std::string nome,
    std::string cargo,
    float salario
    ): Pessoa(codigo, telefone, nome), cargo(cargo) {
    if(salario < 0) throw std::runtime_error("O salário não pode ser negativo");
    this -> salario = salario;
}

const std::string Funcionario::getCargo()  const { return this->cargo; }
const float Funcionario::getSalario() const { return this->salario; }