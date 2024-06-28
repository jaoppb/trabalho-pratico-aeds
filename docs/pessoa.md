# Pessoa

## Atributos

- `unsigned int telefone`
- `unsigned int codigo`
- `std::string nome`

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

# Pessoas

## Atributos

- `std::vector<Pessoa\*> pessoas`
- `unsigned int nextCode`
- `FileHandler fileHandler`

## Métodos

### Pessoas(bool load)

Chama o método `load()` caso `load` seja `true`.

### ~Pessoas()

Armazena os dados do vetor `pessoas` no arquivo `data/pessoas.bin`.

### void load()

Carrega os funcionários e os cliente no vetor `pessoas`.

### Pessoa *_getPessoa(unsigned int code)

Método interno para obter uma pessoa do vetor `pessoas` com base no `code`.

### Cliente *_getCliente(unsigned int code)

Método interno para obter um cliente do vetor `pessoas` com base no `code`.

### Funcionario *_getFuncionario(unsigned int code)

Método interno para obter um funcionário do vetor `pessoas` com base no `code`.

### Cliente *_loadCliente(unsigned int code, std::string telefone, std::string nome, std::string endereco, unsigned int pontos)

Método utilizado pelo `load()` para carregar os clientes lidos.

### Funcionario *_loadFuncionario(unsigned int code, std::string telefone, std::string nome, std::string cargo, float salario)

Método utilizaod pelo `load()` para carregar os funcionario lidos.

### const size_t getTotal()

Retorna o tamanho do vetor `pessoas`.

### const size_t getTotalClients()

Retorna quantos clientes existem no vetor `pessoas`.

### const size_t getTotalEmployes()

Retorna quantos funcionários existem no vetor `pessoas`.

### const Cliente *cadastrarCliente (std::string telefone, std::string nome, std::string endereco, unsigned int pontos);

Realiza o cadastro de um cliente e o salva no vetor `pessoas`.

### const Funcionario *cadastrarFuncionaro(std::string telefone, std::string nome std::string cargo, float salario);

Realiza o cadastro de um funcionário e o salva no vetor `pessoas`.

### const Pessoa *getPessoa (unsigned int code) const;

Retorna a pessoa com código `code` caso seja encontrada, caso contrário retorna `nullptr`.

### const Cliente *getCliente (unsigned int code) const;

Retorna o cliente com código `code` caso seja encontrado, caso contrário retorna `nullptr`.

### const Funcionario *getFuncionario(unsigned int code) const;

Retorna o funcionário com código `code` caso seja encontrado, caso contrário retorna `nullptr`.

### const std::vector<Pessoa*> getPessoa (std::string name) const;

Retorna um vetor de pessoas cujo os nomes tenham a substring `name`.

Caso não encontre ninguém, retorna um vetor vazio.

### const std::vector<Cliente*> getCliente (std::string name) const;

Retorna um vetor de clientes cujo os nomes tenham a substring `name`.

Caso não encontre ninguém, retorna um vetor vazio.

### const std::vector<Funcionario*> getFuncionario(std::string name) const;

Retorna um vetor de funcionários cujo os nomes tenham a substring `name`.

Caso não encontre ninguém, retorna um vetor vazio.

### void addPontos(const Cliente *cliente, int diarias) const;

Adiciona pontos para o cliente passado com base no número de diárias.

São 10 pontos por diária.

Caso o número seja negativo, um erro `std::invalid_argument` é lançado.