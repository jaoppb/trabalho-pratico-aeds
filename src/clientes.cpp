#include <iostream>
#include "clientes.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

//class Pessoas
Pessoas::Pessoas(string nome):
    codigo(0), telefone(0), nome(nome) {}

int Pessoas::getCodigo()   const { return this->codigo; }
int Pessoas::getTelefone() const { return this->telefone; }
string Pessoas::getNome()  const { return this->nome; }

//class Cliente
Cliente::Cliente(string endereco, string nome)://construtor da class Cliente que recebe como parametro duas strings para nome e endereco
    Pessoas(nome), endereco(endereco) {}

string Cliente::getEndereco()   const { return this->endereco; }

//class Funcionario
Funcionario::Funcionario(string nome, float salario, string cargo): //construtor da class Funcionario que recebe como parametro duas strings para nome e cargo e um real do tipo float para salario
    Pessoas(nome), salario(0.0), cargo("") {}//declara salario como incialmente sempre zero para evitar erros inesperados e chama o construtor da classe Pessoas

string Funcionario::getCargo()  const { return this->cargo; }
float Funcionario::getSalario() const { return this->salario; }

GerirCodigos::GerirCodigos() {
    std::srand(std::time(NULL));//responsavel por definir a semente para a geração de codigos aleatorios com base no tempo atual
}
GerirCodigos::~GerirCodigos() {}//destrutor da classe GerirCodigos

int GerirCodigos::gerarCodigos() {
    int codigo;
    do {
        codigo = 1 + floor(std::rand() * 1000); // gera codigos entre 1 e 1000
    } while (std::find(codigosGerados.begin(), codigosGerados.end(), codigo) != codigosGerados.end());//continua gerando codigos em quanto o codigo ja existente não for encontrado, isso faz com que seja garantido que os codigos gerados não se dupliquem

    codigosGerados.push_back(codigo);//guarda o novo codigo gerado no vetor 
    return codigo;
}

void GerirCodigos::cadastrarCliente(vector<Cliente>& cliente, string nome, string endereco)//recebe como parametro um vetor e duas strings
{

    int novoCodigo = gerarCodigos();
    Cliente novoCliente(nome, endereco);//cria um objeto da classe Cliente com nome e endereco
    novoCliente.setCodigo();//define o codigo para o novoCliente
    cliente.push_back(novoCliente);//adiciona o novoCliente ao vetor
    cout << "Cliente cadastrado com sucesso! Seja bem vindo(a) ao Hotel Descanso garantido Sr.(a) " << nome << "o seu codigo eh: " << novoCodigo << endl; 
}

void GerirCodigos::cadastrarFuncionario(std::vector<Funcionario>& funcionario, float salario, std::string cargo, std::string nome)//recebe como parametro um vetor, duas strings e um real do tipo float
{
    int novoCodigo = gerarCodigos();
    Funcionario novoFuncionario(nome, salario, cargo );//cria um objeto da classe Funcionario com nome, salario e cargo
    novoFuncionario.setCodigo();
    funcionario.push_back(novoFuncionario);
    cout << "Funcionario cadastrado com sucesso! Tenha um bom dia de servico" << nome << " seu codigo eh: " << novoCodigo << endl;

}
int main() {
 
    std::vector<Cliente> clientes;
    std::vector<Funcionario> funcionarios; 
    
    GerirCodigos gerenciador;

    gerenciador.cadastrarCliente(clientes, "Yuri ", "Rua dos Clientes, 123");

    gerenciador.cadastrarFuncionario(funcionarios, 2500.00, "Recepcionista", " Viana ");

    return 0;
}



