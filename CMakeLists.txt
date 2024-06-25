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
	src/global.cpp
	src/utils.cpp
)

add_executable(DescansoGarantido src/main.cpp)
target_link_libraries(DescansoGarantido DescansoGarantido_LIB)
