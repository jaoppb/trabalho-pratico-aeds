set(CMAKE_CXX_STANDARD 11)

cmake_minimum_required(VERSION 3.22)
project(DescansoGarantido)

add_library(
	DescansoGarantido_LIB
	src/quarto.cpp
	src/pessoa.cpp
	src/cliente.cpp
	src/funcionario.cpp
	src/estadia.cpp
	src/handlers/estadias.cpp
	src/handlers/pessoas.cpp
	src/handlers/quartos.cpp
	src/handlers/files.cpp
	src/utils.cpp
)

add_executable(
	DescansoGarantido
	src/main.cpp
	src/global.cpp)
target_link_libraries(DescansoGarantido DescansoGarantido_LIB)

find_package(Catch2 3 REQUIRED)
add_executable(
	tests
	src/tests/main.cpp
	src/tests/quarto.cpp
	src/tests/estadia.cpp
	src/tests/cliente.cpp
	src/tests/funcionario.cpp
	src/tests/files.cpp
	src/tests/utils.cpp
	src/tests/handlers.cpp
	src/tests/pessoa.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2 DescansoGarantido_LIB)

file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data COPY_ON_ERROR SYMBOLIC)