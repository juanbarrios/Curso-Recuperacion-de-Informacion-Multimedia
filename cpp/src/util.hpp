#ifndef UTIL_HPP
#define UTIL_HPP

#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

std::vector<std::string> get_args_vector(int argc, char** argv);

int parse_int(const std::string &string);

double parse_double(const std::string &string);

bool existe_archivo(const std::string &filename);

std::string basename(const std::string &filename);

void mostrar_frame(const std::string &window_name, const cv::Mat &imagen, bool valorAbsoluto, bool escalarMin0Max255);

cv::VideoCapture abrir_video(const std::string &filename);

std::vector<std::string> leer_lineas_archivo(const std::string &filename);

#endif
