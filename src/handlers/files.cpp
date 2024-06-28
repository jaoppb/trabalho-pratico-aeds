#include "files.hpp"

/*
 * Construtor da classe FileHandler
 * 
 * Lança um erro caso `path` seja "".
 * 
 * @param std::string path
 * 
 * @throw std::runtime_error
 */
FileHandler::FileHandler(std::string path): path(path) {
	if(path.size() == 0) throw std::runtime_error("O caminho do arquivo precisa ser provido");
}

/*
 * Verifica se o próximo char é o final do arquivo ou
 * se já foi realizado uma tentativa de ler o final do arquivo
 * 
 * @return bool
 */
bool FileHandler::isEOF() { return this->stream.peek() == EOF || this->stream.eof(); }

/*
 * Abre o arquivo para operações binárias
 * 
 * @returns  1 caso já esteja aberto
 * @returns -1 caso a operação tenha falhado
 * 
 * @return int
 */
int FileHandler::open() {
	if(this->stream.is_open()) return 1;
	try {
		this->stream.open(this->path, std::ios::in | std::ios::out | std::ios::binary);
	} catch(...) {
		return -1;
	}
	return this->stream.fail();
}

/*
 * Abre o arquivo na posição `pos`
 *
 * Valores válidos para `pos`:
 *  - std::ios::app
 *  - std::ios::ate
 *  - std::ios::trunc
 * 
 * @param std::ios::openmode pos
 */
int FileHandler::open(std::ios::openmode pos) {
	if (pos != std::ios::app &&
		pos != std::ios::ate &&
		pos != std::ios::trunc) throw std::runtime_error("Posição de abertura do arquivo inválida");
	if(this->stream.is_open()) return 1;
	try {
		this->stream.open(this->path, pos | std::ios::in | std::ios::out | std::ios::binary);
	} catch(...) {
		return -1;
	}
	return this->stream.fail();
}

/*
 * Fechar o arquivo e salva as alterações
 * 
 * @returns  1 caso já esteja fechado
 * @returns -1 caso a operação tenha falhado
 * @returns  0 caso sucedido
 * 
 * @return int
 */
int FileHandler::close() {
	if(!this->stream.is_open()) return 1;
	try {
		this->stream.close();
	} catch(...) {
		return -1;
	}
	return 0;
}

/*
 * Limpa o arquivo
 * 
 * @return int
 */
int FileHandler::clear() {
	if(this->stream.is_open()) this->close();
	this->open(std::ios::trunc);
	this->close();
	return this->stream.fail();
}

/*
 * Escreve em formato binário os dados do ponteiro `data` passado
 * de tamanho `size`, em bytes
 * 
 * @param void   *data
 * @param size_t  size
 * 
 * @return int
 */
int FileHandler::write(void *data, size_t size) {
	this->stream.write(reinterpret_cast<char*>(data), size);
	return this->stream.bad();
}

/*
 * Lê `size` bytes do arquivo e armazena em `result`
 *
 * @param void   *result
 * @param size_t  size
 */
int FileHandler::read(void *result, size_t size) {
	this->stream.read(reinterpret_cast<char*>(result), size);
	return this->stream.bad();
}

/*
 * Tenta ler uma string armazenada no arquivo no formato `length``string`
 * Caso o próximo dado não seja uma string, resultados inesperados irão ocorrer.
 * 
 * Lê quantos bytes a string tem(previamente armazenado no arquivo)
 * Lê os próximos bytes referentes à string e os armazena na `string`
 * 
 * @param std::string &string
 * 
 * @return int
 */
int FileHandler::read(std::string &string) {
	size_t len = 0;
	if(this->read((void*)&len, sizeof(len))) len = 0;
	
	char temp[len + 1];
	this->read((void*)&temp, len);

	temp[len] = '\0';
	string.assign(temp);
	return this->stream.bad();
}

/*
 * Escreve uma string no arquivo
 *
 * Escreve o tamanho da string em seguida a string.
 * 
 * @return int
 */
int FileHandler::write(std::string &str) {
	size_t len = str.size();
	this->write((void*)&len, sizeof(len));
	this->write((void*)str.c_str(), len);
	return this->stream.bad();
}