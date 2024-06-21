#include <catch2/catch_test_macros.hpp>

#include "../src/estadia.hpp"

TEST_CASE("Testes básicos para a Classe Estadia") {
	{
		CHECK(Estadia(10, "24/07/2024", "25/07/2024", 11, 12).getDiarias() ==  1);
		CHECK(Estadia(10, "25/07/2024", "29/07/2024", 11, 12).getDiarias() ==  4);
		CHECK(Estadia(10, "30/07/2024", "04/08/2024", 11, 12).getDiarias() ==  5);
		CHECK(Estadia(10, "12/03/2024", "21/04/2024", 11, 12).getDiarias() == 40);
	}
	{
		CHECK_THROWS(Estadia(10, "21/12/2024", "20/12/2024", 11, 12));
		CHECK_THROWS(Estadia(10, "21/12/2024", "21/11/2024", 11, 12));
		CHECK_THROWS(Estadia(10, "24/05/2024", "20/04/2024", 11, 12));
		CHECK_THROWS(Estadia(10, "02/01/2024", "01/01/2024", 11, 12));
		CHECK_THROWS(Estadia(10, "10/03/2024", "10/02/2024", 11, 12));
	}
}

TEST_CASE("Testes básicos para a Classe Estadias") {
	Estadias estadias;

    {
        const Estadia* estadia = estadias.agendarEstadia("21/06/2024", "25/06/2024", 123, 101);
        CHECK(estadia -> getDiarias() == 4);
    }

    {
        CHECK_THROWS(estadias.agendarEstadia("25/06/2024", "21/06/2024", 123, 101));
        CHECK_THROWS(estadias.agendarEstadia("21/06/2024", "21/06/2024", 123, 101));
    }

    {
        CHECK_THROWS(estadias.agendarEstadia("31/02/2024", "02/03/2024", 123, 101));
        CHECK_THROWS(estadias.agendarEstadia("28/02/2024", "30/02/2024", 123, 101));
    }

    {
        CHECK_THROWS(estadias.agendarEstadia("2024/06/21", "25/06/2024", 123, 101));
        CHECK_THROWS(estadias.agendarEstadia("21/06/2024", "2024/06/25", 123, 101));
    }
}