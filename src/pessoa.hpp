#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>

class Pessoa {
private:
    unsigned int codigo;
    unsigned int telefone;
    std::string nome;
public:
    Pessoa(unsigned int codigo, unsigned int telefone, std::string nome);
    virtual ~Pessoa();

    const unsigned int getCodigo()   const;
    const unsigned int getTelefone() const;
    const std::string  getNome()     const;
};

#endif