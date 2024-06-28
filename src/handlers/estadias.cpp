#include <stdexcept>
#include <iostream>

#include "../global.hpp"
#include "../utils.hpp"
#include "estadias.hpp"

/*
 * Construtor da classe Estadias.
 * Decide se os dados devem ser carregados do arquivo `data/estadias.bin`
 * 
 * @param bool load
 */
Estadias::Estadias(bool load): estadias({}), fileHandler("./data/estadias.bin") {
	if(load) this->load();
}

/*
 * Faz a abertura do arquivo pelo fileHandler e realiza a leitura dos dados.
 */
void Estadias::load() {
	this->fileHandler.open();
	if(this->fileHandler.isEOF()) this->nextCode = 0;
	else this->fileHandler.read((void*)&this->nextCode, sizeof(this->nextCode));

	while(!this->fileHandler.isEOF()) {
		unsigned int code, clientCode, roomNumber;
		time_t checkInDate, checkOutDate;

		this->fileHandler.read((void*)&code		   , sizeof(code));
		this->fileHandler.read((void*)&checkInDate , sizeof(checkInDate));
		this->fileHandler.read((void*)&checkOutDate, sizeof(checkOutDate));
		this->fileHandler.read((void*)&clientCode  , sizeof(clientCode));
		this->fileHandler.read((void*)&roomNumber  , sizeof(roomNumber));

		try {
			this->_loadEstadia(code, checkInDate, checkOutDate, clientCode, roomNumber);
		} catch(std::runtime_error &err) {
			std::cout << err.what() << std::endl;
		}
	}
	this->fileHandler.close();
}

/*
 * Desconstrutor da classe Estadias que salva no arquivo os dados de `estadias`.
 *
 * Formato: '$code$clientCode$roomNumber$checkIn$checkOut'
 */
Estadias::~Estadias() {
	this->fileHandler.clear();
	this->fileHandler.open();
	this->fileHandler.write((void*)&this->nextCode, sizeof(this->nextCode));
	for(Estadia *estadia: this -> estadias) {
		unsigned int code 		= estadia->getCodigo(),
					 clientCode = estadia->getCliente()->getCodigo(),
					 roomNumber = estadia->getQuarto()->getNumero();
		time_t checkInDate  = estadia->getCheckInDate(),
			   checkOutDate = estadia->getCheckOutDate();

		this->fileHandler.write((void*)&code		, sizeof(code));
		this->fileHandler.write((void*)&checkInDate , sizeof(checkInDate));
		this->fileHandler.write((void*)&checkOutDate, sizeof(checkOutDate));
		this->fileHandler.write((void*)&clientCode  , sizeof(clientCode));
		this->fileHandler.write((void*)&roomNumber  , sizeof(roomNumber));
		delete estadia;
	}
	this->fileHandler.close();
}

/*
 * Faz a verificação se a `novaEstadia` é possível, ou seja,
 * checa se entra em conflito com alguma outra estadia registrada.
 * 
 * @param Estadia *novaEstadia
 * 
 * @return `true` ou `false` com base na verificação
 */
const bool Estadias::_checkEstadia(Estadia *novaEstadia) {
	const int roomNumber = novaEstadia -> getQuarto() -> getNumero();
	for(const Estadia *estadia: this -> estadias) {
		if(estadia -> getQuarto() -> getNumero() != roomNumber) continue;

		if(!((estadia -> getCheckOutDate() < novaEstadia -> getCheckInDate()) ||
			  novaEstadia -> getCheckOutDate() < estadia -> getCheckInDate())) return false;
	}

	return true;
}

/*
 * Da baixa na `estadia` passada e realiza as operações necessárias:
 *  - soma os pontos ao cliente; e
 *  - altera o status do quarto quando a baixa é
 *    realizada entre [checkIn, checkOut] da estadia.
 * 
 * @param Estadia *estadia
 * 
 * @return o preço a ser cobrado pela estadia. 
 */
float Estadias::_darBaixa(Estadia *estadia) {
	time_t current_tm = getCurrentTimestamp();
	if (current_tm >= estadia -> getCheckInDate() && 
		current_tm <= estadia -> getCheckOutDate() + 10 * 60 * 60)
		quartosHandler -> setStatus(estadia -> getQuarto(), false);
	pessoasHandler -> addPontos(estadia -> getCliente(), estadia -> getDiarias());
	return estadia -> getQuarto() -> getDiaria() * estadia -> getDiarias();
}

/*
 * Retorna a estádia com o código `code` ou nullptr caso não seja encontrada
 * 
 * @param unsigned int code
 * 
 * @reutrn Estadia
 */
Estadia *Estadias::_getEstadia(unsigned int code) {
	for(Estadia *estadia: this -> estadias) {
		if(estadia -> getCodigo() == code) return estadia;
	}
	return nullptr;
}

/*
 * Carrega um objeto estadia no vetor `estadias` com base nos dados passados.
 * Somente utilizado para carregar os dados lidos do arquivo.
 * 
 * @param unsigned int code
 * @param time_t	   checkInDate
 * @param time_t	   checkOutData
 * @param unsigned int clientCode
 * @param unsigned int roomNumber
 */
Estadia *Estadias::_loadEstadia(
	unsigned int code,
	time_t checkInDate,
	time_t checkOutDate,
	unsigned int clientCode,
	unsigned int roomNumber
) {
	Estadia *estadia = new Estadia(code, checkInDate, checkOutDate, clientCode, roomNumber);
	this -> estadias.push_back(estadia);
	return estadia;
}

