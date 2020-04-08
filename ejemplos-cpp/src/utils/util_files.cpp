#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>

namespace {
//se usa un namespace anónimo para funciones privadas visibles solo dentro de este archivo

void agregar_filename(const std::string &dirname, const std::string &name,
		std::vector<std::string> &list) {
	std::string fullpath = dirname + "/" + name;
#if defined WIN32 || defined _WIN32
	struct stat64 st;
	int status = stat64(fullpath.c_str(), &st);
#elif defined __linux || defined __linux__
	struct stat st;
	int status = stat(fullpath.c_str(), &st);
#endif
	if (status == 0 && S_ISREG(st.st_mode)) {
		list.push_back(fullpath);
	}
}

}

bool existe_archivo(const std::string &filename) {
	struct stat st;
	if (stat(filename.c_str(), &st) == 0)
		return S_ISREG(st.st_mode) ? true : false;
	return false;
}

std::vector<std::string> listar_archivos(const std::string &dirname) {
	std::vector<std::string> list;
#if defined WIN32 || defined _WIN32
	DIR *dp = opendir(dirname.c_str());
	if (dp == NULL) {
		std::cout << "error abriendo " << dirname << std::endl;
		return list;
	}
	struct dirent *dir_entry;
	while ((dir_entry = readdir(dp)) != NULL) {
		std::string name(dir_entry->d_name);
		agregar_filename(dirname, name, list);
	}
	if (closedir(dp) != 0) {
		std::cout << "error cerrando " << dirname << std::endl;
	}
#elif defined __linux || defined __linux__
	struct dirent **namelist = NULL;
	int len = scandir(dirname.c_str(), &namelist, NULL, NULL);
	if (len < 0) {
		std::cout << "error abriendo " << dirname << std::endl;
		return list;
	}
	for (int i = 0; i < len; ++i) {
		std::string name(namelist[i]->d_name);
		agregar_archivo(dirname, name, list);
		free(namelist[i]);
	}
	free(namelist);
#endif
	std::sort(list.begin(), list.end());
	return list;
}

std::vector<std::string> leer_lineas_archivo(const std::string &filename) {
	std::vector<std::string> lines;
	std::ifstream infile;
	infile.open(filename);
	if (!infile.is_open()) {
		std::cout << "no puedo abrir " << filename << std::endl;
		return lines;
	}
	while (!infile.eof()) {
		std::string line;
		std::getline(infile, line, '\n');
		lines.push_back(line);
	}
	return lines;
}

