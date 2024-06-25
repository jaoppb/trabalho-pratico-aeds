#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>

class Pessoa {//definição da classe Pessoa
private:
    unsigned int codigo;
    unsigned int telefone;
    std::string nome;
public:
    Pessoa(unsigned int codigo, unsigned int telefone, std::string nome);//construtor da classe Pessoa
    virtual ~Pessoa();//destrutor virtual da classe Pessoa

    const unsigned int getCodigo()   const;
    const unsigned int getTelefone() const;
    const std::string  getNome()     const;
    //constantes que retornam seus atributos somente para leitura
};

#endif