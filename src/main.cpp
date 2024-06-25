#include <iostream>
#include <cstdlib>
#include <string>

#include "global.hpp"

void Menu()
{
	bool clienteCadastrado = false;
	bool quartoCadastrado = false;

	int result = 0;
	while (result != 6)
	{

		std::cout << "Escolha a opção desejada conforme indicado no menu a seguir: " << std::endl
				  << "1 - Cadastrar um cliente.\n2 - Cadastrar um quarto.\n3 - Cadastrar um funcionário.\n4 - Cadastrar uma estadia.\n5 - Pesquisar um cliente/funcionário\n6 - Sair do menu." << std::endl;
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

			const Cliente *cliente = pessoasHandler->cadastrarCliente(cellPhone, name, address, points);
			cliente->getCodigo();

			std::cout << std::endl;

			std::cout << "Cliente cadastrado com sucesso! Seja bem vindo(a) Sr(a). " << name << " ao Hotel Descanso Garantido, aqui o seu descanso é garantido ou seu dinheiro de volta. O seu código de cadastro é : " << cliente->getCodigo() << std::endl;

			clienteCadastrado = true;

			break;
		}
		case 2:
		{
			unsigned int number = 0;
			float dailyValue = 750.0;

			std::cout << "Para todas as diárias, o valor é de R$750,00. Informe o número do quarto desejado: " << std::endl;
			std::cin >> number;

			quartosHandler->criarQuarto(number, dailyValue);

			quartoCadastrado = true;

			break;
		}
		case 3:
		{
			unsigned int cellPhone = 0;
			std::string name = "";
			std::string cargo = "";
			float wage = 0.0;

			std::cout << "Informe o nome do funcionário " << std::endl;
			std::getline(std::cin, name);

			std::cout << "Informe o cargo do funcionário " << std::endl;
			std::getline(std::cin, cargo);

			std::cout << "Informe o salário do funcionário " << std::endl;
			std::cin >> wage;

			std::cout << "Informe o número de telefone do funcionário " << std::endl;
			std::cin >> cellPhone;

			pessoasHandler->cadastrarFuncionaro(cellPhone, name, cargo, wage);

			std::cout << "Funcionário cadastrado com sucesso ! Seja bem vindo Sr(a) " << name << " ao seu novo ambiente de trabalho. " << std::endl;

			break;
		}
		case 4:
		{
			if (quartoCadastrado == true && clienteCadastrado == true)
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
			else
			{
				std::cout << "Para cadastrar uma estadia primeiro é necessário que o quarto e o cliente estejam cadastrados." << std::endl;
			}

			break;
		}
		case 5:
		{
			int searchOption = 0;
			std::cout << "Escolha o método de pesquisa: \n1 - Pesquisar por nome\n2 - Pesquisar por código\n";
			std::cin >> searchOption;
			std::cin.ignore(); // Limpa o buffer

			if (searchOption == 1)
			{
				std::string nome;
				std::cout << "Digite o nome da pessoa que deseja pesquisar: " << std::endl;
				std::getline(std::cin, nome);

				std::vector<Pessoa *> pessoasEncontradas = pessoasHandler->pesquisarPessoaPorNome(nome);

				if (pessoasEncontradas.empty())
				{
					std::cout << "Nenhuma pessoa encontrada com o nome " << nome << "." << std::endl;
				}
				else
				{
					for (Pessoa *pessoa : pessoasEncontradas)
					{
						Cliente *cliente = dynamic_cast<Cliente *>(pessoa);
						Funcionario *funcionario = dynamic_cast<Funcionario *>(pessoa);

						if (cliente)
						{
							std::cout << "Cliente encontrado: " << std::endl;
							std::cout << "Código: " << cliente->getCodigo() << std::endl;
							std::cout << "Nome: " << cliente->getNome() << std::endl;
							std::cout << "Telefone: " << cliente->getTelefone() << std::endl;
							std::cout << "Endereço: " << cliente->getEndereco() << std::endl;
							std::cout << "Pontos: " << cliente->getPontos() << std::endl;
						}
						else if (funcionario)
						{
							std::cout << "Funcionário encontrado: " << std::endl;
							std::cout << "Código: " << funcionario->getCodigo() << std::endl;
							std::cout << "Nome: " << funcionario->getNome() << std::endl;
							std::cout << "Telefone: " << funcionario->getTelefone() << std::endl;
							std::cout << "Cargo: " << funcionario->getCargo() << std::endl;
							std::cout << "Salário: " << funcionario->getSalario() << std::endl;
						}
					}
				}
			}
			else if (searchOption == 2)
			{
				unsigned int codigo;
				std::cout << "Digite o código da pessoa que deseja pesquisar: " << std::endl;
				std::cin >> codigo;

				Pessoa *pessoaEncontrada = pessoasHandler->pesquisarPessoaPorCodigo(codigo);

				if (!pessoaEncontrada)
				{
					std::cout << "Nenhuma pessoa encontrada com o código " << codigo << "." << std::endl;
				}
				else
				{
					Cliente *cliente = dynamic_cast<Cliente *>(pessoaEncontrada);
					Funcionario *funcionario = dynamic_cast<Funcionario *>(pessoaEncontrada);

					if (cliente)
					{
						std::cout << "Cliente encontrado: " << std::endl;
						std::cout << "Código: " << cliente->getCodigo() << std::endl;
						std::cout << "Nome: " << cliente->getNome() << std::endl;
						std::cout << "Telefone: " << cliente->getTelefone() << std::endl;
						std::cout << "Endereço: " << cliente->getEndereco() << std::endl;
						std::cout << "Pontos: " << cliente->getPontos() << std::endl;
					}
					else if (funcionario)
					{
						std::cout << "Funcionário encontrado: " << std::endl;
						std::cout << "Código: " << funcionario->getCodigo() << std::endl;
						std::cout << "Nome: " << funcionario->getNome() << std::endl;
						std::cout << "Telefone: " << funcionario->getTelefone() << std::endl;
						std::cout << "Cargo: " << funcionario->getCargo() << std::endl;
						std::cout << "Salário: " << funcionario->getSalario() << std::endl;
					}
				}
			}
			else
			{
				std::cout << "Opção inválida. Tente novamente." << std::endl;
			}

			break;
		}
		case 6:
			std::cout << "Muito obrigado pela preferência, volte sempre!" << std::endl;
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