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

        CHECK_THROWS_AS(Pessoa(0, "", ""), std::invalid_argument);
        CHECK_THROWS_AS(Pessoa(0, "000000000", ""), std::invalid_argument);
    }
}