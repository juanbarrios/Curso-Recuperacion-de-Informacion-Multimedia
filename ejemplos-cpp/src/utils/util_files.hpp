#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

bool existe_archivo(const std::string &filename);

std::vector<std::string> listar_archivos(const std::string &dirname);

std::vector<std::string> leer_lineas_archivo(const std::string &filename);

template<typename T>
std::vector<T> leer_bytes_archivo(const std::string &filename) {
	//abrir el archivo
	std::ifstream infile;
	infile.open(filename);
	if (!infile.is_open())
		throw std::runtime_error("no puedo abrir " + filename);
	//ir al final
	infile.seekg(0, std::ios::end);
	//obtener la posicion en bytes
	int numBytes = infile.tellg();
	//volver al inicio
	infile.seekg(0, std::ios::beg);
	//leer todos los bytes del archivo
	if ((numBytes % sizeof(T)) != 0)
		throw std::runtime_error("no cuadran los bytes");
	std::vector<T> vector;
	vector.resize(numBytes / sizeof(T));
	infile.read(reinterpret_cast<char*>(vector.data()), numBytes);
	if (infile.bad())
		throw std::runtime_error("error leyendo " + filename);
	return vector;
}
