#include "files.hpp"

FileHandler::FileHandler(std::string path): path(path) {
	if(path.size() == 0) throw std::runtime_error("O caminho do arquivo precisa ser provido");
}

bool FileHandler::isEOF() { return this->stream.peek() == EOF || this->stream.eof(); }

int FileHandler::open() {
	if(this->stream.is_open()) return 1;
	try {
		this->stream.open(this->path, std::ios::in | std::ios::out | std::ios::binary);
	} catch(...) {
		return -1;
	}
	return this->stream.fail();
}

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

int FileHandler::close() {
	if(!this->stream.is_open()) return 1;
	try {
		this->stream.close();
	} catch(...) {
		return -1;
	}
	return 0;
}

int FileHandler::clear() {
	if(this->stream.is_open()) this->close();
	this->open(std::ios::trunc);
	this->close();
	return this->stream.fail();
}

int FileHandler::write(void *data, size_t size) {
	this->stream.write(reinterpret_cast<char*>(data), size);
	return this->stream.bad();
}

int FileHandler::read(void *result, size_t size) {
	this->stream.read(reinterpret_cast<char*>(result), size);
	return this->stream.bad();
}

int FileHandler::read(std::string &string) {
	size_t len = 0;
	if(this->read((void*)&len, sizeof(len))) len = 0;
	
	char temp[len + 1];
	this->read((void*)&temp, len);

	temp[len] = '\0';
	string.assign(temp);
	return this->stream.bad();
}

int FileHandler::write(std::string &str) {
	size_t len = str.size();
	this->write((void*)&len, sizeof(len));
	this->write((void*)str.c_str(), len);
	return this->stream.bad();
}