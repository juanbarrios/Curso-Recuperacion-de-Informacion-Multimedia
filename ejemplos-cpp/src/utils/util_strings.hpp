#pragma once

#include <string>
#include <vector>

std::vector<std::string> get_args_vector(int argc, char **argv);

bool print_help(const std::vector<std::string> &args);

int parse_int(const std::string &string);

double parse_double(const std::string &string);

std::string basename(const std::string &filename);
