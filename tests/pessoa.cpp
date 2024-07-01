#include <catch2/catch_test_macros.hpp>
#include "../src/pessoa.hpp"
#include "handlers.hpp"

TEST_CASE("Teste básico da Classe Pessoa", "[Pessoa]") {
    {
        Pessoa pessoa(1, "123456789", "Joao da Silva");

        CHECK(pessoa.getCodigo() == 1);
        CHECK(pessoa.getTelefone() == "123456789");
        CHECK(pessoa.getNome() == "Joao da Silva");
    }

    {
        Pessoa pessoa(2, "987654321", "Maria de Souza");

        CHECK(pessoa.getCodigo() == 2);
        CHECK(pessoa.getTelefone() == "987654321");
        CHECK(pessoa.getNome() == "Maria de Souza");
    }

    {
        Pessoa pessoa(3, "", "Ana Clara");

        CHECK(pessoa.getCodigo() == 3);
        CHECK(pessoa.getTelefone() == "");
        CHECK(pessoa.getNome() == "Ana Clara");
    }

    {
        Pessoa pessoa(4, "555555555", "Pedro Alves");

        CHECK(pessoa.getCodigo() == 4);
        CHECK(pessoa.getTelefone() == "555555555");
        CHECK(pessoa.getNome() == "Pedro Alves");
    }

    {
        Pessoa pessoa_invalida(0, "12345", "");

        CHECK(pessoa_invalida.getCodigo() == 0);
        CHECK(pessoa_invalida.getTelefone() == "12345");
        CHECK(pessoa_invalida.getNome() == "");
    }

    {
        CHECK_NOTHROW(Pessoa(5, "111222333", "Carlos Oliveira"));
        CHECK_NOTHROW(Pessoa(6, "222333444", "Elisa Mendes"));
    }
}

TEST_CASE("Teste básico da Classe Pessoas") {
    unsigned int total         = pessoasHandler->getTotal(),
                 totalClients  = pessoasHandler->getTotalClients(),
                 totalEmployes = pessoasHandler->getTotalEmployess();

    SECTION("Começo") {
        CHECK(total         == 14);
        CHECK(totalClients  == 12);
        CHECK(totalEmployes == 2);
    }

    SECTION("Pessoas::cadastroCliente") {
        CHECK_NOTHROW(pessoasHandler->cadastrarCliente("12345678", "Maria Ana 1", "R. Um, 123"  , 0));
        CHECK_NOTHROW(pessoasHandler->cadastrarCliente("23456789", "Maria Ana 2", "R. Dois, 234", 0));
        CHECK_THROWS(pessoasHandler->cadastrarCliente("123456789", "Maria Ana 3", "", 0));
    }

    SECTION("Pessoas::getTotal*") {
        CHECK(total         == pessoasHandler->getTotal());
        CHECK(totalClients  == pessoasHandler->getTotalClients());
        CHECK(totalEmployes == pessoasHandler->getTotalEmployess());
    }

    SECTION("Pessoas::cadastroFuncionario") {
        CHECK_NOTHROW(pessoasHandler->cadastrarFuncionaro("87654321", "Funcionario do Hotel 1", "Gerente"      , 2500));
        CHECK_NOTHROW(pessoasHandler->cadastrarFuncionaro("87654321", "Funcionario do Hotel 2", "Recepcionista", 1200));
        CHECK_THROWS(pessoasHandler->cadastrarFuncionaro("87654321", "Funcionario do Hotel 3", "Recepcionista", -1200));
    }

    SECTION("Pessoas::getTotal*") {
        CHECK(total         == pessoasHandler->getTotal());
        CHECK(totalClients  == pessoasHandler->getTotalClients());
        CHECK(totalEmployes == pessoasHandler->getTotalEmployess());
    }

    SECTION("Pessoas::get* by name") {
        CHECK(pessoasHandler->getCliente("maria ana").size() == 2);
        CHECK(pessoasHandler->getFuncionario("funcionario do hotel").size() == 2);
        CHECK(pessoasHandler->getPessoa("").size() == total);
    }
}