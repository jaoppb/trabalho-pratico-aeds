#include <stdexcept>

#include "quartos.hpp"

/*
 * Construtor da classe Quartos.
 * Decide se os dados devem ser carregados do arquivo `data/quartos.bin`
 * 
 * @param bool load
 */
Quartos::Quartos(bool load): quartos({}), fileHandler("./data/quartos.bin") {
	if(load) this->load();
}

/*
 * Faz a abertura do arquivo pelo fileHandler,
 realiza a leitura dos dados e os armazena em `quartos`
 */
void Quartos::load() {
	this->fileHandler.open();
	while(!this->fileHandler.isEOF()) {
		unsigned int number, guests;
		float valorDiaria;
		bool status;

		this->fileHandler.read((void*)&number, 		sizeof(number));
		this->fileHandler.read((void*)&valorDiaria, sizeof(valorDiaria));
		this->fileHandler.read((void*)&guests, 		sizeof(guests));
		this->fileHandler.read((void*)&status, 		sizeof(status));
		
		this->_loadQuarto(number, valorDiaria, guests, status);
	}
	this->fileHandler.close();
}

/*
 * Desconstrutor de Quartos
 *
 * Salva todos os dados do vetor `quartos` no arquivo do fileHandler
 * 
 * Formato: '$number$dailyCost$capacity$status'
 */
Quartos::~Quartos() {
	this->fileHandler.clear();
	this->fileHandler.open();
	for(Quarto *quarto: this->quartos) {
		unsigned int number = quarto->getNumero(),
					 guests = quarto->getQuantidadeDeHospedes();
		float valorDiaria	= quarto->getDiaria();
		bool status			= quarto->getStatus();

		this->fileHandler.write((void*)&number, 	 sizeof(number));
		this->fileHandler.write((void*)&valorDiaria, sizeof(valorDiaria));
		this->fileHandler.write((void*)&guests, 	 sizeof(guests));
		this->fileHandler.write((void*)&status, 	 sizeof(status));

		delete quarto;
	}
	this->fileHandler.close();
}

/*
 * Método interno para adicionar um quarto ao vetor `quartos`
 * com os parametros passados
 * 
 * Retona um ponteiro para o objeto gerado
 * 
 * @param unsigned int numero
 * @param float 	   valorDiaria
 * @param unsigned int guests
 * @param bool		   status
 * 
 * return *Quarto
 */
Quarto *Quartos::_loadQuarto(unsigned int numero, float valorDiaria, unsigned int guests, bool status) {
	Quarto *quarto = new Quarto(numero, valorDiaria, guests, status);
	this->quartos.push_back(quarto);
	return quarto;
}

/*
 * Retorna o número de quartos registrados no
 * vetor `quartos`.
 */
const size_t Quartos::getTotal() const { return this->quartos.size(); }

/*
 * Cria um quarto com os parametros passados
 *
 * Lança um erro caso já tenha um quarto com o número registrado
 * 
 * Retorna um ponteiro read-only para o objeto criado
 * 
 * @param unsigned int numero
 * @param float		   valorDiaria
 * @param unsigned int guests(capacity)
 * 
 * @throw std::runtime_error
 * 
 * @return Quarto*
 */
const Quarto* Quartos::criarQuarto(unsigned int numero, float valorDiaria, unsigned int guests) {
	int length = this -> quartos.size();
	for(int i = 0; i < length; i++) {
		if(this -> quartos[i] -> getNumero() == numero) throw std::runtime_error("Um quarto com esse número já existe");
	}

	Quarto *quarto = new Quarto(numero, valorDiaria, guests);
	this -> quartos.push_back(quarto);
	return quarto;
}

/*
 * Retorna um ponteiro read-only para o objeto quarto registrado
 * em `quartos` cujo o número seja igual à `numero`.
 * 
 * Lança um erro caso o quarto não seja encontrado.
 * 
 * @param unsigned int numero
 *
 * @throw std::runtime_error
 *  
 * @return const Quarto*
 */
const Quarto* Quartos::getQuarto(unsigned int numero) const {
	if(numero < 0) throw std::runtime_error("O número do quarto precisa ser zero ou positivo");

	for(int i = this -> quartos.size() - 1; i >= 0; i--) {
		if(this -> quartos[i] -> getNumero() == numero) return this -> quartos[i];
	}

	throw std::runtime_error("Quarto não encontrado");
}

/*
 * Altera o status do quarto de número `numero` para `status`.
 *
 * @param unsigned int numero
 * @param bool		   status
 */
void Quartos::setStatus(unsigned int numero, bool status) {
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

/*
 * Altera o status do quarto passado para `status`.
 *
 * Utiliza o método `setStatus(unsigned int numero, bool status)`,
 * então tudo que se aplica ao outro método se aplica a esse.
 * 
 * @param const Quarto *quarto
 * @param bool		  	status
 */
void Quartos::setStatus(const Quarto *quarto, bool status) {
	this -> setStatus(quarto -> getNumero(), status);
}

/*
 * Retorna o status do quarto de número `numero`
 *
 * Utiliza o método `getQuarto(`
 * 
 * @return const bool
 */
const bool Quartos::getStatus(unsigned int numero) const {
	return this -> getQuarto(numero) -> getStatus();

	throw std::runtime_error("Número do quarto inválido");
}

/*
 * Retorna todos os quarto do vetor `quarto` cuja a capacidade seja
 * no minimo capacity
 * 
 * @param unsigned int capacity
 */
const std::vector<Quarto*> Quartos::getRoomsByCapacity(unsigned int capacity) {
	std::vector<Quarto*> result({});
	for(Quarto *quarto: this->quartos) {
		if(quarto->getQuantidadeDeHospedes() >= capacity)
			result.push_back(quarto);
	}
	return result;
}