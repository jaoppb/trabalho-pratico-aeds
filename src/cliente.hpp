#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <vector>
#include <string>

using namespace std;

class Cliente {
private:
    unsigned int codigo, tel; //unsigned = não guarda o sinal do número ou seja so armazena 0 ou positivo
    string endereco, nome;

public:
    Cliente(
        unsigned int codigo,
        unsigned int telefone,
        string endereco,
        string nome
    );

    const unsigned int getCodigo() const; //const no tipo impede alteração depois de pegar o valor 
    const unsigned int getTelefone() const; //const depois do metódo indica que não altera nenhum valor do objeto
    const string getEndereco() const;
    const string getNome() const;

    void setTelefone(int tel);
    void setEndereco(string casa);
    void setNome(string name);
};

class Clientes {
private:
    vector<Cliente*> clientes; //usar ponteiro para armazenar valores permite que a memória fique mais distribuída
    unsigned int proximoCodigo;
    const int gerarCodigo();
    bool checkCodigo(int codigo); //como cliente vai ser gerado dentro da classe não precisa de ser público
public:
    Clientes(); //alguns valores precisam ser inicializados
    ~Clientes(); //como os clientes estão sendo gerados com `new` é uma boa prático limpá-los
    const Cliente* addCliente( //retorna o ponteiro com acesso somente a leitura depois de criado
        unsigned int telefone,
        string endereco,
        string nome
    );
    const Cliente *getCliente(unsigned int codigo);
    const bool removerCliente(unsigned int codigo);
};

#endif