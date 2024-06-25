#ifndef FILES_HPP
#define FILES_HPP

#include <fstream>

class FileHandler {
private:
	std::fstream stream;
	std::string path;
public:
	FileHandler(std::string path);

	int open();
	int open(std::ios::openmode pos);
	int close();

	bool isEOF();

	int clear();
	int write(void *data, size_t size);
	int write(std::string &str);
	int read(void *result, size_t size);
	int read(std::string &str);
};

#endif