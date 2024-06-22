# Estadia

## Atributos

- `unsigned int codigo`
- `time_t dataEntrada`
- `time_t dataSaida`
- `int diarias`
- `int codigoCliente`
- `int numeroDoQuarto`

> `dataDeSaida` > `dataDeEntrada`

## Métodos

### Estadia(unsigned int codigo, std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto)

Construtor da classe que inicializa os atributos com os valores passados como parâmetros. `dataEntrada` e `dataSaida` são processadas para incluir horas específicas (14:00:00 para entrada e 12:00:00 para saída) e calcular o número de diárias.
Caso a `dataSaida` seja menor ou igual à `dataEntrada`, uma exceção é lançada.
Caso alguma das datas passadas sejam inválidas um exceção é lançada.

### const int getDiarias() const

Retorna o número de diárias da estadia.

# Estadias

## Atributos

- `std::vector<Estadia*> estadias`
- `unsigned int nextCode`

## Métodos

### Estadias()

Construtor da classe que inicializa o vetor de estadias como vazio e o `nextCode` como 0.

### ~Estadias()

Destrutor da classe que libera a memória alocada para as estadias.

### bool _checkEstadia(Estadia* novaEstadia)

Checa se uma nova estadia pode ser adicionada verificando se um quarto vai estar ocupado na data indicada de `novaEstadia`.

### const Estadia* agendarEstadia(std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto)

Agrega uma nova estadia ao vetor de estadias com os valores fornecidos e retorna um ponteiro const(evitar alterações indevidas na estadia) para a nova estadia.
Caso algum problema tenha ocorrido(como datas conflitantes) o valor de `nullptr` é retornado.