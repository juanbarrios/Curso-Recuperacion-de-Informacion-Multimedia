#include "util_opencv.hpp"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdexcept>
#include "util_files.hpp"
#include "util_strings.hpp"

void mostrar_imagen(const std::string &window_name, const cv::Mat &imagen,
		bool valorAbsoluto, bool escalarMin0Max255) {
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
			std::cout << "video " << frame.size << std::endl;
		}
	}
	if (!capture.isOpened()) {
		std::cout << "no puedo abrir video " << filename << std::endl;
		throw std::runtime_error("no puedo abrir video");
	}
	return capture;
}

void agregar_texto(cv::Mat &imagen, int center_x, int center_y,
		const std::string &texto) {
	static int fontFace = cv::FONT_HERSHEY_PLAIN;
	static double fontScale = 1;
	static int thickness = 1;
	int baseline = 0;
	cv::Size textSize = cv::getTextSize(texto, fontFace, fontScale, thickness,
			&baseline);
	cv::Point p(center_x - textSize.width / 2, center_y + textSize.height);
	cv::Rect rect(p.x - 1, p.y - textSize.height - 1, textSize.width + 2,
			textSize.height + 2);
	cv::rectangle(imagen, rect, cv::Scalar::all(0), -1);
	cv::putText(imagen, texto, p, fontFace, fontScale, cv::Scalar::all(255),
			thickness);
}

