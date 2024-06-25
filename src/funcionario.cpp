#include <stdexcept>

#include "funcionario.hpp"

//class Funcionario
Funcionario::Funcionario( //implementação do construtor da classe Funcionário
    unsigned int codigo,
    unsigned int telefone,
    std::string nome,
    std::string cargo,
    float salario
    ): Pessoa(codigo, telefone, nome), cargo(cargo) {//inicialização dos atributos herdados da classe Pessoa e também da prórpia classe Funcionario
    if(salario < 0) throw std::runtime_error("O salario não pode ser negativo");
    this -> salario = salario;//caso o salário seja negativo, um erro é lançado
}

const std::string Funcionario::getCargo()  const { return this->cargo; }//retorna o respectivo cargo somente para leitura
const float Funcionario::getSalario() const { return this->salario; }//retorna o salário somente para leitura
void Funcionario::setSalario(float salario) {
    if(salario < 0) throw std::runtime_error("O salario não pode ser negativo");
    this->salario = salario;
}