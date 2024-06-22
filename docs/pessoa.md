# Pessoa

## Atributos

-  `unsigned int telefone`
-  `unsigned int codigo`
-  `std::string nome`

## Métodos 

### Pessoa(unsigned int codigo, unsigned int telefone, std::string nome)
Construtor da classe que incializa os atributos passados como parâmetro

### virtual ~Pessoa()
Para transformar a classe pessoa em uma classe polimórfica, usa-se o desconstrutor como virtual. Isso é necessário para trasformar ponteiros do objeto pessoa para um ponteiro de objeto de uma de suas classes derivadas. 

### const usigned int getCodigo() const
Retorna o código como somente leitura.

### const usigned int getTelefone() const
Retorna o telefona como somente leitura.

### const std::string getNome() const
Retorna o nome como somente leitura

