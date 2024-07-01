#include <catch2/catch_test_macros.hpp>

#include "../src/estadia.hpp"
#include "../src/utils.hpp"
#include "handlers.hpp"

TEST_CASE("Testes básicos para a Classe Estadia") {
    //cadastrar quarto
    const Quarto *quarto = nullptr;
    try {
        quarto = quartosHandler -> criarQuarto(12, 1.0f, 1);
    } catch(std::runtime_error &err) {
        quarto = quartosHandler -> getQuarto(12);
    }
    REQUIRE(quarto != nullptr);
    const int roomNum = quarto -> getNumero();

    //cadastrar cliente
    const Cliente *cliente = nullptr;
    try {
        cliente = pessoasHandler -> cadastrarCliente("3199999999", "Cliente Teste", "Rua 31, 200, Bairro Tal - Cidade Tal", 0);
    } catch(std::runtime_error &err) {
        cliente = pessoasHandler -> getCliente("Cliente Teste")[0];
    }
    REQUIRE(cliente != nullptr);
    const int clientCode = cliente -> getCodigo();

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
    const Quarto *quarto = nullptr;
    try {
        quarto = quartosHandler -> criarQuarto(123, 12.0f, 1);
    } catch(std::runtime_error &err) {
        quarto = quartosHandler -> getQuarto(123);
    }
    REQUIRE(quarto != nullptr);
    const int roomNum = quarto -> getNumero();

    //registra um cliente
    const Cliente *cliente = nullptr;
    try {
        cliente = pessoasHandler -> cadastrarCliente("3199999999", "Cliente Teste", "Rua 31, 200, Bairro Tal - Cidade Tal", 0);
    } catch(std::runtime_error &err) {
        cliente = pessoasHandler -> getCliente("Cliente Teste")[0];
    }
    REQUIRE(cliente != nullptr);
    const int clientCode = cliente -> getCodigo();

    SECTION("") {
        CHECK_THROWS(estadiasHandler -> agendarEstadia("24/06/2024", "25/06/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("19/06/2024", "22/06/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("19/06/2024", "27/06/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("19/02/2024", "27/12/2024", clientCode, roomNum));
        CHECK_THROWS(estadiasHandler -> agendarEstadia("21/06/2024", "22/06/2024", clientCode, roomNum));
        CHECK(estadiasHandler -> agendarEstadia("13/07/2025", "19/07/2025", clientCode, roomNum) != nullptr);
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

    SECTION("Teste de Estadias::darBaixa") {
        const Estadia* estadias[5] = {};
        REQUIRE((estadias[0] = estadiasHandler -> agendarEstadia("20/12/2024", "21/12/2024", clientCode, roomNum)) != nullptr);
        REQUIRE((estadias[1] = estadiasHandler -> agendarEstadia("14/10/2024", "16/10/2024", clientCode, roomNum)) != nullptr);
        REQUIRE((estadias[2] = estadiasHandler -> agendarEstadia("20/10/2024", "31/10/2024", clientCode, roomNum)) != nullptr);
        REQUIRE((estadias[3] = estadiasHandler -> agendarEstadia("03/11/2024", "10/11/2024", clientCode, roomNum)) != nullptr);
        REQUIRE((estadias[4] = estadiasHandler -> agendarEstadia("22/12/2024", "23/12/2024", clientCode, roomNum)) != nullptr);
        int points = cliente -> getPontos();
        {
            CHECK(estadiasHandler -> darBaixa(estadias[0] -> getCodigo()) == 12.0f);
            CHECK(cliente -> getPontos() == (points += 10));
        }
        {
            CHECK(estadiasHandler -> darBaixa(estadias[1] -> getCodigo()) == 24.0f);
            CHECK(cliente -> getPontos() == (points += 20));
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
            CHECK(estadiasHandler -> darBaixa(estadias[4] -> getCodigo()) == 12.0f);
            CHECK(cliente -> getPontos() == (points += 10));
        }
    }

    SECTION("getTotal") {
        REQUIRE(estadiasHandler->getTotal() == 7);

        REQUIRE(quartosHandler->criarQuarto(401, 100, 3) != nullptr);

        REQUIRE(estadiasHandler->agendarEstadia("12/12/2024", "13/12/2024", clientCode, 401) != nullptr);

        CHECK(estadiasHandler->getTotal() == 8);
    }

    SECTION("getEstadia(unsigned int code)") {
        const Estadia* estadia = estadiasHandler->getEstadia(estadiasHandler->getTotal());
        REQUIRE(estadia == nullptr);

        REQUIRE((estadia = estadiasHandler->agendarEstadia("12/12/2026", "13/12/2026", clientCode, 401)) != nullptr);

        CHECK(estadia == estadiasHandler->getEstadia(estadia->getCodigo()));
    }

    SECTION("getEstadias(std::string date)") {
        CHECK_THROWS(estadiasHandler->getEstadia("29/02/2025"));

        std::vector<Estadia*> estadias = estadiasHandler->getEstadia("01/01/2025");
        REQUIRE(estadias.size() == 0);

        REQUIRE(quartosHandler->criarQuarto(500, 250, 4) != nullptr);
        REQUIRE(quartosHandler->criarQuarto(501, 250, 4) != nullptr);

        REQUIRE(estadiasHandler->agendarEstadia("31/12/2024", "04/01/2025", clientCode, 500) != nullptr);
        REQUIRE(estadiasHandler->agendarEstadia("20/12/2024", "01/01/2025", clientCode, 501) != nullptr);
        REQUIRE(estadiasHandler->agendarEstadia("02/01/2025", "10/01/2025", clientCode, 501) != nullptr);

        estadias = estadiasHandler->getEstadia("01/01/2025");
        CHECK(estadias.size() == 2);
    }

    SECTION("getEstadias(unsigned int clientCode)") {
        std::vector<Estadia*> estadias = estadiasHandler->getEstadias(0);
        REQUIRE(estadias.size() == 1);

        REQUIRE(estadiasHandler->agendarEstadia("21/12/2025", "30/12/2025", 0, 500) != nullptr);
        REQUIRE(estadiasHandler->agendarEstadia("20/12/2025", "10/01/2026", 0, 501) != nullptr);

        REQUIRE(estadiasHandler->getEstadias(0).size() == 3);
    }

    SECTION("getEstadias(std::vector<unsigned int> clinetCodes)") {
        unsigned int code = 0;
        REQUIRE_NOTHROW((code = pessoasHandler->cadastrarCliente("12345678", "Diego Lopes", "R. Dois, 423", 0)->getCodigo()));

        std::vector<unsigned int> codes = {0, code};
        REQUIRE(estadiasHandler->getEstadias(codes).size() == 3);

        REQUIRE(estadiasHandler->agendarEstadia("10/01/2025", "20/02/2025", 0, 500) != nullptr);
        REQUIRE(estadiasHandler->agendarEstadia("11/01/2025", "20/01/2025", 0, 501) != nullptr);

        REQUIRE(quartosHandler->criarQuarto(600, 250, 4) != nullptr);
        REQUIRE(quartosHandler->criarQuarto(601, 250, 4) != nullptr);

        REQUIRE(estadiasHandler->agendarEstadia("31/12/2024", "04/01/2025", code, 600) != nullptr);
        REQUIRE(estadiasHandler->agendarEstadia("20/12/2024", "10/01/2025", code, 601) != nullptr);

        CHECK(estadiasHandler->getEstadias(codes).size() == 7);
    }

    SECTION("getEstadiasByRoom") {
        REQUIRE(quartosHandler->criarQuarto(700, 250, 4) != nullptr);

        REQUIRE(estadiasHandler->getEstadiasByRoom(700).size() == 0);

        REQUIRE(estadiasHandler->agendarEstadia("31/12/2024", "04/01/2025", 0, 700) != nullptr);
        REQUIRE(estadiasHandler->agendarEstadia("04/01/2025", "05/01/2025", 0, 700) != nullptr);

        CHECK(estadiasHandler->getEstadiasByRoom(700).size() == 2);
    }

    SECTION("isAvaliable") {
        time_t checkIn = parseDate("15/12/2024");
        time_t checkOut = parseDate("17/12/2024");
        REQUIRE(estadiasHandler->isAvaliable(300, checkIn, checkOut) == true);

        REQUIRE_NOTHROW(quartosHandler->criarQuarto(300, 250, 3));
        REQUIRE_NOTHROW(estadiasHandler->agendarEstadia("14/12/2024", "16/12/2024", 0, 300));

        REQUIRE(estadiasHandler->isAvaliable(300, checkIn, checkOut) == false);
    }
}