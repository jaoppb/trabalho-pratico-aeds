#include <iostream>
#include <cstdlib>
#include <string>

#include "global.hpp"
#include "utils.hpp"

bool registerClient() {
	std::string name = "";
	std::string address = "";
	std::string cellPhone = "";
	unsigned int points = 0;

	std::cout << "\nInforme seu nome: " << std::endl;
	std::getline(std::cin, name);

	std::cout << "\nInforme seu endereço: " << std::endl;
	std::getline(std::cin, address);

	std::cout << "\nInforme seu número de telefone: " << std::endl;
	std::cin >> cellPhone;

	try {
		const Cliente *cliente = pessoasHandler->cadastrarCliente(cellPhone, name, address, points);
		cliente->getCodigo();

		std::cout << std::endl;

		std::cout << "\nCliente cadastrado com sucesso! Seja bem vindo(a) Sr(a). " << name << " ao Hotel Descanso Garantido, aqui o seu descanso é garantido ou seu dinheiro de volta. O seu código de cadastro é : " << cliente->getCodigo() << "\n" << std::endl;

		return true;
	} catch (std::runtime_error &err) {
		std::cout << err.what() << std::endl;
	}
	return false;
}

bool registerRoom() {
	unsigned int number = 0, guests = 1;
	float dailyValue = 0;

	std::cout << "Informe o número do quarto desejado:" << std::endl;
	std::cin >> number;

	std::cout << "Informe o valor da diária(separe decimal com utilizando .):" << std::endl;
	std::cin >> dailyValue;

	std::cout << "Insira a capacidade do quarto:" << std::endl;
	std::cin >> guests;

	try {
		quartosHandler->criarQuarto(number, dailyValue, guests);

		std::cout << "Quarto " << number << " cadastrado com sucesso.\n";

		return true;
	} catch (std::runtime_error &err) {
		std::cout << err.what() << std::endl;
	}
	return false;
}

bool registerEmploye() {
	std::string cellPhone = "";

	std::string name = "";
	std::string cargo = "";
	float wage = 0.0;

	std::cout << "\nInforme o nome do funcionário " << std::endl;
	std::getline(std::cin, name);

	std::cout << "\nInforme o cargo do funcionário " << std::endl;
	std::getline(std::cin, cargo);

	std::cout << "\nInforme o salário do funcionário " << std::endl;
	std::cin >> wage;

	std::cout << "\nInforme o número de telefone do funcionário " << std::endl;
	std::cin >> cellPhone;

	try {
		pessoasHandler->cadastrarFuncionaro(cellPhone, name, cargo, wage);

		std::cout << "\nFuncionário cadastrado com sucesso ! Seja bem vindo Sr(a) " << name << " ao seu novo ambiente de trabalho. \n" << std::endl;

		return true;
	} catch (std::runtime_error &err) {
		std::cout << err.what();
	}
	return false;
}

bool scheduleEstadia() {
	std::string entryDate;
	std::string exitDate;
	unsigned int guests,
		 		 clientCode,
				 numberRoom;

	std::cout << "\nPara o cadastro de uma estadia, por favor digite a data de entrada desejada no formato (dd/mm/aaaa) " << std::endl;
	std::cin >> entryDate;

	std::cout << "\nDigite a data de saída também no mesmo formato" << std::endl;
	std::cin >> exitDate;

	std::cout << "\nInforme o código do cliente " << std::endl;
	std::cin >> clientCode;

	std::cout << "\nInforme a quantidade de hospedes:" << std::endl;
	std::cin >> guests;

	const std::vector<Quarto*> quartos = quartosHandler->getRoomsByCapacity(guests);
	if(quartos.empty()) {
		std::cout << "\nNenhum quarto disponível com essa capacidade disponível.";
		return false;
	}

	bool one = false;
	for(Quarto *quarto: quartos) {
		if(!estadiasHandler->isAvaliable(quarto->getNumero(), parseDate(entryDate), parseDate(exitDate))) continue;
		std::cout << "Quarto N°" 	   << quarto->getNumero() << std::endl
				  << " - Capacidade: " << quarto->getQuantidadeDeHospedes() << std::endl
				  << " - Diaria: " 	   << quarto->getDiaria() << std::endl << std::endl;
		one = true;
	}
	if(!one) {
		std::cout << "\nNenhum quarto disponível nessa data com essa capacidade.";
		return false;
	}

	std::cout << "\nInforme o quarto do cliente " << std::endl;
	std::cin >> numberRoom;

	try
	{
		const Estadia *estadia = estadiasHandler->agendarEstadia(entryDate, exitDate, clientCode, numberRoom);
		estadia->getCodigo();

		std::cout << "\nEstadia cadastrada com sucesso! Aproveite seus dias de descanso no melhor hotel para um bom relaxamento de qualidade da cidade! O seu código de estadia é: " << estadia->getCodigo() << std::endl;
		return true;
	} catch (std::runtime_error &err) {
		std::cout << err.what() << std::endl;
	}
	return false;
}

