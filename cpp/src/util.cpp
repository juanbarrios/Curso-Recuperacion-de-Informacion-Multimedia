#include "util.hpp"

#include <dirent.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/stat.h>
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>

std::vector<std::string> get_args_vector(int argc, char** argv) {
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i) {
		args.push_back(std::string(argv[i]));
	}
	return args;
}

int parse_int(const std::string &string) {
	std::size_t next_position = 0;
	int n;
	try {
		n = std::stoi(string, &next_position, 10);
	} catch (...) {
		throw std::logic_error("invalid number \"" + string + "\"");
	}
	if (next_position != string.length())
		throw std::logic_error("invalid number \"" + string + "\"");
	return n;
}

double parse_double(const std::string &string) {
	std::size_t next_position = 0;
	double n;
	try {
		n = std::stod(string, &next_position);
	} catch (...) {
		throw std::logic_error("invalid number \"" + string + "\"");
	}
	if (next_position != string.length())
		throw std::logic_error("invalid number \"" + string + "\"");
	return n;
}

bool existe_archivo(const std::string &filename) {
	struct stat st;
	if (stat(filename.c_str(), &st) == 0)
		return S_ISREG(st.st_mode) ? true : false;
	return false;
}

std::string basename(const std::string &filename) {
	std::size_t pos1 = filename.find_last_of("/\\");
	std::string name = (pos1 == std::string::npos) ? filename : filename.substr(pos1 + 1);
	std::size_t pos2 = name.find_last_of(".");
	return (pos2 == std::string::npos) ? name : name.substr(0, pos2);

}

void mostrar_imagen(const std::string &window_name, const cv::Mat &imagen, bool valorAbsoluto, bool escalarMin0Max255) {
	cv::Mat imagen_abs;
	if (valorAbsoluto) {
		imagen_abs = cv::abs(imagen);
	} else {
		imagen_abs = imagen;
	}
	cv::Mat imagen_norm;
	if (escalarMin0Max255) {
		cv::normalize(imagen_abs, imagen_norm, 0, 255, cv::NORM_MINMAX, CV_8U);
	} else {
		imagen_norm = imagen_abs;
	}
	cv::imshow(window_name, imagen_norm);
}

cv::VideoCapture abrir_video(const std::string &filename) {
	cv::VideoCapture capture;
	if (existe_archivo(filename)) {
		std::cout << "abriendo archivo " << filename << std::endl;
		capture.open(filename);
	} else {
		int id_webcam = parse_int(filename);
		std::cout << "abriendo camara " << id_webcam << std::endl;
		if (capture.open(id_webcam)) {
			//leer el primer frame
			cv::Mat frame;
			capture.read(frame);
			std::cout << "video " << frame.size << std::endl;
		}
	}
	if (!capture.isOpened()) {
		std::cout << "no puedo abrir video " << filename << std::endl;
		throw std::runtime_error("no puedo abrir video");
	}
	return capture;
}

void agregar_texto(cv::Mat &imagen, int center_x, int center_y, const std::string &texto) {
	static int fontFace = cv::FONT_HERSHEY_PLAIN;
	static double fontScale = 1;
	static int thickness = 1;
	int baseline = 0;
	cv::Size textSize = cv::getTextSize(texto, fontFace, fontScale, thickness, &baseline);
	cv::Point p(center_x - textSize.width / 2, center_y + textSize.height);
	cv::Rect rect(p.x - 1, p.y - textSize.height - 1, textSize.width + 2, textSize.height + 2);
	cv::rectangle(imagen, rect, cv::Scalar::all(0), -1);
	cv::putText(imagen, texto, p, fontFace, fontScale, cv::Scalar::all(255), thickness);
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

namespace {
//se usa un namespace anónimo para funciones privadas visibles solo dentro de este archivo

void agregar_archivo(const std::string &dirname, const std::string &name, std::vector<std::string> &list) {
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
		agregar_archivo(dirname, name, list);
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

