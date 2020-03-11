#pragma once

#include <string>
#include <vector>

bool existe_archivo(const std::string &filename);

std::vector<std::string> listar_archivos(const std::string &dirname);

std::vector<std::string> leer_lineas_archivo(const std::string &filename);
