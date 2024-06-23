# Quarto

## Atributos

int   **numero** <br>
int   **quantidadeDeHospedes** <br>
float **diaria** <br>
bool  **status**

> numero >= 0 <br>
> quantidadeDeHospede > 0 <br>
> diaria > 0 <br>
> status: `true` para ocupado e `false` para descupado.


## Métodos

### Quarto(int numero, float diaria)
Construtor da classe que inicializa quantidadeDeHospedes com 0, status com false e os outros atributos passados por parâmetro. Caso esteja fora dos limites, um erro é lançado.

### int getNumero()
Retorna o número do quarto.

### int getQuantidadeDeHospedes()
Retorna a quantidade de hospédes que estão atualmente no quarto.

### float getDiaria()
Retorna o valor da diária do quarto.

### bool getStatus()
Retorna o status atual do quarto.

### void setQuantidadeDeHospedes(int hospedes)
Define a quantidade de hospedes no quarto.

### void setDiaria(float diaria)
Define o valor da diária do quarto, caso esteja fora do limite um erro é lançado.

### void setStatus(float status)
Define o status atual do quarto.


# Quartos

## Atributos

std::vector\<Quarto\*\> **quartos**

## Metódos

### Quarto()
Inicializa `quartos` como um vector vazio.

### ~Quarto()
Os quartos alocados são criados com `new`, então é utilizado o `delete` para a limpeza.

### const Quarto\* criarQuarto(int numero, float valorDiaria)
É criado um quarto com o `número` e `diaria` passados.
O const é utilizado no retorno para evitar alterações indevidas no objeto.
Quando um valor inválido é passado para a criação do quarto um erro é lançado a partir do construtor do `quarto` e quando se tenta criar um quarto que já tenha o número `numero`.

### const Quarto\* getQuarto(int numero)
Retorna o endereço da memória do quarto obtido a partir do `numero` passado.
O const é utilizado para evitar alterações indevidas no objeto.
Um erro é lançado quando o quarto não é encontrado.

### void setStatus(int numero, bool status)
Altera o status do quarto de número `numero` passado.
Caso o quarto não seja encontrado, um erro é lançado.

### void setStatus(const Quarto *quarto, bool status)
Altera o status do quarto passado utilizando `setStatus(int numero, bool status)`

### const bool getStatus(int numero)
Retorna a situação do quarto obtido a partir do `numero`.
Um erro é lançado caso o quarto não seja encontrado.