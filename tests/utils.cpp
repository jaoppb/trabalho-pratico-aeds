#include <catch2/catch_test_macros.hpp>

#include "../src/utils.hpp"

TEST_CASE("Teste básico do parseDate") {
	{
		CHECK(parseDate("31/12/1969 - 21:00:00") == 0);
		CHECK(parseDate("21/06/2024 - 15:30:00") == 1718994600);
		CHECK(parseDate("01/01/2024 - 00:00:00") == 1704078000);
		CHECK(parseDate("31/12/2024 - 23:59:59") == 1735700399);
		CHECK(parseDate("21/06/2024 - 00:00:00") == 1718938800);
		CHECK(parseDate("21/06/2024 - 23:59:59") == 1719025199);
		CHECK(parseDate("29/02/2024 - 12:00:00") == 1709218800);
	}
	{
		CHECK(parseDate("01/01/2024") == 1704078000);
		CHECK(parseDate("21/06/2024") == 1718938800);
	}
	{
		CHECK_THROWS(parseDate("32/13/2024 - 25:61:61"));
		CHECK_THROWS(parseDate("2024/06/21 - 15:30:00"));
		CHECK_THROWS(parseDate("2024/06/21 - 15:30:00"));
		CHECK_THROWS(parseDate("31/02/2024 - 12:00:00"));
		CHECK_THROWS(parseDate("29/02/2023 - 12:00:00"));
		CHECK_THROWS(parseDate("31/04/2024 - 10:00:00"));
	}
	{
		CHECK_THROWS(parseDate("31/02/2024"));
		CHECK_THROWS(parseDate("29/02/2023"));
		CHECK_THROWS(parseDate("31/04/2024"));
	}
}