/*
 * Retorna quantas estadias estão no vetor `estadias`
 *
 * @return const size_t
 */
const size_t Estadias::getTotal() const { return this->estadias.size(); }

/*
 * Tenta realizar o agendamento de uma estadia com os dados passados,
 * o código atribuído é trackeado pelo atributo `nextCode`, que soma
 * a cada agendamento.
 * 
 * A data de entrada precisa ser pelo menos o dia atual.
 * O período da estadia não pode entrar em conflito com nenhuma outra.
 * 
 * @param std::string dataEntrada
 * @param std::string dataSaida
 * @param int 		  codigoCliente
 * @param int		  numeroDoQuarto
 * 
 * @throw std::runtime_error
 * 
 * @return const *Estadia
 */
const Estadia* Estadias::agendarEstadia(
	std::string dataEntrada,
	std::string dataSaida,
	int codigoCliente,
	int numeroDoQuarto) {
	time_t current_tm = getCurrentTimestamp();
	Estadia *estadia = new Estadia(this -> nextCode, dataEntrada, dataSaida, codigoCliente, numeroDoQuarto);
	if(current_tm >= estadia -> getCheckInDate() + 10 * 60 * 60) {
		delete estadia;
		throw std::runtime_error("A data de entrada precisa ser pelo menos o dia atual");
	}

	if(!this -> _checkEstadia(estadia)) {
		delete estadia;
		throw std::runtime_error("Alguma estádia já agendada conflita com a nova estádia.");
	}
	
	if (estadia -> getCheckInDate()  <= current_tm &&
		estadia -> getCheckOutDate() >= current_tm)
		quartosHandler -> setStatus(numeroDoQuarto, true);
	this -> estadias.push_back(estadia);
	this -> nextCode++;
	return estadia;
}

/*
 * Acesso público ao método interno `_darBaixa()`.
 * Caso a estádia não seja encontrada um erro é lançado.
 * 
 * @throw std::runtime_error
 * 
 * @return float
 */
float Estadias::darBaixa(unsigned int code) {
	Estadia *estadia = this -> _getEstadia(code);
	if(estadia == nullptr) throw std::runtime_error("Estadia não encontrada");
	return this -> _darBaixa(estadia);
}

/*
 * Acesso público ao método interno _getEstadia.
 *
 * @param unsigned int code
 * 
 * @return const *Estadia
 */
const Estadia* Estadias::getEstadia(unsigned int code) {
	return this->_getEstadia(code);
}

/*
 * Retorna todas as estadias em que a `date` esteja incluída, ou seja,
 * todas as estadias que possuem `date` no seu range [checkIn, checkOut].
 *
 * @param std::string date
 * 
 * @return const std::vector<Estadia*>
 */
const std::vector<Estadia*> Estadias::getEstadia(std::string date) {
	std::vector<Estadia*> result({});
	time_t dateTM = parseDate(date);
	for(Estadia *estadia: this->estadias) {
		if(estadia->getCheckInDate() <= dateTM && dateTM <= estadia->getCheckOutDate())
			result.push_back(estadia);
	}
	return result;
}

/*
 * Retorna todas as estádias do cliente obtido pelo código `clientCode`.
 * Caso nenhuma seja encontrada, o vetor é retornado vazio.
 *
 * @param unsigned int clientCode
 * 
 * @return const std::vector<Estadia*>
 */
const std::vector<Estadia*> Estadias::getEstadias(unsigned int clientCode) {
	std::vector<Estadia*> result;
	for (Estadia* estadia : this->estadias) {
		if (estadia->getCliente()->getCodigo() == clientCode) {
			result.push_back(estadia);
		}
	}
	return result;
}

/*
 * Retorna todas as estadias de todos os clientes dos códigos `codes`.
 *
 * @param std::vector<unsigned int> codes
 * 
 * @return const std::vector<Estadia*>
 */
const std::vector<Estadia*> Estadias::getEstadias(std::vector<unsigned int> codes) {
	std::vector<Estadia*> result;
	for(unsigned int code: codes) {
		std::vector<Estadia*> estadias = this->getEstadias(code);
		for(Estadia* estadia: estadias) result.push_back(estadia);
	}
	return result;
}

/*
 * Retorna todas as estadias do quarto de número `roomNumber`.
 * 
 * @param unsigned int roomNumber
 * 
 * @return const std::vector<Estadia*>
 */
const std::vector<Estadia*> Estadias::getEstadiasByRoom(unsigned int roomNumber) {
	std::vector<Estadia*> result;
	for (Estadia* estadia : estadias) {
		if (estadia->getQuarto()->getNumero() == roomNumber) {
			result.push_back(estadia);
		}
	}
	return result;
}

/*
 * Verifica se o quarto de número `roomNumber` está disponível para estadia,
 * no range [checkIn, checkOut]
 * 
 * @param unsigned int roomNumber
 * @param time_t	   checkIn
 * @param time_t	   checkOut
 */
const bool Estadias::isAvaliable(unsigned int roomNumber, time_t checkIn, time_t checkOut) {
	const std::vector<Estadia*> estadias = this->getEstadiasByRoom(roomNumber);
	for(Estadia *estadia: estadias) {
		if(!((estadia -> getCheckOutDate() < checkIn) ||
			  checkOut < estadia -> getCheckInDate())) return false;
	}
	return true;
}