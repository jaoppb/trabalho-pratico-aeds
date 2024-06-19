cmake_minimum_required(VERSION 3.22)
project(DescansoGarantido)

add_executable(
	DescansoGarantido
	src/main.cpp
)

file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data SYMBOLIC)