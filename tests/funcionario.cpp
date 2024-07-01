#include <catch2/catch_test_macros.hpp>
#include "../src/funcionario.hpp"
#include "../src/pessoa.hpp"

TEST_CASE("Teste básico da Classe Funcionario", "Exceptions da Classe Funcionario") {
    SECTION("Construtor e getters") {
        Funcionario funcionario(1, "123456789", "João", "Desenvolvedor", 5000.0f);

        CHECK(funcionario.getCodigo() == 1);
        CHECK(funcionario.getTelefone() == "123456789");
        CHECK(funcionario.getNome() == "João");
        CHECK(funcionario.getCargo() == "Desenvolvedor");
        CHECK(funcionario.getSalario() == 5000.0f);
    }

    SECTION("Setter de salario") {
        Funcionario funcionario(2, "987654321", "Maria", "Gerente", 7000.0f);

        CHECK(funcionario.getSalario() == 7000.0f);
        funcionario.setSalario(8000.0f);
        CHECK(funcionario.getSalario() == 8000.0f);
    }

    SECTION("Salario negativo") {
        CHECK_THROWS(Funcionario(3, "654321987", "José", "Analista", -1000.0f));
    }
}