#include <catch2/catch_test_macros.hpp>
#include "../cliente.hpp"

TEST_CASE("Teste básico da Classe Cliente", "[Cliente]") {
    Cliente cliente(1, 123456789, 0, "Joao da Silva", "Rua A, 123");

    {
        CHECK(cliente.getCodigo() == 1);
        CHECK(cliente.getTelefone() == 123456789);
        CHECK(cliente.getNome() == "Joao da Silva");
        CHECK(cliente.getEndereco() == "Rua A, 123");
        CHECK(cliente.getPontos() == 0);
    }

    {
        cliente.addPontos(1);
        CHECK(cliente.getPontos() == 10);

        cliente.addPontos(3);
        CHECK(cliente.getPontos() == 40);
    }

    {
        cliente.setEndereco("Rua B, 456");
        CHECK(cliente.getEndereco() == "Rua B, 456");
    }

    {

        CHECK_NOTHROW(Cliente(2, 987654321, 0, "Maria da Silva", "Rua C, 789"));
        
        Cliente cliente_invalido(3, 123456780, 0, "Pedro de Souza", "Rua D, 321");
        cliente_invalido.addPontos(2);
        CHECK(cliente_invalido.getPontos() == 20);

        CHECK_THROWS(cliente_invalido.addPontos(-5));
        CHECK_THROWS(cliente_invalido.setEndereco("")); 
        
        Cliente cliente_valido(4, 987654322, 10, "Ana Clara", "Rua E, 654");
        CHECK(cliente_valido.getCodigo() == 4);
        CHECK(cliente_valido.getTelefone() == 987654322);
        CHECK(cliente_valido.getPontos() == 10);
        CHECK(cliente_valido.getNome() == "Ana Clara");
        CHECK(cliente_valido.getEndereco() == "Rua E, 654");
    }
}