#include <catch2/catch_test_macros.hpp>

#include "../src/utils.hpp"

TEST_CASE("Teste básico do parseDate") {
	SECTION("Data válidas - com e sem horários") {
		CHECK(parseDate("01/01/1970 - 00:00:00") == 0);
		CHECK(parseDate("21/06/2024 - 15:30:00") == 1718983800);
		CHECK(parseDate("01/01/2024 - 00:00:00") == 1704067200);
		CHECK(parseDate("31/12/2024 - 23:59:59") == 1735689599);
		CHECK(parseDate("21/06/2024 - 00:00:00") == 1718928000);
		CHECK(parseDate("21/06/2024 - 23:59:59") == 1719014399);
		CHECK(parseDate("29/02/2024 - 12:00:00") == 1709208000);
		CHECK(parseDate("01/01/2024") == 1704067200);
		CHECK(parseDate("21/06/2024") == 1718928000);
	}
	SECTION("Datas e horários inválidos") {
		CHECK_THROWS(parseDate("32/13/2024 - 25:61:61"));
		CHECK_THROWS(parseDate("2024/06/21 - 15:30:00"));
		CHECK_THROWS(parseDate("2024/06/21 - 15:30:00"));
		CHECK_THROWS(parseDate("31/02/2024 - 12:00:00"));
		CHECK_THROWS(parseDate("29/02/2023 - 12:00:00"));
		CHECK_THROWS(parseDate("31/04/2024 - 10:00:00"));
	}
	SECTION("Datas com dias inexistentes") {
		CHECK_THROWS(parseDate("31/02/2024"));
		CHECK_THROWS(parseDate("29/02/2023"));
		CHECK_THROWS(parseDate("31/04/2024"));
	}
}

TEST_CASE("Teste da toLower") {
	SECTION("Tudo maiusculo") {
		std::string str = "FOA J S DOP IHA OSIDF";
		toLower(str);
		CHECK(str == "foa j s dop iha osidf");
	}

	SECTION("Tudo minusculo") {
		std::string str = "fjaoisfjasijdoas dapojsa dajsio";
		toLower(str);
		CHECK(str == "fjaoisfjasijdoas dapojsa dajsio");
	}

	SECTION("Misturado") {
		std::string str = "asfasidOSAIFJosijdaofijAOS FoASIf hAS";
		toLower(str);
		CHECK(str == "asfasidosaifjosijdaofijaos foasif has");
	}

	SECTION("Com caracteres variados") {
		std::string str = "!@#$%¨&*()_+=-,<.>;:~^´`[{}]°|\\ºª§¹²³£¢¬?1234567890";
		toLower(str);
		CHECK(str == "!@#$%¨&*()_+=-,<.>;:~^´`[{}]°|\\ºª§¹²³£¢¬?1234567890");
	}
}

TEST_CASE("Testes da formatTimestamp") {
	CHECK(formatTimestamp(0) 		  == "31/12/69");
	CHECK(formatTimestamp(1718983800) == "21/06/24");
	CHECK(formatTimestamp(1704067200) == "31/12/23");
	CHECK(formatTimestamp(1735689599) == "31/12/24");
	CHECK(formatTimestamp(1718928000) == "20/06/24");
	CHECK(formatTimestamp(1719014399) == "21/06/24");
	CHECK(formatTimestamp(1709208000) == "29/02/24");
	CHECK(formatTimestamp(1704067200) == "31/12/23");
	CHECK(formatTimestamp(1718928000) == "20/06/24");
}