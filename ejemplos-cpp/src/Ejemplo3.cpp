#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "utils/util_opencv.hpp"
#include "utils/util_strings.hpp"

static int threshold_1 = 210;
static int threshold_2 = 110;
static int delta = 30;

void ejemplo(const std::string &filename) {
	cv::VideoCapture capture = abrir_video(filename);
	cv::Mat frame, frame_gris, frame_canny;
	while (capture.grab()) {
		if (!capture.retrieve(frame))
			continue;
		//convertir a gris
		cv::cvtColor(frame, frame_gris, cv::COLOR_BGR2GRAY);
		cv::imshow("VIDEO", frame_gris);
		//calcular canny
		cv::Canny(frame_gris, frame_canny, threshold_1, threshold_2, 3);
		agregar_texto(frame_canny, frame_canny.cols / 2, 2, "TH=" + std::to_string(threshold_1) + "," + std::to_string(threshold_2));
		mostrar_imagen("CANNY", frame_canny, false, false);
		//esperar por una tecla
		char key = cv::waitKey(1) & 0xFF;
		if (key == ' ')
			key = cv::waitKey(0) & 0xFF;
		if (key == 'q' or key == 27) {
			break;
		} else if (key == 'a') {
			threshold_1 += delta;
		} else if (key == 'z') {
			if (threshold_1 - delta > 0)
				threshold_1 -= delta;
		} else if (key == 's') {
			threshold_2 += delta;
		} else if (key == 'x') {
			if (threshold_2 - delta > 0)
				threshold_2 -= delta;
		}
	}
	capture.release();
	cv::destroyAllWindows();
}

int main(int argc, char** argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		std::cout << "Ejemplo 3 CANNY" << std::endl;
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

