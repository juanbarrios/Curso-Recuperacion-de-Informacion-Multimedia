#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"

void ejemplo(const std::string &filename) {
	std::cout << "abriendo " << filename << std::endl;
	cv::Mat imagen_color = cv::imread(filename, cv::IMREAD_COLOR);
	if (!imagen_color.data) {
		std::cout << "no puedo abrir imagen " << filename << std::endl;
		return;
	}
	cv::Mat imagen_gris;
	cv::cvtColor(imagen_color, imagen_gris, cv::COLOR_BGR2GRAY);
	cv::Mat imagen_bin;
	int threshold = cv::threshold(imagen_gris, imagen_bin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	std::string window_name = basename(filename);
	cv::imshow(window_name, imagen_color);
	cv::imshow(window_name + " GRIS", imagen_gris);
	agregar_texto(imagen_bin, imagen_bin.cols / 2, 2, "OTSU=" + std::to_string(threshold));
	cv::imshow(window_name + " BINARIA", imagen_bin);
	std::cout << window_name << ": size=" << imagen_color.size() << " threshold_otsu=" << threshold << std::endl;
}

int main(int argc, char** argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		std::cout << "Ejemplo 1 OTSU" << std::endl;
		if (args.size() < 2) {
			std::cout << "Uso: " << args[0] << " [filename]" << std::endl;
			return 1;
		}
		for (std::size_t i = 1; i < args.size(); ++i) {
			std::string filename = args[i];
			ejemplo(filename);
		}
		std::cout << "Presione una tecla para salir..." << std::endl;
		cv::waitKey(0);
		cv::destroyAllWindows();
	} catch (const std::exception& ex) {
		std::cout << "Ha ocurrido un ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cout << "Ha ocurrido ERROR desconocido" << std::endl;
	}
	return 0;
}