void searchEstadias() {
	int searchOption = 0;
	while (searchOption < 1 || searchOption > 3) {
		std::cout << "\nEscolha o método de pesquisa de estadias: \n"
							<< "1 - Pesquisar por código do cliente\n"
							<< "2 - Pesquisar por número do quarto\n"
							<< "3 - Sair das pesquisas\n";
		std::cin >> searchOption;
	}
	std::cin.ignore();

	if (searchOption == 1) {
		unsigned int clientCode;
		std::cout << "\nDigite o código do cliente: " << std::endl;
		std::cin >> clientCode;

		try {
			std::vector<Estadia*> estadias = estadiasHandler->getEstadias(clientCode);

			if (estadias.empty()) {
				std::cout << "\nNenhuma estadia encontrada para o cliente com código " << clientCode << ".\n" << std::endl;
			} else {
				for (Estadia* estadia : estadias) {
					int checkIn[6], checkOut[6];
					handleTimestamp(checkIn , estadia->getCheckInDate ());
					handleTimestamp(checkOut, estadia->getCheckOutDate());
					std::cout << "\nEstadia encontrada: \n";
					std::cout << " - Código: " << estadia->getCodigo() << std::endl;
					std::cout << " - Data de Entrada: " << checkIn[2] << "/" << checkIn[1] << "/" << checkIn[0] << std::endl;
					std::cout << " - Data de Saída: " << checkOut[2] << "/" << checkOut[1] << "/" << checkOut[0] << std::endl;
					std::cout << " - Código do Cliente: " << estadia->getCliente()->getCodigo() << std::endl;
					std::cout << " - Número do Quarto: " << estadia->getQuarto()->getNumero() << std::endl;
				}
			}
		} catch (std::runtime_error &err) {
			std::cout << err.what() << std::endl;
		}
	} else if (searchOption == 2) {
		unsigned int roomNumber;
		std::cout << "\nDigite o número do quarto: " << std::endl;
		std::cin >> roomNumber;

		try {
			std::vector<Estadia*> estadias = estadiasHandler->getEstadiasByRoom(roomNumber);

			if (estadias.empty()) {
				std::cout << "\nNenhuma estadia encontrada para o quarto com número " << roomNumber << ".\n" << std::endl;
			} else {
				for (Estadia* estadia : estadias) {
					int checkIn[6], checkOut[6];
					handleTimestamp(checkIn , estadia->getCheckInDate ());
					handleTimestamp(checkOut, estadia->getCheckOutDate());
					std::cout << "\nEstadia encontrada: \n";
					std::cout << " - Código: " << estadia->getCodigo() << std::endl;
					std::cout << " - Data de Entrada: " << checkIn[2] << "/" << checkIn[1] << "/" << checkIn[0] << std::endl;
					std::cout << " - Data de Saída: " << checkOut[2] << "/" << checkOut[1] << "/" << checkOut[0] << std::endl;
					std::cout << " - Código do Cliente: " << estadia->getCliente()->getCodigo() << std::endl;
					std::cout << " - Número do Quarto: " << estadia->getQuarto()->getNumero() << std::endl;
				}
			}
		} catch (std::runtime_error &err) {
			std::cout << err.what() << std::endl;
		}
	} else if (searchOption != 3) {
		std::cout << "\nOpção inválida. Voltando ao menu principal.\n";
	}
}

