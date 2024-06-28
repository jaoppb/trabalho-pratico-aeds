#include <stdexcept>
#include <vector>

#include "pessoas.hpp"
#include "../utils.hpp"

/*
 * Construtor de Pessoas
 *
 * Carrega os dados do arquivo `data/pessoas.bin` caso load seja `true`
 * 
 * @param load
 */
Pessoas::Pessoas(bool load): pessoas({}), fileHandler("./data/pessoas.bin") {
	if(load) this->load();
};

/*
 * Realiza a leitura do arquivo até que seu final seja encontrado,
 * e armazena cada dado no vetor `pessoas`.
 */
void Pessoas::load() {
	this->fileHandler.open();
	if(this->fileHandler.isEOF()) this->nextCode = 0;
	else this->fileHandler.read((void*)&this->nextCode, sizeof(this->nextCode));

	while(!this->fileHandler.isEOF()) {
		char type;
		unsigned int code, points;
		float wage;
		std::string number, name, address, role;

		this->fileHandler.read((void*)&type, sizeof(type));
		this->fileHandler.read((void*)&code, sizeof(code));
		this->fileHandler.read(number);
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

/*
 * Desconstrutor de Pessoas
 *
 * Salva todos os dados do vetor `pessoas` no arquivo `data/pessoas.bin`
 * 
 * Formato Cliente:     'c$code$number$name$address$points'
 * Formato Funcionário: 'f$code$number$name$role$wage'
 */
Pessoas::~Pessoas () {
	this->fileHandler.clear();
	this->fileHandler.open();
	this->fileHandler.write((void*)&this->nextCode, sizeof(this->nextCode));
    for(Pessoa *pessoa: this -> pessoas) {
		char type = '\0';
		unsigned int code, points;
		float wage;
		std::string number, name, address, role;

		code   = pessoa->getCodigo();
		number = pessoa->getTelefone();
		name   = pessoa->getNome();

		Cliente *cliente = dynamic_cast<Cliente*>(pessoa);
		Funcionario *funcionario = dynamic_cast<Funcionario*>(pessoa);
		
		type = (cliente != NULL ? 'c' : funcionario != NULL ? 'f' : 'p');
		this->fileHandler.write((void*)&type, sizeof(type));

		this->fileHandler.write((void*)&code, sizeof(code));
		this->fileHandler.write(number);
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

/*
 * Método interno para achar a pessoa com o código `codigo`
 *
 * @param unsigned int codigo
 * 
 * @returns nullptr caso nenhuma seja encontrada
 * 
 * @return *Pessoa
 */
Pessoa *Pessoas::_getPessoa(unsigned int codigo) const {
	for(Pessoa *pessoa: this -> pessoas) {
		if(pessoa -> getCodigo() == codigo) return pessoa;
	}
	return nullptr;
}

/*
 * Método interno para achar o cliente com o código `codigo`
 *
 * @param unsigned int codigo
 * 
 * @returns nullptr caso nenhum seja encontrado
 * 
 * @return *Cliente
 */
Cliente *Pessoas::_getCliente(unsigned int codigo) const {
	return dynamic_cast<Cliente*>(this -> _getPessoa(codigo));
}

/*
 * Método interno para achar o funcionário com o código `codigo`
 *
 * @param unsigned int codigo
 * 
 * @returns nullptr caso nenhum seja encontrado
 * 
 * @return *Cliente
 */
Funcionario *Pessoas::_getFuncionario(unsigned int codigo) const {
	return dynamic_cast<Funcionario*>(this -> _getPessoa(codigo));
}

/*
 * Método interno para carregar um cliente com os dados passados no vetor `pessoas`
 *
 * Retorna um ponteiro para o objeto gerado.
 * 
 * @param unsigned int code
 * @param std::string  telefone
 * @param std::string  nome
 * @param std::string  endereco
 * @param ungined int  pontos
 * 
 * return *Cliente
 */
Cliente *Pessoas::_loadCliente(unsigned int code, std::string telefone, std::string nome, std::string endereco, unsigned int pontos) {
	Cliente *cliente = new Cliente(code, pontos, telefone, nome, endereco);
	this->pessoas.push_back(cliente);
	return cliente;
}

/*
 * Método interno para carregar um funcionário com os dados passados no vetor `pessoas`
 *
 * Retorna um ponteiro para o objeto gerado.
 * 
 * @param unsigned int code
 * @param std::string  telefone
 * @param std::string  nome
 * @param std::string  cargo
 * @param float		   salario
 * 
 * return *Funcionario
 */
Funcionario *Pessoas::_loadFuncionaro(unsigned int code, std::string telefone, std::string nome, std::string cargo, float salario) {
	Funcionario *funcionario = new Funcionario(code, telefone, nome, cargo, salario);
	this->pessoas.push_back(funcionario);
	return funcionario;
}

/*
 * Retorna o total de pessoas cadastradas.
 *
 * @return size_t
 */
const size_t Pessoas::getTotal() const { return this->pessoas.size(); }

/*
 * Retorna o total de clientes cadastrados no vetor `pessoas`
 *
 * @return size_t
 */
const size_t Pessoas::getTotalClients() const {
	size_t result = 0;
	for(Pessoa *pessoa: this->pessoas) {
		if(dynamic_cast<Cliente*>(pessoa) != NULL) result++;
	}
	return result;
}

/*
 * Retorna o total de funcionarios cadastrados no vetor `pessoas`
 *
 * @return size_t
 */
const size_t Pessoas::getTotalEmployess() const {
	size_t result = 0;
	for(Pessoa *pessoa: this->pessoas) {
		if(dynamic_cast<Funcionario*>(pessoa) != NULL) result++;
	}
	return result;
}

/*
 * Cadastra um cliente com o código `nextCode` e com os dados passados
 *
 * Retorna um ponteiro read-only para o objeto gerado
 * 
 * @param std::string  telefone
 * @param std::string  nome
 * @param std::string  endereco
 * @param unsigned int pontos
 */
const Cliente *Pessoas::cadastrarCliente(std::string telefone, std::string nome, std::string endereco, unsigned int pontos) {
	Cliente *cliente = new Cliente(this -> nextCode, pontos, telefone, nome, endereco);
	this -> pessoas.push_back(cliente);
	this -> nextCode++;
	return cliente;
}

/*
 * Cadastra um funcionario com o código `nextCode` e com os dados passados
 *
 * Retorna um ponteiro read-only para o objeto gerado
 * 
 * @param std::string telefone
 * @param std::string nome
 * @param std::string cargo
 * @param float		  salario
 */
const Funcionario *Pessoas::cadastrarFuncionaro(std::string telefone, std::string nome, std::string cargo, float salario) {
	Funcionario *funcionario = new Funcionario(this -> nextCode, telefone, nome, cargo, salario);
	this -> pessoas.push_back(funcionario);
	this -> nextCode++;
	return funcionario;
}

/*
 * Acesso público ao método `_getPessoa(unsigned int codigo)`
 *
 * @param unsigned int codigo
 * 
 * @return const Pessoa*
 */
const Pessoa *Pessoas::getPessoa(unsigned int codigo) const {
	Pessoa *pessoa = this -> _getPessoa(codigo);
	if(pessoa == nullptr) throw std::runtime_error("Pessoa não encontrada.");
	return pessoa;
}

/*
 * Acesso público ao método `_getCliente(unsigned int codigo)`
 *
 * @param unsigned int codigo
 * 
 * @return const Cliente*
 */
const Cliente *Pessoas::getCliente(unsigned int codigo) const {
	Cliente *cliente = this -> _getCliente(codigo);
	if(cliente == nullptr) throw std::runtime_error("Cliente não encontrado.");
	return cliente;
}

/*
 * Acesso público ao método `_getFuncionario(unsigned int codigo)`
 *
 * @param unsigned int codigo
 * 
 * @return const Funcionario*
 */
const Funcionario *Pessoas::getFuncionario(unsigned int codigo) const {
	Funcionario *funcionario = this -> _getFuncionario(codigo);
	if(funcionario == nullptr) throw std::runtime_error("Funcionario não encontrado.");
	return funcionario;
}

/*
 * Retorna um vetor com ponteiros para todos as pessoas
 * cujo nome tenham a substring `name`
 * 
 * @param std::string name
 * 
 * @return const std::vector<Pessoa*>
 */
const std::vector<Pessoa*> Pessoas::getPessoa(std::string name) const {
	std::vector<Pessoa*> result;
	toLower(name);
	for(Pessoa *pessoa: this->pessoas) {
		std::string nomePessoa = pessoa->getNome();
		toLower(nomePessoa);
		if(nomePessoa.find(name) != std::string::npos)
			result.push_back(pessoa);
	}
	return result;
}

/*
 * Retorna um vetor com ponteiros para todos os clientes
 * cujo nome tenham a substring `name`
 * 
 * @param std::string name
 * 
 * @return const std::vector<Cliente*>
 */
const std::vector<Cliente*> Pessoas::getCliente(std::string name) const {
	std::vector<Cliente*> result;
	for(Pessoa *pessoa: this->getPessoa(name)) {
		Cliente *cliente = dynamic_cast<Cliente*>(pessoa);
		if(cliente) result.push_back(cliente);
	}
	return result;
}

/*
 * Retorna um vetor com ponteiros para todos os funcionáios
 * cujo nome tenham a substring `name`
 * 
 * @param std::string name
 * 
 * @return const std::vector<Funcionario*>
 */
const std::vector<Funcionario*> Pessoas::getFuncionario(std::string name) const {
	std::vector<Funcionario*> result;
	for(Pessoa *pessoa: this->getPessoa(name)) {
		Funcionario *funcionario = dynamic_cast<Funcionario*>(pessoa);
		if(funcionario) result.push_back(funcionario);
	}
	return result;
}

/*
 * Adiciona os pontos ao cliente `cliente` com base nas diarias `diarias`
 *
 * @param const Cliente *cliente
 * @param 		int		 diarias
 */
void Pessoas::addPontos(const Cliente *cliente, int diarias) const {
	this -> _getCliente(cliente -> getCodigo()) -> addPontos(diarias);
}