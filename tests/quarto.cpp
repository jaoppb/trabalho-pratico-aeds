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

TEST_CASE("Testa básico da Classe Quartos") {
	{
		Quartos quartos;
		const Quarto *quarto10 = quartos.criarQuarto(10, 24.0f);
		
		CHECK(quarto10 -> getNumero() == 10);
		CHECK(quarto10 -> getDiaria() == 24.0f);
		
		CHECK_THROWS(quartos.criarQuarto(10, 24.51f));
		CHECK_THROWS(quartos.criarQuarto(20, 0.0f));
		CHECK_THROWS(quartos.criarQuarto(15, -10.0f));
		CHECK_THROWS(quartos.criarQuarto(-4, 18.0f));
		CHECK_THROWS(quartos.criarQuarto(-8, -1.0f));

		CHECK(quartos.getStatus(10) == false);
		quartos.setStatus(10, true);
		CHECK(quartos.getStatus(10) == true);

		CHECK_THROWS(quartos.getStatus(20));
		CHECK_THROWS(quartos.getStatus(15));
		CHECK_THROWS(quartos.setStatus(20, false));
		CHECK_THROWS(quartos.setStatus(15, true));

		const Quarto *quarto05, *quarto20;
		CHECK_NOTHROW(quarto05 = quartos.criarQuarto( 5, 19.9f));
		CHECK_NOTHROW(quarto20 = quartos.criarQuarto(20, 14.9f));

		CHECK(quartos.getQuarto( 5) == quarto05);
		CHECK(quartos.getQuarto(10) == quarto10);
		CHECK(quartos.getQuarto(20) == quarto20);

		CHECK_THROWS(quartos.getQuarto( 15));
		CHECK_THROWS(quartos.getQuarto(-24));
	}
}