void searchPessoas() {
	int searchOption = 0;
	while (searchOption < 1 || searchOption > 3) {
		std::cout << "\nEscolha o método de pesquisa: \n"
					<< "1 - Pesquisar por nome\n"
					<< "2 - Pesquisar por código\n"
					<< "3 - Sair das pesquisas\n";
		std::cin >> searchOption;
	}
	std::cin.ignore();

	if (searchOption == 1) {
		std::string nome;
		std::cout << "\nDigite o nome da pessoa que deseja pesquisar: " << std::endl;
		std::getline(std::cin, nome);

		std::vector<Pessoa *> pessoasEncontradas = pessoasHandler->getPessoa(nome);

		if (pessoasEncontradas.empty()) {
			std::cout << "\nNenhuma pessoa com o nome " << nome << " encontrada.\n" << std::endl;
		} else {
			for (Pessoa *pessoa : pessoasEncontradas) {
				Cliente *cliente = dynamic_cast<Cliente *>(pessoa);
				Funcionario *funcionario = dynamic_cast<Funcionario *>(pessoa);

				if (cliente) {
					std::cout << "\nCliente encontrado: \n" << std::endl;
					std::cout << " - Código: " << cliente->getCodigo() << std::endl;
					std::cout << " - Nome: " << cliente->getNome() << std::endl;
					std::cout << " - Telefone: " << cliente->getTelefone() << std::endl;
					std::cout << " - Endereço: " << cliente->getEndereco() << std::endl;
					std::cout << " - Pontos: " << cliente->getPontos() << std::endl;
				} else if (funcionario) {
					std::cout << "\nFuncionário encontrado: " << std::endl;
					std::cout << " - Código: " << funcionario->getCodigo() << std::endl;
					std::cout << " - Nome: " << funcionario->getNome() << std::endl;
					std::cout << " - Telefone: " << funcionario->getTelefone() << std::endl;
					std::cout << " - Cargo: " << funcionario->getCargo() << std::endl;
					std::cout << " - Salário: " << funcionario->getSalario() << std::endl;
				}
			}
		}
	} else if (searchOption == 2) {
		unsigned int codigo;
		std::cout << "\nDigite o código da pessoa que deseja pesquisar: " << std::endl;
		std::cin >> codigo;

		const Pessoa *pessoaEncontrada = pessoasHandler->getPessoa(codigo);

		if (!pessoaEncontrada) {
			std::cout << "\nNenhuma pessoa encontrada com o código " << codigo << "." << std::endl;
		} else {
			const Cliente *cliente = dynamic_cast<const Cliente *>(pessoaEncontrada);
			const Funcionario *funcionario = dynamic_cast<const Funcionario *>(pessoaEncontrada);

			if (cliente) {
				std::cout << "\nCliente encontrado: " << std::endl;
				std::cout << "Código: " << cliente->getCodigo() << std::endl;
				std::cout << "Nome: " << cliente->getNome() << std::endl;
				std::cout << "Telefone: " << cliente->getTelefone() << std::endl;
				std::cout << "Endereço: " << cliente->getEndereco() << std::endl;
				std::cout << "Pontos: " << cliente->getPontos() << std::endl;
			} else if (funcionario) {
				std::cout << "Funcionário encontrado: " << std::endl;
				std::cout << "Código: " << funcionario->getCodigo() << std::endl;
				std::cout << "Nome: " << funcionario->getNome() << std::endl;
				std::cout << "Telefone: " << funcionario->getTelefone() << std::endl;
				std::cout << "Cargo: " << funcionario->getCargo() << std::endl;
				std::cout << "Salário: " << funcionario->getSalario() << std::endl;
			}
		}
	} else if (searchOption != 3) {
		std::cout << "\nOpção inválida. Voltando ao menu principal.\n";
	}
}
void checkOutStay(){
	unsigned int codeStay;
	std::cout << "\nInforme o código da estadia à dar baixa: " << std::endl;
	std::cin >> codeStay;
	try {
		float value = estadiasHandler->darBaixa(codeStay);
		std::cout << "\nBaixa de R$ " << value << " realizada com sucesso!\n" << std::endl;
	} catch(std::runtime_error &err) {
		std::cout << err.what();	
	}
}

void menu() {
	bool clientRegistered = pessoasHandler->getTotalClients() > 0;
	bool roomRegistered = quartosHandler->getTotal() > 0;
	bool employeeRegistered = pessoasHandler->getTotalEmployess() > 0;
	bool stayRegistered = estadiasHandler->getTotal() > 0;

	int result = -1;
	while (result != 0) {
		std::cout << "\nEscolha a opção desejada conforme indicado no menu a seguir: \n" << std::endl
				  << "1 - Cadastrar um cliente.\n"
				  << "2 - Cadastrar um quarto.\n"
				  << "3 - Cadastrar um funcionário.\n"
				  << "4 - Cadastrar uma estadia.\n"
				  << "5 - Pesquisar um cliente/funcionário\n"
				  << "6 - Pesquisar estadias\n"
				  << "7 - Dar baixa em uma estadia\n"
				  << "0 - Sair do menu.\n" << std::endl;
		std::cin >> result;
		std::cin.ignore();

		switch (result) {
		case 1:
			if(registerClient()) clientRegistered = true;
			break;
		case 2:
			if(registerRoom()) roomRegistered = true;
			break;
		case 3:
			if(registerEmploye()) employeeRegistered = true;
			break;
		case 4:
			if (roomRegistered == true && clientRegistered == true && scheduleEstadia()) stayRegistered = true;
			else std::cout << "\nPara cadastrar uma estadia primeiro é necessário que um quarto e um cliente estejam cadastrados.\n" << std::endl;
			break;
		case 5:
			if (employeeRegistered == true || clientRegistered == true) {
				searchPessoas();
			}else{
				std::cout << "Para pesquisar por um funcionário ou cliente, primeiro é necessário que um ao menos um dos dois estejam cadastrados.\n" << std::endl;
			}
			break;
		case 6:
			if(stayRegistered == true) searchEstadias();
			else std::cout << "\nPara pesquisar uma estadia é necessário que pelo menos uma já esteja cadastrada.\n" << std::endl;
			break;
		case 7:
			if(stayRegistered == true) checkOutStay();
			else std::cout << "\nPara dar baixa em uma estadia é necessário que pelo menos uma já esteja cadastrada.\n" << std::endl;
			break;
		case 0:
			std::cout << "Muito obrigado pela preferência, volte sempre!" << std::endl;
			break;
		default:
			std::cout << "Opção inválida, digite novamente." << std::endl;
			break;
		}
		if (result != 0) result = -1;
	}
}

int main() {
	menu();

	delete estadiasHandler;
	delete pessoasHandler;
	delete quartosHandler;

	return 0;
}