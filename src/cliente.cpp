#include "cliente.hpp"
#include <iostream>
#include <vector>

using namespace std;

// Implementação dos métodos da classe Cliente

Cliente::Cliente(
    unsigned int codigo,
    unsigned int telefone,
    string endereco,
    string nome
): codigo(codigo), tel(telefone), endereco(endereco), nome(nome) {}

const unsigned int Cliente::getCodigo() const {
    return codigo;
}

const unsigned int Cliente::getTelefone() const {
    return tel;
}

const string Cliente::getEndereco() const {
    return endereco;
}

const string Cliente::getNome() const {
    return nome;
}

void Cliente::setTelefone(int tel) {
    this->tel = tel;
}

void Cliente::setEndereco(string casa) {
    this->endereco = casa;
}

void Cliente::setNome(string name) {
    this->nome = name;
}

// Implementação dos métodos da classe Clientes

Clientes::Clientes(): clientes({}), proximoCodigo(0) {}

Clientes::~Clientes() {
    for(Cliente *cliente: this -> clientes) {
        delete cliente;
    }
}

const int Clientes::gerarCodigo() {
    return ++proximoCodigo; // incrementa e retorna o próximo código
}

bool Clientes::checkCodigo(int codigo) {
    for(Cliente *cliente: this -> clientes) { // percorre todos os valores de clientes e a cada valor roda o for atribuindo o valor a cliente 
        if(cliente -> getCodigo() == codigo) {
            return true;
        }
    }
    return false; // essa função serve para verificar se já existe um cliente cadastrado com certo código
}

const Cliente* Clientes::addCliente(
    unsigned int telefone,
    string endereco,
    string nome
) {
    unsigned int code = this -> gerarCodigo();
    if(this -> checkCodigo(code)) {
        cout << "Código já cadastrado." << endl; // codigo ja cadastrado
        return nullptr; //retorna NULL como não foi possível cadastrar o cliente
    }

    Cliente *cliente = new Cliente(
        code,
        telefone,
        endereco,
        nome
    ); //gera um pointeiro para o objeto cliente
    
    clientes.push_back(cliente); // adiciona o código gerado no vetor cliente
    return cliente;
}

const Cliente* Clientes::getCliente(unsigned int codigo) {
    for(Cliente *cliente: this -> clientes) {
        if(cliente -> getCodigo() == codigo) {
            return cliente;
        }
    }
    return nullptr;
}

const bool Clientes::removerCliente(unsigned int codigo) {
    int len = clientes.size(); // len = length = largura/tamanho
    for(int i = 0; i < len; i++) {
        if(this -> clientes[i] -> getCodigo() == codigo) {
            clientes.erase(clientes.begin() + i); // erase serve para remover elementos 
            return true;
        }
    }
    cout << "Cliente com código " << codigo << " não encontrado." << endl; // Erro: Cliente com o código não encontrado
    return false;
}