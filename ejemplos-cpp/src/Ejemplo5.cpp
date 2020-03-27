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
#include "utils/util_ui.hpp"

namespace {

int zona_x = 4, zona_y = 20;
int zona_w = 1, zona_h = 1;
int scale_real = 100, scale_imag = 1;

int delta_position = 5;
int delta_scale = 1;

void print_params(const std::string &operacion) {
	std::cout << operacion << " [" << zona_x << ", " << zona_y << "]-["
			<< zona_w << ", " << zona_h << "] -> scale=(" << scale_real << ","
			<< scale_imag << ")" << std::endl;
}
void modificar_param(char key, char key_subir, char key_bajar, int &parametro,
		int delta, const std::string &nombre) {
	if (key == key_subir) {
		parametro += delta;
		print_params("+" + nombre);
	} else if (key == key_bajar) {
		if (parametro - delta > 0)
			parametro -= delta;
		print_params("-" + nombre);
	}
}

void modificarFrecuencias(cv::Mat &frec_complex) {
	//ciclo sobre un rango de frecuencias
	for (int i = zona_y; i < zona_y + zona_h; ++i) {
		for (int j = zona_x; j < zona_x + zona_w; ++j) {
			//obtener el peso de esa frecuencia
			cv::Vec2f complex_value = frec_complex.at<cv::Vec2f>(i, j);
			//modificar el peso
			complex_value[0] *= scale_real;
			complex_value[1] *= scale_imag;
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
void usar_key(char key) {
	modificar_param(key, 'a', 'z', zona_x, delta_position, "x");
	modificar_param(key, 's', 'x', zona_y, delta_position, "y");
	modificar_param(key, 'd', 'c', zona_w, delta_position, "w");
	modificar_param(key, 'f', 'v', zona_h, delta_position, "h");
	modificar_param(key, 'i', 'k', scale_real, delta_scale, "real");
	modificar_param(key, 'o', 'l', scale_imag, delta_scale, "imag");
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
		cv::idft(frecuencias_complex, output_frame,
				cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
		//mostrar la imagen resultante
		output_frame.convertTo(output_frame_gris, CV_8U);
		cv::imshow("OUTPUT", output_frame_gris);
		//esperar por una tecla
		char key = cv::waitKey(1) & 0xFF;
		if (key == ' ')
			key = cv::waitKey(0) & 0xFF;
		if (key == 'q' or key == 27)
			break;
		usar_key(key);
	}
	capture.release();
	cv::destroyAllWindows();
}

}

int main(int argc, char **argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		std::cout << "Ejemplo 5 DFT" << std::endl;
		std::cout << "Uso: " << args[0] << " [video_filename | webcam_id]"
				<< std::endl;
		std::cout << "[a,z] [s,x] [d,c] [f,v] -> ajuste del rectangulo"
				<< std::endl;
		std::cout << "[i,k] -> modificar parte real" << std::endl;
		std::cout << "[o,l] -> modificar parte imaginaria" << std::endl;
		std::string filename = "";
		if (args.size() >= 2) {
			filename = args[1];
		} else {
			filename = ui_select_video();
		}
		ejemplo(filename);
	} catch (const std::exception &ex) {
		std::cout << "Ha ocurrido un ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cout << "Ha ocurrido ERROR desconocido" << std::endl;
	}
	return 0;
}

