#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.inl.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

#include "utils/util_files.hpp"
#include "utils/util_opencv.hpp"
#include "utils/util_strings.hpp"

namespace {

std::random_device r;
std::default_random_engine e1(r());
std::uniform_int_distribution<int> uniform_dist(100, 240);

cv::Scalar getLineColor() {
	//return cv::Scalar(0, 255, 255);
	int r = uniform_dist(e1);
	int g = uniform_dist(e1);
	int b = uniform_dist(e1);
	return cv::Scalar(b, g, r);
}

double sumar_magnitud_vectores(const cv::Mat &flow) {
	double total = 0;
	for (int y = 0; y < flow.rows; ++y) {
		for (int x = 0; x < flow.cols; ++x) {
			const cv::Point2f &f = flow.at<cv::Point2f>(y, x);
			total += std::abs(f.x) + std::abs(f.y);
		}
	}
	return round(total / 1000);
}

const int step = 3;

void dibujarVectores(const cv::Mat &flow, cv::Mat &imgFlow) {
	for (int y = 0; y < flow.rows; y += step)
		for (int x = 0; x < flow.cols; x += step) {
			const cv::Point2f &f = flow.at<cv::Point2f>(y, x);
			int fx = std::round(f.x);
			int fy = std::round(f.y);
			if (std::abs(fx) < step && std::abs(fy) < step)
				continue;
			cv::line(imgFlow, cv::Point(x, y), cv::Point(x + fx, y + fy),
					getLineColor(), 1);
			//cv::circle(imgFlow, cv::Point(x, y), 3, color, -1);
		}
}

void ejemplo(const std::string &filename) {
	cv::VideoCapture capture = abrir_video(filename);
	cv::Mat frame, gris, current, previous, flow, imgFlow;
	int cont = -1;
	for (;;) {
		char c = cv::waitKey(1);
		if (c == 'q' || c == 27) {
			std::cout << "exit!" << std::endl;
			break;
		} else if (c == ' ') {
			c = cv::waitKey(0);
		} else if (!capture.grab() || !capture.retrieve(frame)
				|| frame.empty()) {
			std::cout << "video end!" << std::endl;
			cv::waitKey(0);
			break;
		}
		cont++;
		//if (cont % 10 != 0)
		//	continue;
		cv::cvtColor(frame, gris, cv::COLOR_BGR2GRAY);
		cv::resize(gris, current, cv::Size(0, 0), 0.5, 0.5, cv::INTER_LINEAR);
		if (previous.empty()) {
			current.copyTo(previous);
			continue;
		}
		cv::calcOpticalFlowFarneback(previous, current, flow, 0.99, 1, 5, 20,
				5, 1.1, 0);
		std::cout << "frame=" << cont << "  suma="
				<< sumar_magnitud_vectores(flow) << std::endl;
		cv::cvtColor(current, imgFlow, cv::COLOR_GRAY2BGR);
		//imgFlow = 0;
		dibujarVectores(flow, imgFlow);
		cv::imshow("FLOW", imgFlow);
		current.copyTo(previous);
	}
}

}

int main(int argc, char **argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		std::cout << "Ejemplo 7 OPTICAL FLOW" << std::endl;
		if (args.size() != 2) {
			std::cout << "Uso: " << args[0] << " [video_filename | webcam_id]"
					<< std::endl;
			return 1;
		}
		std::string filename = args[1];
		ejemplo(filename);
	} catch (const std::exception &ex) {
		std::cout << "Ha ocurrido un ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cout << "Ha ocurrido ERROR desconocido" << std::endl;
	}
	return 0;
}
