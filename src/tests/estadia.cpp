#include <catch2/catch_test_macros.hpp>

#include "../estadia.hpp"
#include "../global.hpp"

TEST_CASE("Testes básicos para a Classe Estadia") {
    //cadastrar quarto
    const Quarto *quarto = quartosHandler -> criarQuarto(12, 1.0f);
    REQUIRE(quarto != nullptr);
    const uint roomNum = quarto -> getNumero();

    //cadastrar cliente
    const Cliente *cliente = pessoasHandler -> cadastrarCliente(3199999999, "Cliente Teste", "Rua 31, 200, Bairro Tal - Cidade Tal", 0);
    REQUIRE(cliente != nullptr);
    const uint clientCode = cliente -> getCodigo();

	{
		CHECK(Estadia(10, "24/07/2024", "25/07/2024", clientCode, roomNum).getDiarias() ==  1);
		CHECK(Estadia(10, "25/07/2024", "29/07/2024", clientCode, roomNum).getDiarias() ==  4);
		CHECK(Estadia(10, "30/07/2024", "04/08/2024", clientCode, roomNum).getDiarias() ==  5);
		CHECK(Estadia(10, "12/03/2024", "21/04/2024", clientCode, roomNum).getDiarias() == 40);
	}
	{
		CHECK_THROWS(Estadia(10, "21/12/2024", "20/12/2024", clientCode, roomNum));
		CHECK_THROWS(Estadia(10, "21/12/2024", "21/11/2024", clientCode, roomNum));
		CHECK_THROWS(Estadia(10, "24/05/2024", "20/04/2024", clientCode, roomNum));
		CHECK_THROWS(Estadia(10, "02/01/2024", "01/01/2024", clientCode, roomNum));
		CHECK_THROWS(Estadia(10, "10/03/2024", "10/02/2024", clientCode, roomNum));
	}
    {
        REQUIRE_THROWS(pessoasHandler -> getCliente(12));
		CHECK_THROWS(Estadia(10, "24/07/2024", "25/07/2024", 12, roomNum));
		CHECK_THROWS(Estadia(10, "25/07/2024", "29/07/2024", 12, roomNum));
		CHECK_THROWS(Estadia(10, "30/07/2024", "04/08/2024", 12, roomNum));
		CHECK_THROWS(Estadia(10, "12/03/2024", "21/04/2024", 12, roomNum));
    }
    {
        REQUIRE_THROWS(quartosHandler -> getQuarto(100));
		CHECK_THROWS(Estadia(10, "24/07/2024", "25/07/2024", clientCode, 100));
		CHECK_THROWS(Estadia(10, "25/07/2024", "29/07/2024", clientCode, 100));
		CHECK_THROWS(Estadia(10, "30/07/2024", "04/08/2024", clientCode, 100));
		CHECK_THROWS(Estadia(10, "12/03/2024", "21/04/2024", clientCode, 100));
    }
    {
        REQUIRE_THROWS(pessoasHandler -> getCliente(12));
        REQUIRE_THROWS(quartosHandler -> getQuarto(100));
		CHECK_THROWS(Estadia(10, "24/07/2024", "25/07/2024", 12, 100));
		CHECK_THROWS(Estadia(10, "25/07/2024", "29/07/2024", 12, 100));
		CHECK_THROWS(Estadia(10, "30/07/2024", "04/08/2024", 12, 100));
		CHECK_THROWS(Estadia(10, "12/03/2024", "21/04/2024", 12, 100));
    }
}

TEST_CASE("Testes básicos para a Classe Estadias") {
    //registra um quarto
    const Quarto *quarto = quartosHandler -> criarQuarto(123, 12.0f);
    REQUIRE(quarto != nullptr);
    const uint roomNum = quarto -> getNumero();

    //registra um cliente
    const Cliente *cliente = pessoasHandler -> cadastrarCliente(3199999999, "Cliente Teste", "Rua 31, 200, Bairro Tal - Cidade Tal", 0);
    REQUIRE(cliente != nullptr);
    const uint clientCode = cliente -> getCodigo();

    {
        const Estadia* estadia = estadiasHandler -> agendarEstadia("23/06/2024", "25/06/2024", clientCode, roomNum);
        CHECK(estadia -> getDiarias() == 2);
        CHECK_THROWS(estadiasHandler -> agendarEstadia("24/06/2024", "25/06/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("19/06/2024", "22/06/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("19/06/2024", "27/06/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("19/02/2024", "27/12/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("21/06/2024", "22/06/2024", clientCode, roomNum));
        CHECK(estadiasHandler -> agendarEstadia("25/06/2024", "28/06/2024", clientCode, roomNum) != nullptr);
        CHECK(estadiasHandler -> agendarEstadia("28/06/2024", "03/07/2024", clientCode, roomNum) != nullptr);
    }

    {
        CHECK_THROWS(estadiasHandler -> agendarEstadia("25/06/2024", "21/06/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("21/06/2024", "21/06/2024", clientCode, roomNum));
    }

    {
        CHECK_THROWS(estadiasHandler -> agendarEstadia("31/02/2024", "02/03/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("28/02/2024", "30/02/2024", clientCode, roomNum));
    }

    {
        CHECK_THROWS(estadiasHandler -> agendarEstadia("2024/06/21", "25/06/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("21/06/2024", "2024/06/25", clientCode, roomNum));
    }

    {
        const Estadia* estadias[5] = {};
        estadias[0] = estadiasHandler -> agendarEstadia("12/10/2024", "13/10/2024", clientCode, roomNum);
        estadias[1] = estadiasHandler -> agendarEstadia("13/10/2024", "16/10/2024", clientCode, roomNum);
        estadias[2] = estadiasHandler -> agendarEstadia("20/10/2024", "31/10/2024", clientCode, roomNum);
        estadias[3] = estadiasHandler -> agendarEstadia("03/11/2024", "10/11/2024", clientCode, roomNum);
        estadias[4] = estadiasHandler -> agendarEstadia("10/11/2024", "20/12/2024", clientCode, roomNum);
        int points = cliente -> getPontos();
        {
            CHECK(estadiasHandler -> darBaixa(estadias[0] -> getCodigo()) == 12.0f);
            CHECK(cliente -> getPontos() == (points += 10));
        }
        {
            CHECK(estadiasHandler -> darBaixa(estadias[1] -> getCodigo()) == 36.0f);
            CHECK(cliente -> getPontos() == (points += 30));
        }
        {
            CHECK(estadiasHandler -> darBaixa(estadias[2] -> getCodigo()) == 132.0f);
            CHECK(cliente -> getPontos() == (points += 110));
        }
        {
            CHECK(estadiasHandler -> darBaixa(estadias[3] -> getCodigo()) == 84.0f);
            CHECK(cliente -> getPontos() == (points += 70));
        }
        {
            CHECK(estadiasHandler -> darBaixa(estadias[4] -> getCodigo()) == 480.0f);
            CHECK(cliente -> getPontos() == (points += 400));
        }
    }
}