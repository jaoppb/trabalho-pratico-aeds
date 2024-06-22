#include <stdexcept>

#include "handlers.hpp"

//Class Pessoas

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

const Cliente *Pessoas::cadastrarCliente(unsigned int telefone, std::string nome, std::string endereco) {
	Cliente *cliente = new Cliente(this -> nextCode, telefone, nome, endereco);
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
	return this -> _getPessoa(codigo);
}

const Cliente *Pessoas::getCliente(unsigned int codigo) const {
	return dynamic_cast<Cliente*>(this -> _getPessoa(codigo));
}

const Funcionario *Pessoas::getFuncionario(unsigned int codigo) const {
	return dynamic_cast<Funcionario*>(this -> _getPessoa(codigo));
}

//Class Estadias

Estadias::Estadias(): estadias({}) {
	this -> nextCode = 0;
}

Estadias::~Estadias() {
	for(Estadia *estadia: this -> estadias) {
		delete estadia;
	}
}

const bool Estadias::_checkEstadia(Estadia *novaEstadia) {
	for(const Estadia *estadia: this -> estadias) {
		if(estadia -> getQuarto() -> getNumero() != novaEstadia -> getQuarto() -> getNumero()) continue;

		if(!((estadia -> getCheckOutDate() < novaEstadia -> getCheckInDate()) ||
			  novaEstadia -> getCheckOutDate() < estadia -> getCheckInDate())) return false;
	}

	return true;
}

const Estadia* Estadias::agendarEstadia(
	std::string dataEntrada,
	std::string dataSaida,
	int codigoCliente,
	int numeroDoQuarto) {
	Estadia *estadia = new Estadia(this -> nextCode, dataEntrada, dataSaida, codigoCliente, numeroDoQuarto);
	if(!this -> _checkEstadia(estadia)) {
		delete estadia;
		return nullptr;
	}
	
	this -> nextCode++;
	return estadia;
}

//Class Quartos

Quartos::Quartos(): quartos({}) {}

Quartos::~Quartos() {
	for(int i = this -> quartos.size() - 1; i >= 0; i--) {
		delete this -> quartos[i];
	}
}

const Quarto* Quartos::criarQuarto(int numero, float valorDiaria) {
	int length = this -> quartos.size();
	for(int i = 0; i < length; i++) {
		if(this -> quartos[i] -> getNumero() == numero) throw std::runtime_error("Um quarto com esse número já existe");
	}

	Quarto *quarto = new Quarto(numero, valorDiaria);
	this -> quartos.push_back(quarto);
	return quarto;
}

const Quarto* Quartos::getQuarto(int numero) const {
	if(numero < 0) throw std::runtime_error("O número do quarto precisa ser zero ou positivo");

	for(int i = this -> quartos.size() - 1; i >= 0; i--) {
		if(this -> quartos[i] -> getNumero() == numero) return this -> quartos[i];
	}

	throw std::runtime_error("Quarto não encontrado");
}

void Quartos::setStatus(int numero, bool status) {
	if(numero < 0) throw std::runtime_error("O número do quarto não pode ser negativo");

	for(int i = this -> quartos.size() - 1; i >= 0; i--) {
		Quarto *quarto = this -> quartos[i];
		if(quarto -> getNumero() == numero) {
			quarto -> setStatus(status);
			return;
		}
	}

	throw std::runtime_error("Número do quarto inválido");
}

const bool Quartos::getStatus(int numero) const {
	return this -> getQuarto(numero) -> getStatus();

	throw std::runtime_error("Número do quarto inválido");
}