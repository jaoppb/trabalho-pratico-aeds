#include <catch2/catch_test_macros.hpp>
#include "../src/pessoa.hpp"
#include "handlers.hpp"

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

TEST_CASE("Testes para o Handler de Pessoas") {
    SECTION("Cadastro de Cliente") {
        const Cliente *cliente1 = nullptr;
        REQUIRE_NOTHROW(cliente1 = pessoasHandler->cadastrarCliente("12345678", "João Augusto", "R. Um, 200", 0));
        
        REQUIRE(pessoasHandler->getCliente(cliente1->getCodigo()) == cliente1);
        CHECK(cliente1->getTelefone() == "12345678");
        CHECK(cliente1->getNome() == "João Augusto");
        CHECK(cliente1->getPontos() == 0);

        REQUIRE_NOTHROW(pessoasHandler->addPontos(cliente1, 5));
        CHECK(cliente1->getPontos() == 50);

        CHECK_NOTHROW(pessoasHandler->cadastrarCliente("213241214", "Diego Borges", "R. Dois, 200", -213));
        CHECK_THROWS(pessoasHandler->cadastrarCliente("232141231", "Ana Clara", "", -13));
    }

    SECTION("Cadastro de Funcionário") {
        const Funcionario *funcionario1 = nullptr;
        REQUIRE_NOTHROW(funcionario1 = pessoasHandler->cadastrarFuncionaro("145689624", "Fernando Gomes", "Gerente", 1230.4f));

        REQUIRE(pessoasHandler->getFuncionario(funcionario1->getCodigo()) == funcionario1);
        CHECK(funcionario1->getTelefone() == "145689624");
        CHECK(funcionario1->getNome() == "Fernando Gomes");
        CHECK(funcionario1->getCargo() == "Gerente");
    }
}