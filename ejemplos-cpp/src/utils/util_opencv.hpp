#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

void mostrar_imagen(const std::string &window_name, const cv::Mat &imagen,
		bool valorAbsoluto, bool escalarMin0Max255);

cv::VideoCapture abrir_video(const std::string &filename);

void agregar_texto(cv::Mat &imagen, int center_x, int center_y,
		const std::string &texto);
