#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"

void ejemplo(const std::string &filename, int sigma1, int sigma2, double threshold) {
	cv::VideoCapture capture = abrir_video(filename);
	cv::Mat frame, frame_gris, blur1, blur2, frame_diff, frame_noneg, frame_bin;
	while (capture.grab()) {
		if (!capture.retrieve(frame))
			continue;
		//convertir a gris
		cv::cvtColor(frame, frame_gris, cv::COLOR_BGR2GRAY);
		cv::imshow("VIDEO", frame_gris);
		//calcular DoG
		cv::GaussianBlur(frame_gris, blur1, cv::Size(sigma1, sigma1), 0, 0);
		cv::GaussianBlur(frame_gris, blur2, cv::Size(sigma2, sigma2), 0, 0);
		cv::subtract(blur1, blur2, frame_diff, cv::noArray(), CV_32F);
		mostrar_frame("Diff", frame_diff, false, true);
		cv::threshold(frame_diff, frame_bin, threshold, 255, cv::THRESH_BINARY);
		mostrar_frame("BIN", frame_bin, false, true);
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
		std::cout << "Ejemplo 4 Difference of Gaussians" << std::endl;
		if (args.size() != 5) {
			std::cout << "Uso: " << args[0] << " [video_filename | webcam_id] [sigma1] [sigma2] [threshold]" << std::endl;
			return 1;
		}
		std::string filename = args[1];
		int sigma1 = parse_int(args[2]);
		int sigma2 = parse_int(args[3]);
		double threshold = parse_double(args[4]);
		ejemplo(filename, sigma1, sigma2, threshold);
	} catch (const std::exception& ex) {
		std::cout << "Ha ocurrido un ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cout << "Ha ocurrido ERROR desconocido" << std::endl;
	}
	return 0;
}
