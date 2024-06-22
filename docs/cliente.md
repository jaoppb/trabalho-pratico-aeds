# Clientes
Classe derivade de Pessoa

## Atributos 

-  `unsigned int codigo`
-  `unsigned int telefone`
-  `std::string nome`
-  `std::string endereco`


## Métodos

### Cliente(unsigned int codigo, unsigned int telefone, std::string nome, std::string endereco)
Construtor da classe que inicializa os atributos com os valores passados como parâmtros

### int getPontos()

retorna os `pontos` totais.

### void addPontos(int diarias)

A cada diária o cliente recebe 10 pontos.

### std::string getEndereco()

Retorna o `endereço` cadastrado. 

### void setEndereco(string endereco) 

Modifica o `endereço`.



