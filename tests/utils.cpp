#include <catch2/catch_test_macros.hpp>

#include "../src/utils.hpp"

TEST_CASE("Teste básico do parseDate") {
	{
		CHECK(parseDate("01/01/1970 - 00:00:00") == 0);
		CHECK(parseDate("21/06/2024 - 15:30:00") == 1718983800);
		CHECK(parseDate("01/01/2024 - 00:00:00") == 1704067200);
		CHECK(parseDate("31/12/2024 - 23:59:59") == 1735689599);
		CHECK(parseDate("21/06/2024 - 00:00:00") == 1718928000);
		CHECK(parseDate("21/06/2024 - 23:59:59") == 1719014399);
		CHECK(parseDate("29/02/2024 - 12:00:00") == 1709208000);
	}
	{
		CHECK(parseDate("01/01/2024") == 1704067200);
		CHECK(parseDate("21/06/2024") == 1718928000);
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