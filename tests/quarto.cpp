#include <catch2/catch_test_macros.hpp>

#include "../src/quarto.hpp"

TEST_CASE("Teste básico da Classe Quarto") {
	{
		Quarto quarto(10, 24.99f);

		CHECK( quarto.getNumero() == 10 );
		CHECK( quarto.getDiaria() == 24.99f );
		CHECK( quarto.getQuantidadeDeHospedes() == 0 );
		CHECK( quarto.getStatus() == false );
	}

	{
		Quarto quarto(20.5f, 242);

		CHECK( quarto.getNumero() ==  20    );
		CHECK( quarto.getDiaria() == 242.0f );
		CHECK( quarto.getQuantidadeDeHospedes() == 0 );
		CHECK( quarto.getStatus() == false );
	}
}

TEST_CASE("Exceptions da Classe Quarto") {
	CHECK_NOTHROW( Quarto(-0, 1.0f) );
	CHECK_NOTHROW( Quarto(0 ,  .1f) );

	CHECK_THROWS( Quarto(  -1,  10.0f) );
	CHECK_THROWS( Quarto( 100,   0.0f) );
	CHECK_THROWS( Quarto( -20, -24.0f) );
}