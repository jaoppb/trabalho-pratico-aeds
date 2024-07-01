#include <catch2/catch_test_macros.hpp>

#include "../src/quarto.hpp"
#include "handlers.hpp"

TEST_CASE("Teste básico da Classe Quarto", "Exceptions da Classe Quarto") {
	{
		Quarto quarto(10, 24.99f, 1);

		CHECK( quarto.getNumero() == 10 );
		CHECK( quarto.getDiaria() == 24.99f );
		CHECK( quarto.getQuantidadeDeHospedes() == 1 );
		CHECK( quarto.getStatus() == false );
	}

	{
		Quarto quarto(20.5f, 242, 1);

		CHECK( quarto.getNumero() ==  20    );
		CHECK( quarto.getDiaria() == 242.0f );
		CHECK( quarto.getQuantidadeDeHospedes() == 1 );
		CHECK( quarto.getStatus() == false );
	}

	{
		CHECK_NOTHROW( Quarto(-0, 1.0f, 1) );
		CHECK_NOTHROW( Quarto(0 ,  .1f, 1) );

		CHECK_THROWS( Quarto( 100,   0.0f, 1) );
		CHECK_THROWS( Quarto( -20, -24.0f, 1) );
		
		CHECK_THROWS( Quarto(100, 150.0f, 0) );
		CHECK_THROWS( Quarto(120, 200.0f, 0) );
	}
}

TEST_CASE("Testa básico da Classe Quartos") {
	{
		const Quarto *quarto10 = quartosHandler -> criarQuarto(10, 24.0f, 1);
		
		CHECK(quarto10 -> getNumero() == 10);
		CHECK(quarto10 -> getDiaria() == 24.0f);
		
		CHECK_THROWS(quartosHandler -> criarQuarto(10, 24.51f, 1));
		CHECK_THROWS(quartosHandler -> criarQuarto(20, 0.0f, 1));
		CHECK_THROWS(quartosHandler -> criarQuarto(15, -10.0f, 1));
		CHECK_THROWS(quartosHandler -> criarQuarto(-8, -1.0f, 1));

		CHECK(quartosHandler -> getStatus(10) == false);
		quartosHandler -> setStatus(10, true);
		CHECK(quartosHandler -> getStatus(10) == true);

		CHECK_THROWS(quartosHandler -> getStatus(20));
		CHECK_THROWS(quartosHandler -> getStatus(15));
		CHECK_THROWS(quartosHandler -> getStatus(-10));
		CHECK_THROWS(quartosHandler -> getStatus(-90));
		CHECK_THROWS(quartosHandler -> setStatus(20, false));
		CHECK_THROWS(quartosHandler -> setStatus(15, true));
		CHECK_THROWS(quartosHandler -> setStatus(-10, false));
		CHECK_THROWS(quartosHandler -> setStatus(-90, true));

		const Quarto *quarto05 = nullptr, *quarto20 = nullptr;
		CHECK_NOTHROW(quarto05 = quartosHandler -> criarQuarto( 5, 19.9f, 4));
		CHECK_NOTHROW(quarto20 = quartosHandler -> criarQuarto(20, 14.9f, 2));

		CHECK(quartosHandler -> getQuarto( 5) == quarto05);
		CHECK(quartosHandler -> getQuarto(10) == quarto10);
		CHECK(quartosHandler -> getQuarto(20) == quarto20);

		CHECK_THROWS(quartosHandler -> getQuarto( 15));
		CHECK_THROWS(quartosHandler -> getQuarto(-24));

		std::vector<Quarto*> quartos = quartosHandler->getRoomsByCapacity(1);
		CHECK(quartos.size() == 5);

		quartos = quartosHandler->getRoomsByCapacity(3);
		CHECK(quartos.size() == 2);

		quartos = quartosHandler->getRoomsByCapacity(-10);
		CHECK(quartos.size() == 0);
	}
}