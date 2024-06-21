#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <vector>
#include <string>

using namespace std;

class Cliente {
private:
    int codigo, tel;
    string endereco, nome;

public:
    int getCodigo() const; 
    void setCodigo(int codigo);
    void setTelefone(int tel);
    int getTelefone(); 
    void setEndereco(string casa);
    string getEndereco(); 
    void setNome(string name);
    string getNome(); 
};

class CadastroCliente {
private:
    vector<Cliente> clientes;
    int gerarCodigo();

public:
    void addCliente(Cliente cliente);
    bool removerCliente(int codigo);
    bool checkCodigo(int codigo);
};

#endif