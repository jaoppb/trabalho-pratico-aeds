#include <stdexcept>
#include <vector>

#include "pessoas.hpp"

Pessoas::Pessoas(bool load): pessoas({}), fileHandler("./data/pessoas.bin") {
	if(load) this->load();
};

void Pessoas::load() {
	this->fileHandler.open();
	if(this->fileHandler.isEOF()) this->nextCode = 0;
	else this->fileHandler.read((void*)&this->nextCode, sizeof(this->nextCode));

	while(!this->fileHandler.isEOF()) {
		char type;
		unsigned int code, number, points;
		float wage;
		std::string name, address, role;

		this->fileHandler.read((void*)&type, sizeof(type));
		this->fileHandler.read((void*)&code, sizeof(code));
		this->fileHandler.read((void*)&number, sizeof(number));
		this->fileHandler.read(name);

		if(type == 'c') {
			this->fileHandler.read(address);
			this->fileHandler.read((void*)&points, sizeof(points));

			this->_loadCliente(code, number, name, address, points);
		} else if(type = 'f') {
			this->fileHandler.read(role);
			this->fileHandler.read((void*)&wage, sizeof(wage));

			this->_loadFuncionaro(code, number, name, role, wage);
		}
	}
	this->fileHandler.close();
}

Pessoas::~Pessoas () {
	this->fileHandler.clear();
	this->fileHandler.open();
	this->fileHandler.write((void*)&this->nextCode, sizeof(this->nextCode));
    for(Pessoa *pessoa: this -> pessoas) {
		char type = '\0';
		unsigned int code, number, points;
		float wage;
		std::string name, address, role;

		code   = pessoa->getCodigo();
		number = pessoa->getTelefone();
		name   = pessoa->getNome();

		Cliente *cliente = dynamic_cast<Cliente*>(pessoa);
		Funcionario *funcionario = dynamic_cast<Funcionario*>(pessoa);
		
		type = (cliente != NULL ? 'c' : funcionario != NULL ? 'f' : 'p');
		this->fileHandler.write((void*)&type, sizeof(type));

		this->fileHandler.write((void*)&code, sizeof(code));
		this->fileHandler.write((void*)&number, sizeof(number));
		this->fileHandler.write(name);

		if(cliente != NULL) {
			address = cliente->getEndereco();
			points  = cliente->getPontos();

			this->fileHandler.write(address);
			this->fileHandler.write((void*)&points, sizeof(points));
		} else if(funcionario != NULL) {
			role = funcionario->getCargo();
			wage = funcionario->getSalario();

			this->fileHandler.write(role);
			this->fileHandler.write((void*)&wage, sizeof(wage));
		}

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

Cliente *Pessoas::_loadCliente(unsigned int code, unsigned int telefone, std::string nome, std::string endereco, unsigned int pontos) {
	Cliente *cliente = new Cliente(code, telefone, pontos, nome, endereco);
	this->pessoas.push_back(cliente);
	return cliente;
}

Funcionario *Pessoas::_loadFuncionaro(unsigned int code, unsigned int telefone, std::string nome, std::string cargo, float salario) {
	Funcionario *funcionario = new Funcionario(code, telefone, nome, cargo, salario);
	this->pessoas.push_back(funcionario);
	return funcionario;
}

const size_t Pessoas::getTotal() const { return this->pessoas.size(); }

const size_t Pessoas::getTotalClients() const {
	size_t result = 0;
	for(Pessoa *pessoa: this->pessoas) {
		if(dynamic_cast<Cliente*>(pessoa) != NULL) result++;
	}
	return result;
}

const size_t Pessoas::getTotalEmployess() const {
	size_t result = 0;
	for(Pessoa *pessoa: this->pessoas) {
		if(dynamic_cast<Funcionario*>(pessoa) != NULL) result++;
	}
	return result;
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

const std::vector<Pessoa*> Pessoas::getPessoa(std::string name) const {
	std::vector<Pessoa*> result;
	for(Pessoa *pessoa: this->pessoas) {
		if(pessoa->getNome().find(name)) result.push_back(pessoa);
	}
	return result;
}

const std::vector<Cliente*> Pessoas::getCliente(std::string name) const {
	std::vector<Cliente*> result;
	for(Pessoa *pessoa: this->getPessoa(name)) {
		Cliente *cliente = dynamic_cast<Cliente*>(pessoa);
		if(cliente) result.push_back(cliente);
	}
	return result;
}

const std::vector<Funcionario*> Pessoas::getFuncionario(std::string name) const {
	std::vector<Funcionario*> result;
	for(Pessoa *pessoa: this->getPessoa(name)) {
		Funcionario *funcionario = dynamic_cast<Funcionario*>(pessoa);
		if(funcionario) result.push_back(funcionario);
	}
	return result;
}

void Pessoas::addPontos(const Cliente *cliente, int diarias) const {
	this -> _getCliente(cliente -> getCodigo()) -> addPontos(diarias);
}