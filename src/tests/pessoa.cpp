#include <catch2/catch_test_macros.hpp>
#include "../pessoa.hpp"

TEST_CASE("Testes basicos para a Classe Pessoa") {
   
    Pessoa pessoa(1, "3199999999", "Lucas Silva");
    CHECK(pessoa.getCodigo() == 1);
    CHECK(pessoa.getTelefone() == "3199999999");
    CHECK(pessoa.getNome() == "Lucas Silva");

    Pessoa pessoa2(2, "3198888888", "Ana Maria");
    CHECK(pessoa2.getCodigo() == 2);
    CHECK(pessoa2.getTelefone() == "3198888888");
    CHECK(pessoa2.getNome() == "Ana Maria");
}