#include "cliente.hpp"
#include <iostream>
#include <vector>

using namespace std;

// Implementação dos métodos da classe Cliente

int Cliente::getCodigo() const {
    return codigo;
}

void Cliente::setCodigo(int codigo) {
    this->codigo = codigo;
}

void Cliente::setTelefone(int tel) {
    this->tel = tel;
}

int Cliente::getTelefone() {
    return tel;
}

void Cliente::setEndereco(string casa) {
    this->endereco = casa;
}

string Cliente::getEndereco() {
    return endereco;
}

void Cliente::setNome(string name) {
    this->nome = name;
}

string Cliente::getNome() {
    return nome;
}

// Implementação dos métodos da classe CadastroCliente

int CadastroCliente::gerarCodigo() {
    static int ultimoCodigo = 0; // mantem o ultimo código gerado
    return ++ultimoCodigo; // incrementa e retorna o último código
}

bool CadastroCliente::checkCodigo(int codigo) {
    int VectorH = clientes.size();
    for(int i = 0; i < VectorH; i++) { // auto permite o compilador deduzir automaticamente o tipo de elemento, esse for percorre todos os elementos do vetor cliente   
        if(clientes[i].getCodigo() == codigo) {
            return true;
        }
    }
    return false; // essa função serve para verificar se já existe um cliente cadastrado com certo código
}

void CadastroCliente::addCliente(Cliente cliente) {
    if(checkCodigo(cliente.getCodigo())) {
        cout << "Código já cadastrado." << endl; // codigo ja cadastrado
    } else {
        cliente.setCodigo(gerarCodigo()); // gera um novo código para o cliente
        clientes.push_back(cliente); // adiciona o código gerado no vetor cliente
    }
}

bool CadastroCliente::removerCliente(int codigo) {
    int VectorH = clientes.size();
    for(int i = 0; i < VectorH; i++) {
        if(clientes[i].getCodigo() == codigo) {
            clientes.erase(clientes.begin() + i); // erase serve para remover elementos 
            return true;
        }
    }
    cout << "Cliente com código " << codigo << " não encontrado." << endl; // Erro: Cliente com o código não encontrado
    return false;
}
