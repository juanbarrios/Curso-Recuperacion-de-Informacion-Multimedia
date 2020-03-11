#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "utils/util_opencv.hpp"
#include "utils/util_strings.hpp"

namespace {

int desde_x = 4, desde_y = 20;
int size_x = 8, size_y = 8;
int delta_pos = 5;
int mult_real = 100, mult_imaginaria = 10;
int delta_mult = 2;

void modificar_param(char key, char key_subir, char key_bajar, int &parametro, int delta, const std::string &nombre) {
	if (key == key_subir) {
		parametro += delta;
		std::cout << nombre << "=" << parametro << std::endl;
	} else if (key == key_bajar) {
		if (parametro - delta > 0)
			parametro -= delta;
		std::cout << nombre << "=" << parametro << std::endl;
	}
}

void modificarFrecuencias(cv::Mat &frec_complex) {
	//ciclo sobre un rango de frecuencias
	for (int i = desde_y; i < desde_y + size_y; ++i) {
		for (int j = desde_x; j < desde_x + size_x; ++j) {
			//obtener el peso de esa frecuencia
			cv::Vec2f complex_value = frec_complex.at<cv::Vec2f>(i, j);
			//modificar el peso
			complex_value[0] *= mult_real;
			complex_value[1] *= mult_imaginaria;
			//actualizar el peso de esa frecuencia
			frec_complex.at<cv::Vec2f>(i, j) = complex_value;
		}
	}
}

cv::Mat imagenToComplex(const cv::Mat &gris) {
	//convertir a float
	cv::Mat real;
	gris.convertTo(real, CV_32F);
	//la parte imaginaria son ceros
	cv::Mat imag;
	imag.create(gris.size(), CV_32FC1);
	imag = 0;
	//unir parte real e imaginaria
	cv::Mat planos[] = { real, imag };
	cv::Mat complex;
	cv::merge(planos, 2, complex);
	return complex;
}

void visualizar(const cv::Mat &frec_complex) {
	//separar complejos en parte real e imaginaria
	cv::Mat frec_real;
	cv::Mat frec_imag;
	frec_real.create(frec_complex.size(), CV_32FC1);
	frec_imag.create(frec_complex.size(), CV_32FC1);
	cv::Mat frec_planos[] = { frec_real, frec_imag };
	cv::split(frec_complex, frec_planos);
	//calcular la magnitud
	cv::Mat frec_magnitud;
	cv::magnitude(frec_real, frec_imag, frec_magnitud);
	//calcular log magnitud para visualizar
	cv::Mat frec_logMagnitud;
	cv::log(frec_magnitud + 1, frec_logMagnitud);
	//normalizar y mostrar
	cv::normalize(frec_logMagnitud, frec_logMagnitud, 0, 1, cv::NORM_MINMAX);
	cv::imshow("LogMagnitud", frec_logMagnitud);
}

void ejemplo(const std::string &filename) {
	cv::VideoCapture capture = abrir_video(filename);
	cv::Mat frame, frame_gris, output_frame, output_frame_gris;
	while (capture.grab()) {
		if (!capture.retrieve(frame))
			continue;
		//convertir a gris
		cv::cvtColor(frame, frame_gris, cv::COLOR_BGR2GRAY);
		cv::imshow("VIDEO", frame_gris);
		//convertir la imagen en tipo complejo (2 canales, parte imaginaria=0)
		cv::Mat frame_complex = imagenToComplex(frame_gris);
		//calcular la DFT de la imagen
		cv::Mat frecuencias_complex;
		cv::dft(frame_complex, frecuencias_complex, cv::DFT_COMPLEX_OUTPUT);
		//modificar las frecuencias de la DFT
		modificarFrecuencias(frecuencias_complex);
		//visualizar las frecuencias
		visualizar(frecuencias_complex);
		//invertir la DFT
		cv::idft(frecuencias_complex, output_frame, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
		//mostrar la imagen resultante
		output_frame.convertTo(output_frame_gris, CV_8U);
		cv::imshow("OUTPUT", output_frame_gris);
		//esperar por una tecla
		char key = cv::waitKey(1) & 0xFF;
		if (key == ' ')
			key = cv::waitKey(0) & 0xFF;
		if (key == 'q' or key == 27)
			break;
		modificar_param(key, 'a', 'z', desde_x, delta_pos, "desde_x");
		modificar_param(key, 's', 'x', desde_y, delta_pos, "desde_y");
		modificar_param(key, 'd', 'c', size_x, delta_pos, "size_x");
		modificar_param(key, 'f', 'v', size_y, delta_pos, "size_y");
		modificar_param(key, 'i', 'k', mult_real, delta_mult, "mult_real");
		modificar_param(key, 'o', 'l', mult_imaginaria, delta_mult, "mult_imaginaria");
	}
	capture.release();
	cv::destroyAllWindows();
}

}

int main(int argc, char** argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		std::cout << "Ejemplo 5 DFT" << std::endl;
		if (args.size() != 2) {
			std::cout << "Uso: " << args[0] << " [video_filename | webcam_id]" << std::endl;
			return 1;
		}
		std::string filename = args[1];
		ejemplo(filename);
	} catch (const std::exception& ex) {
		std::cout << "Ha ocurrido un ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cout << "Ha ocurrido ERROR desconocido" << std::endl;
	}
	return 0;
}

