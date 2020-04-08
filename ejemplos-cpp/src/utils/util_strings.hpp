#pragma once

#include <string>
#include <vector>

std::vector<std::string> get_args_vector(int argc, char **argv);

int parse_int(const std::string &string);

double parse_double(const std::string &string);

std::string basename(const std::string &filename);

std::string filename_sin_extension(const std::string &filename);
