#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

#include "handlers.hpp"
#include "../src/cliente.hpp"
#include "../src/funcionario.hpp"
#include "../src/quarto.hpp"

TEST_CASE("Cadastro de Cliente", "[Menu]") {
		std::string nome = "João Silva";
		std::string endereco = "Rua das Flores, 123";
		std::string telefone = "999999999";
		unsigned int pontos = 0;

		const Cliente* cliente = pessoasHandler->cadastrarCliente(telefone, nome, endereco, pontos);

		REQUIRE(cliente != nullptr);
		CHECK(cliente->getNome() == nome);
		CHECK(cliente->getEndereco() == endereco);
		CHECK(cliente->getTelefone() == telefone);
		CHECK(cliente->getPontos() == pontos);
}

TEST_CASE("Cadastro de Quarto", "[Menu]") {
		unsigned int numeroQuarto = 101;
		float diaria = 750.0f;
		unsigned int capacidade = 2;

		const Quarto* quarto = quartosHandler->criarQuarto(numeroQuarto, diaria, capacidade);

		REQUIRE(quarto != nullptr);
		CHECK(quarto->getNumero() == numeroQuarto);
		CHECK(quarto->getDiaria() == diaria);
}

TEST_CASE("Cadastro de Funcionário", "[Menu]") {
		std::string nome = "Ana Souza";
		std::string cargo = "Recepcionista";
		float salario = 3000.0f;
		std::string telefone = "888888888";

		const Funcionario* funcionario = pessoasHandler->cadastrarFuncionaro(telefone, nome, cargo, salario);

		REQUIRE(funcionario != nullptr);
		CHECK(funcionario->getNome() == nome);
		CHECK(funcionario->getCargo() == cargo);
		CHECK(funcionario->getSalario() == salario);
		CHECK(funcionario->getTelefone() == telefone);
		CHECK(funcionario->getCodigo() > 0); 
}

TEST_CASE("Cadastro de Estadia", "[Menu]") {
		std::string dataEntrada = "10/10/2024";
		std::string dataSaida = "17/10/2024";
		int codigoCliente = 0;
		int numeroQuarto = 101;

		CHECK_NOTHROW(estadiasHandler->agendarEstadia(dataEntrada, dataSaida, codigoCliente, numeroQuarto));
}

TEST_CASE("Pesquisa de Cliente por Nome", "[Menu]") {
		std::string nomePesquisa = "João Silva";

		std::vector<Pessoa*> resultados = pessoasHandler->getPessoa(nomePesquisa);

		REQUIRE(!resultados.empty());
		const Cliente* clienteEncontrado = dynamic_cast<const Cliente*>(resultados.front());
		REQUIRE(clienteEncontrado != nullptr);
		CHECK(clienteEncontrado->getNome() == nomePesquisa);
}

TEST_CASE("Pesquisa de Cliente por Código", "[Menu]") {
		unsigned int codigoPesquisa = 0;

		const Pessoa* resultado = pessoasHandler->getCliente(codigoPesquisa);

		REQUIRE(resultado != nullptr);
		CHECK(resultado->getCodigo() == codigoPesquisa);
}

TEST_CASE("Cadastro e Pesquisa de Funcionario por Nome", "[Menu]") {
		std::string nome = "Carlos Pereira";
		std::string cargo = "Gerente";
		float salario = 4500.0f;
		std::string telefone = "777777777";

		const Funcionario* funcionario = pessoasHandler->cadastrarFuncionaro(telefone, nome, cargo, salario);

		REQUIRE(funcionario != nullptr);

		std::vector<Pessoa*> resultados = pessoasHandler->getPessoa(nome);

		REQUIRE(!resultados.empty());
		Funcionario* funcionarioEncontrado = dynamic_cast<Funcionario*>(resultados.front());
		REQUIRE(funcionarioEncontrado != nullptr);
		CHECK(funcionarioEncontrado->getNome() == nome);
		CHECK(funcionarioEncontrado->getCargo() == cargo);
		CHECK(funcionarioEncontrado->getSalario() == salario);
}

TEST_CASE("Cadastro e Pesquisa de Quarto por Número", "[Menu]") {
		unsigned int numeroQuarto = 202;
		float diaria = 850.0f;
		unsigned int capacidade = 3;

		const Quarto* quarto = quartosHandler->criarQuarto(numeroQuarto, diaria, capacidade);

		REQUIRE(quarto != nullptr);

		const Quarto* quartoEncontrado = quartosHandler->getQuarto(numeroQuarto);
		REQUIRE(quartoEncontrado != nullptr);
		CHECK(quartoEncontrado->getNumero() == numeroQuarto);
		CHECK(quartoEncontrado->getDiaria() == diaria);
}