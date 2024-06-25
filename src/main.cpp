#include <iostream>
#include <cstdlib>
#include <string>

#include "global.hpp"

void Menu()
{
	int result = 0;
	while (result != 5)
	{
		bool clienteCadastrado = false;
		bool quartoCadastrado = false;

		std::cout << "Escolha a opção desejada conforme indicado no menu a seguir: " << std::endl
				  << "1 - Cadastrar um cliente.\n2 - Cadastrar um quarto.\n3 - Cadastrar um funcionário.\n4 - Cadastrar uma estadia.\n5 - Sair do menu." << std::endl;
		std::cin >> result;
		std::cin.ignore();

		switch (result)
		{
		case 1:
		{
			std::string name = "";
			std::string address = "";
			unsigned int cellPhone = 0;
			unsigned int points = 0;

			std::cout << "Informe seu nome: " << std::endl;
			std::getline(std::cin, name);

			std::cout << "Informe seu endereço: " << std::endl;
			std::getline(std::cin, address);

			std::cout << "Informe seu número de telefone: " << std::endl;
			std::cin >> cellPhone;

			pessoasHandler->cadastrarCliente(cellPhone, name, address, points);
			
			std::cout << "Cliente cadastrado com sucesso! Seja bem vindo(a) Sr(a). " << name << "ao Hotel Descanso Garantido, aqui o seu descanso é garantido ou seu dinheiro de volta." << std::endl; 

			clienteCadastrado = true;

			break;
		}
		case 2:
		{
			unsigned int number = 0;
			float dailyValue = 750.0;

			std::cout << "Informe o número do quarto desejado: " << std::endl;
			std::cin >> number;

			quartosHandler->criarQuarto(number, dailyValue); 
			break;
		}
		case 3:
		{
			unsigned int cellPhone = 0; 
			std::string name = ""; 
			std::string cargo = ""; 
			float wage = 0.0;

			std::cout << "Informe o nome do funcionário " << std::endl;
			std::cin >> name;

			std::cout << "Informe o cargo do funcionário " << std::endl;
			std::cin >> cargo;

			std::cout << "Informe o salário do funcionário " << std::endl;
			std::cin >> wage;

			std::cout << "Informe o número de telefone do funcionário " << std::endl;
			std::cin >> cellPhone;

			pessoasHandler->cadastrarFuncionaro(cellPhone, name, cargo, wage);

			std::cout << "Funcionário cadastrado com sucesso ! Seja bem vindo Sr(a) " << name << " ao seu novo ambiente de trabalho. " << std::endl;

			quartoCadastrado = true;

			break;
		}
		case 4:
		{
			if(quartoCadastrado && clienteCadastrado)
			{
				std::string entryDate;
				std::string exitDate;
				int clientCode;
				int numberRoom;

				std::cout << "Para o cadastro de uma estadia, por favor digite a data de entrada desejada no formato (dd/mm/aaaa) " << std::endl;
				std::cin >> entryDate;

				std::cout << "Digite a data de saída " << std::endl;
				std::cin >> exitDate;

				std::cout << "Informe o código do cliente " << std::endl;
				std::cin >> clientCode;

				std::cout << "Informe o quarto do cliente " << std::endl;
				std::cin >> numberRoom;

				estadiasHandler->agendarEstadia(entryDate, exitDate, clientCode, numberRoom);

				std::cout << "Estadia cadastrada com sucesso! Aproveite seus dias de descanso no melhor hotel para um bom relaxamento de qualidade da cidade" << std::endl;
			}
			else{
				std::cout << "Para cadastrar uma estadia primeiro é necessário que o quarto e o cliente estejam cadastrados." << std::endl;
			}	

				break;
		}
		case 5:
			std::cout << "Muito obrigado pela preferência, volte sempre!" << std::endl;
			exit(0);
			break;
		default:
			std::cout << "Opção inválida, digite novamente." << std::endl;
			break;
		}
	}
}

int main()
{
	Menu();

	return 0;
}