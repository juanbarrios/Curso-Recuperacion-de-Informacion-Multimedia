#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "utils/util_opencv.hpp"
#include "utils/util_strings.hpp"

static int delta = 5;
static int sobel_threshold = 21;

void ejemplo(const std::string &filename) {
	cv::VideoCapture capture = abrir_video(filename);
	cv::Mat frame, frame_gris, sobelX, sobelY, sobelX2, sobelY2;
	cv::Mat magnitud, magnitud_aprox, bordes, bordes_aprox;
	while (capture.grab()) {
		if (!capture.retrieve(frame))
			continue;
		//convertir a gris
		cv::cvtColor(frame, frame_gris, cv::COLOR_BGR2GRAY);
		cv::imshow("VIDEO", frame_gris);
		//calcular filtro de sobel
		cv::Sobel(frame_gris, sobelX, CV_32F, 1, 0, 3);
		cv::Sobel(frame_gris, sobelY, CV_32F, 0, 1, 3);
		mostrar_imagen("X", sobelX, true, true);
		mostrar_imagen("Y", sobelY, true, true);
		//magnitud del gradiente
		cv::multiply(sobelX, sobelX, sobelX2);
		cv::multiply(sobelY, sobelY, sobelY2);
		cv::sqrt(sobelX2 + sobelY2, magnitud);
		mostrar_imagen("MAGNITUD GRADIENTE", magnitud, false, true);
		//aproximacion de la magnitud del gradiente
		magnitud_aprox = cv::abs(sobelX) + cv::abs(sobelY);
		mostrar_imagen("APROX GRADIENTE", magnitud_aprox, false, true);
		//umbral sobre la magnitud del gradiente
		cv::threshold(magnitud, bordes, sobel_threshold, 255, cv::THRESH_BINARY);
		agregar_texto(bordes, bordes.cols / 2, 2, "TH=" + std::to_string(sobel_threshold));
		mostrar_imagen("BORDES", bordes, false, false);
		//esperar por una tecla
		char key = cv::waitKey(1) & 0xFF;
		if (key == ' ')
			key = cv::waitKey(0) & 0xFF;
		if (key == 'q' or key == 27)
			break;
		else if (key == 'a')
			sobel_threshold += delta;
		else if (key == 'z')
			if (sobel_threshold - delta > 0)
				sobel_threshold -= delta;
	}
	capture.release();
	cv::destroyAllWindows();
}

int main(int argc, char** argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		std::cout << "Ejemplo 2 SOBEL" << std::endl;
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
