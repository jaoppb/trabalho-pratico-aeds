cmake_minimum_required(VERSION 3.22)
project(DescansoGarantido)


add_library(
	DescansoGarantido_LIB
	src/quarto.cpp
)

add_executable(DescansoGarantido src/main.cpp)
target_link_libraries(DescansoGarantido DescansoGarantido_LIB)

find_package(Catch2 3 REQUIRED)
add_executable(
	DescansoGarantido
	src/main.cpp
)

file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data SYMBOLIC)