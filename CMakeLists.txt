cmake_minimum_required(VERSION 3.22)
project(DescansoGarantido)

add_library(
	DescansoGarantido_LIB
	src/quarto.cpp
	src/cliente.cpp
	src/estadia.cpp
	src/utils.cpp
)

add_executable(DescansoGarantido src/main.cpp)
target_link_libraries(DescansoGarantido DescansoGarantido_LIB)

find_package(Catch2 3 REQUIRED)
add_executable(
	tests
	tests/quarto.cpp
	tests/estadia.cpp
	tests/utils.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain DescansoGarantido_LIB)

IF(WIN32)
	find_path(CATCH_INCLUDE_DIR NAMES catch.hpp PATH_SUFFIXES catch2)
	target_include_directories(tests PRIVATE ${CATCH_INCLUDE_DIR})
ENDIF()