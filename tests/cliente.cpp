#include <catch2/catch_test_macros.hpp>
#include "../src/cliente.hpp"
#include "../src/pessoa.hpp"

TEST_CASE("Teste básico da Classe Cliente", "Exceptions da Classe Cliente") {
    SECTION("Construtor e getters") {
        Cliente cliente(1, 100, "123456789", "Maria", "Rua A");

        CHECK(cliente.getCodigo() == 1);
        CHECK(cliente.getTelefone() == "123456789");
        CHECK(cliente.getNome() == "Maria");
        CHECK(cliente.getEndereco() == "Rua A");
        CHECK(cliente.getPontos() == 100);
    }

    SECTION("Setter de endereco") {
        Cliente cliente(2, 50, "987654321", "João", "Rua B");

        CHECK(cliente.getEndereco() == "Rua B");
        cliente.setEndereco("Rua C");
        CHECK(cliente.getEndereco() == "Rua C");
    }

    SECTION("Add pontos") {
        Cliente cliente(3, 200, "555555555", "Pedro", "Rua D");

        CHECK(cliente.getPontos() == 200);
        cliente.addPontos(5);
        CHECK(cliente.getPontos() == 250);
    }

    SECTION("Pontos negativos") {
        CHECK_THROWS(Cliente(4, -10, "777777777", "Ana", "Rua E"));
    }

    SECTION("Endereco vazio") {
        CHECK_THROWS(Cliente(5, 150, "999999999", "Paula", ""));
    }

    SECTION("Setter de endereco vazio") {
        Cliente cliente(6, 300, "111111111", "Carlos", "Rua F");

        CHECK(cliente.getEndereco() == "Rua F");
        CHECK_THROWS(cliente.setEndereco(""));
    }
}