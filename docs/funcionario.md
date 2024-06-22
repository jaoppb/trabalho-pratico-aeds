# Funcionario
Classe derivada de Pessoa

## Atributos

-  `std::string cargo`
-  `float salario`

## Métodos

### Funcionario(unsigned int codigo, unsigned int telefone, std::string nome, std::string cargo, float salario) 
Construtor da classe que inicializa os atributos passados como parâmetro. Caso salário seja negativo, um erro é laçado.

### const std::string getCargo() const

Retorna o `cargo` somente para leitura.

### const float getSalario() const

Retorna o `salario` somemte para leitura.

### void setSalario(float salario)

Modifica o `salario`.