#include <catch2/catch_test_macros.hpp>

#include "../src/handlers/files.hpp"

TEST_CASE("Teste básico para arquivos") {
	FileHandler handler("tests.bin");
	handler.clear();
	handler.open();
	std::string str = "Teste de String";
	handler.write(str);

	int integer = 12345678;
	bool boolean = true;
	double number = 123421320194.2140123f;

	handler.write((void*)&integer, sizeof(integer));
	handler.write((void*)&boolean, sizeof(boolean));
	handler.write((void*)&number, sizeof(number));

	handler.close();

	str = "";
	integer = 0;
	boolean = false;
	number = 0;

	handler.open();

	handler.read(str);
	handler.read((void*)&integer, sizeof(integer));
	handler.read((void*)&boolean, sizeof(boolean));
	handler.read((void*)&number, sizeof(number));

	handler.close();

	CHECK(str == "Teste de String");
	CHECK(integer == 12345678);
	CHECK(boolean == true);
	CHECK(number == 123421320194.2140123f);
}