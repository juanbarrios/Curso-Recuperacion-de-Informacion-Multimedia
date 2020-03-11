#include <opencv2/core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "utils/util_opencv.hpp"
#include "utils/util_strings.hpp"
#include "utils/util_ui.hpp"

void procesar_imagen(const std::string &filename) {
	std::cout << "abriendo " << filename << std::endl;
	cv::Mat imagen_color = cv::imread(filename, cv::IMREAD_COLOR);
	if (imagen_color.empty()) {
		std::cout << "no puedo abrir imagen " << filename << std::endl;
		return;
	}
	cv::Mat imagen_gris;
	cv::cvtColor(imagen_color, imagen_gris, cv::COLOR_BGR2GRAY);
	cv::Mat imagen_bin;
	int threshold = cv::threshold(imagen_gris, imagen_bin, 0, 255,
			cv::THRESH_BINARY | cv::THRESH_OTSU);
	std::string window_name = basename(filename);
	cv::imshow(window_name, imagen_color);
	agregar_texto(imagen_bin, imagen_bin.cols / 2, 2,
			"OTSU=" + std::to_string(threshold));
	cv::imshow(window_name + " BINARIA", imagen_bin);
	std::cout << window_name << ": size=" << imagen_color.size()
			<< " threshold_otsu=" << threshold << std::endl;
}
void procesar_archivos(std::vector<std::string> filenames) {
	if (filenames.size() == 0)
		filenames = ui_select_filenames();
	if (filenames.size() == 0)
		return;
	for (std::string filename : filenames)
		procesar_imagen(filename);
	std::cout << "Presione una tecla..." << std::endl;
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void procesar(const std::vector<std::string> &args) {
	std::cout << "CC5213 - Ejemplo 1 OTSU" << std::endl;
	std::cout << "Usando OpenCV " << CV_VERSION << std::endl;
	if (print_help(args)) {
		std::cout << "  Uso: " << basename(args[0]) << " [filenames]"
				<< std::endl;
	} else {
		std::vector<std::string> filenames(args.begin() + 1, args.end());
		procesar_archivos(filenames);
	}
	std::cout << "fin" << std::endl;
}

int main(int argc, char **argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		procesar(args);
	} catch (const std::exception &ex) {
		std::cout << "Ha ocurrido un ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cout << "Ha ocurrido ERROR desconocido" << std::endl;
	}
	return 0;
}
