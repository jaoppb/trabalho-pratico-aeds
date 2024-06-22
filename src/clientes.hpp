#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <vector>

class Pessoas {
private:
    int codigo;
    int telefone;
    std::string nome;

public:
    Pessoas(std::string nome);

    int getCodigo()     const;
    int getTelefone()   const;
    std::string getNome()    const;

    void setCodigo() { this->codigo = codigo; }

};

class Cliente: public Pessoas {
private:
    std::string endereco;

public:
    Cliente(std::string nome, std::string endereco);

    std::string getEndereco() const;

    void setEndereco(std::string endereco) { this->endereco = endereco; };
};

class Funcionario: public Pessoas {
private:    
    std::string cargo;
    float salario;

public:
    Funcionario(std::string nome, float salario, std::string cargo);

    std::string getCargo() const;

    float getSalario() const;

    void setSalario(float salario)  { this->salario = salario; }
};

class GerirCodigos {
private:
    std::vector <int> codigosGerados;

public:
    GerirCodigos();
    ~GerirCodigos();

    int gerarCodigos();

    void cadastrarCliente(std::vector<Cliente>& cliente, std::string nome, std::string endereco );
    void cadastrarFuncionario(std::vector<Funcionario>& funcionario, float salario, std::string cargo, std::string nome);     

};


#endif