# Estadia

## Atributos

- `unsigned int codigo`
- `time_t dataEntrada`
- `time_t dataSaida`
- `int diarias`
- `const Cliente* cliente`
- `const Quarto* quarto`

> `dataDeSaida` > `dataDeEntrada`

## Métodos

### Estadia(unsigned int codigo, std::string dataEntrada, std::string dataSaida, unsigned int codigoCliente, unsigned int numeroDoQuarto)

Construtor da classe que inicializa os atributos com os valores passados como parâmetros. `dataEntrada` e `dataSaida` são processadas para incluir horas específicas (14:00:00 para entrada e 12:00:00 para saída) e calcular o número de diárias.

Caso a `dataSaida` seja menor ou igual à `dataEntrada`, uma exceção é lançada.

Caso alguma das datas passadas sejam inválidas um exceção é lançada.

Os códigos de cliente e quarto são usados nos respectivos handlers para pegar os objetos dos mesmos.

### const uint getCodigo() const

Retorna o `codigo`.

### const int getDiarias() const

Retorna o número de diárias da estadia.

### const Cliente *getCliente() const

Retorna um ponteiro readonly para o cliente que foi cadastrado na estadia.

### const Quarto *getQuarto() const

Retorna um ponteiro readonly para o quarto que foi cadastrado na estadia.

### const time_t getCheckInDate const

Retorna a `dataEntrada` como readonly.

### const time_t getCheckOutDate const

Retorna a `dataSaida` como readonly.

# Estadias

## Atributos

- `std::vector<Estadia*> estadias`
- `unsigned int nextCode`
- `FileHandler fileHandler`

## Métodos

Métodos com "_" no inicio do nome demonstram que são privados.

### Estadias()

Construtor da classe que inicializa o vetor de estadias como vazio e o `nextCode` como 0.

### ~Estadias()

Destrutor da classe que libera a memória alocada para as estadias.

### void load()

Carrega as estadias lidas do arquivo `data/estadias.bin`.

### bool _checkEstadia(Estadia* novaEstadia)

Checa se uma nova estadia pode ser adicionada verificando se um quarto vai estar ocupado na data indicada de `novaEstadia`.

### float _darBaixa(Estadia *estadia)

Verifica se a data atual está entre o dia de check-in e o dia de check-out da `estadia` passada e caso esteja altera o status do quarto da estadia para desocupado.

Contabiliza os pontos de fidelidade do cliente passanda as diarias.

E retorna o valor a ser cobrado pela estadia.

### Estadia *_getEstadia(unsigned int code);

Busca no atributo `estadias` por uma estadia com o código igual ao `code` passado.

Caso encontre retorna o ponteiro da estadia.

Caso não encontre retorn `nullptr`.

### Estadia *_loadEstadia(unsigned int code, time_t checkInDate, time_t checkOutDate, unsigned int clientCode, unsigned int roomNumber)

Utilizado pelo `load()` para carregar dos arquivos uma estadia.

### const Estadia* agendarEstadia(std::string dataEntrada, std::string dataSaida, int codigoCliente, int numeroDoQuarto)

Registra uma nova estadia ao vetor de estadias com os valores fornecidos e retorna um ponteiro const(evitar alterações indevidas na estadia) para a nova estadia. Também altera o status do quarto para ocupado.

Caso algum problema tenha ocorrido(como a `dataDeEntrada` anterior ao dia atual ou datas conflitantes) um erro correspondente é lançado.

### float darBaixa(unsigned int code)

Combina `_getEstadia` com `_darBaixa` para dar baixa na estadia com o código passado.

Retorna o custo da estadia.

### const Estadia *getEstadia(unsigned int code)

A mesma funcionalidade de _getEstadia, porém público com retorno como somente leitura.

### const std::vector<Estadia*> getEstadia(std::string date)

Retorna o vetor `estadias` filtrado com base na `date` passada, verificando se está no range [checkInDate, checkOutDate].

### const std::vector<Estadia*> getEstadias(unsigned int clientCode)

Retorna o vetor `estadias` filtrado com base no `clientCode` passado, verificando se a estadia pertence ao cliente.

### const std::vector<Estadia*> getEstadias(std::vector<unsigned int> codes)

Retorna o vetor `estadias` filtrado com base se algum codigo no vetor `codes` passado combina com o código do cliente da estadia.

### const std::vector<Estadia*> getEstadiasByRoom(unsigned int roomNumber)

Retorna o vetor `estadias` filtrado com base no `roomNumber` passado.

### const bool isAvaliable(unsigned int roomNumber, time_t checkIn, time_t checkOut)

Verificar se o quarto de número `roomNumber` está disponível para estadia no período de `checkIn` à `checkOut`.