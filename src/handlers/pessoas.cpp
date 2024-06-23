#include <stdexcept>

#include "pessoas.hpp"

Pessoas::Pessoas(): pessoas({}) {};

Pessoas::~Pessoas () {
    for(Pessoa *pessoa: this -> pessoas) {
        delete pessoa;
    }
}

Pessoa *Pessoas::_getPessoa(unsigned int codigo) const {
	for(Pessoa *pessoa: this -> pessoas) {
		if(pessoa -> getCodigo() == codigo) return pessoa;
	}
	return nullptr;
}

Cliente *Pessoas::_getCliente(unsigned int codigo) const {
	return dynamic_cast<Cliente*>(this -> _getPessoa(codigo));
}

Funcionario *Pessoas::_getFuncionario(unsigned int codigo) const {
	return dynamic_cast<Funcionario*>(this -> _getPessoa(codigo));
}

const Cliente *Pessoas::cadastrarCliente(unsigned int telefone, std::string nome, std::string endereco, unsigned int pontos) {
	Cliente *cliente = new Cliente(this -> nextCode, telefone, pontos, nome, endereco);
	this -> pessoas.push_back(cliente);
	this -> nextCode++;
	return cliente;
}

const Funcionario *Pessoas::cadastrarFuncionaro(unsigned int telefone, std::string nome, std::string cargo, float salario) {
	Funcionario *funcionario = new Funcionario(this -> nextCode, telefone, nome, cargo, salario);
	this -> pessoas.push_back(funcionario);
	this -> nextCode++;
	return funcionario;
}

const Pessoa *Pessoas::getPessoa(unsigned int codigo) const {
	Pessoa *pessoa = this -> _getPessoa(codigo);
	if(pessoa == nullptr) throw std::runtime_error("Pessoa não encontrada.");
	return pessoa;
}

const Cliente *Pessoas::getCliente(unsigned int codigo) const {
	Cliente *cliente = this -> _getCliente(codigo);
	if(cliente == nullptr) throw std::runtime_error("Cliente não encontrado.");
	return cliente;
}

const Funcionario *Pessoas::getFuncionario(unsigned int codigo) const {
	Funcionario *funcionario = this -> _getFuncionario(codigo);
	if(funcionario == nullptr) throw std::runtime_error("Funcionario não encontrado.");
	return funcionario;
}

void Pessoas::addPontos(const Cliente *cliente, int diarias) const {
	this -> _getCliente(cliente -> getCodigo()) -> addPontos(diarias);
}