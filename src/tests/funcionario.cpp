#include <catch2/catch_test_macros.hpp>
#include "../funcionario.hpp"
#include "../pessoa.hpp"

TEST_CASE("Testes basicos para a Classe Funcionario") {
   
    Funcionario funcionario(1, "3199999999", "Lucas Silva", "Gerente", 5000.0f);
    CHECK(funcionario.getCodigo() == 1);
    CHECK(funcionario.getTelefone() == "3199999999");
    CHECK(funcionario.getNome() == "Lucas Silva");
    CHECK(funcionario.getCargo() == "Gerente");
    CHECK(funcionario.getSalario() == 5000.0f);

    funcionario.setSalario(6000.0f);
    CHECK(funcionario.getSalario() == 6000.0f);

    CHECK_THROWS_AS(Funcionario(2, "3199999998", "Fernando Matias", "Assistente", -1000.0f), std::runtime_error);

    CHECK_THROWS_AS(funcionario.setSalario(-2000.0f), std::runtime_error);
}