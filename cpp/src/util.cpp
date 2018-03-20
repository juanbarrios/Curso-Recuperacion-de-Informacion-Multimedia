#include "util.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <sys/stat.h>
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
		}
	}
	if (!capture.isOpened()) {
		std::cout << "no puedo abrir video " << filename << std::endl;
		throw std::runtime_error("no puedo abrir video");
	}
	return capture;
}

void mostrar_frame(const std::string &window_name, const cv::Mat &imagen, bool valorAbsoluto, bool escalarMin0Max255) {
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
