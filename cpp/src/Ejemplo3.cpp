#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"

void ejemplo(const std::string &filename, double threshold_1, double threshold_2) {
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
		cv::imshow("CANNY", frame_canny);
		//esperar por una tecla
		char key = cv::waitKey(1) & 0xFF;
		if (key == ' ')
			key = cv::waitKey(0) & 0xFF;
		if (key == 'q' or key == 27)
			break;
	}
	capture.release();
	cv::destroyAllWindows();
}

int main(int argc, char** argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		std::cout << "Ejemplo 3 CANNY" << std::endl;
		if (args.size() != 4) {
			std::cout << "Uso: " << args[0] << " [video_filename | webcam_id] [canny_threshold_1] [canny_threshold_2]" << std::endl;
			return 1;
		}
		std::string filename = args[1];
		double canny_threshold_1 = parse_double(args[2]);
		double canny_threshold_2 = parse_double(args[3]);
		ejemplo(filename, canny_threshold_1, canny_threshold_2);
	} catch (const std::exception& ex) {
		std::cout << "Ha ocurrido un ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cout << "Ha ocurrido ERROR desconocido" << std::endl;
	}
	return 0;
}

