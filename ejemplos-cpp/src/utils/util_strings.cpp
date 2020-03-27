#include <iostream>
#include <stdexcept>
#include "util_files.hpp"
#include "util_strings.hpp"

std::vector<std::string> get_args_vector(int argc, char **argv) {
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i) {
		args.push_back(std::string(argv[i]));
	}
	return args;
}

int parse_int(const std::string &string) {
	std::size_t next_position = 0;
	int n;
	try {
		n = std::stoi(string, &next_position, 10);
	} catch (...) {
		throw std::logic_error("invalid number \"" + string + "\"");
	}
	if (next_position != string.length())
		throw std::logic_error("invalid number \"" + string + "\"");
	return n;
}

double parse_double(const std::string &string) {
	std::size_t next_position = 0;
	double n;
	try {
		n = std::stod(string, &next_position);
	} catch (...) {
		throw std::logic_error("invalid number \"" + string + "\"");
	}
	if (next_position != string.length())
		throw std::logic_error("invalid number \"" + string + "\"");
	return n;
}

std::string basename(const std::string &filename) {
	std::size_t pos1 = filename.find_last_of("/\\");
	std::string name =
			(pos1 == std::string::npos) ? filename : filename.substr(pos1 + 1);
	std::size_t pos2 = name.find_last_of(".");
	return (pos2 == std::string::npos) ? name : name.substr(0, pos2);

}

