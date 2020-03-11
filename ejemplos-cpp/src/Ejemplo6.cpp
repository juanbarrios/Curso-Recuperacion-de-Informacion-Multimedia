#include <fftw3.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "utils/Mfcc.hpp"
#include "utils/util_files.hpp"
#include "utils/util_opencv.hpp"
#include "utils/util_strings.hpp"

namespace {

std::vector<short> loadAudioSamples(const std::string &filename, int sample_rate) {
	//s16le: Signed 16 bits little-endian
	const std::string codec = "s16le";
	//archivo de salida con el audio raw
	std::string fileOutput = filename + "." + codec + "." + std::to_string(sample_rate) + ".raw";
	std::vector<short> audio_samples;
	if (!existe_archivo(fileOutput)) {
		//ejecutar el comando FFMPEG para decodificar el audio
		std::string command = "ffmpeg -y -i  \"" + filename + "\" -ac 1 -vn -sn -ar " + std::to_string(sample_rate) + " -f " + codec + " -acodec pcm_" + codec
				+ " \"" + fileOutput + "\"";
		std::cout << "running: " << command << std::endl;
		int ret = std::system(command.c_str());
		if (ret != 0) {
			std::cout << "error al ejecutar: " << command << std::endl;
			return audio_samples;
		}
	}
	//abrir el archivo raw
	std::ifstream infile;
	infile.open(fileOutput);
	if (!infile.is_open()) {
		std::cout << "no puedo abrir " << fileOutput << std::endl;
		return audio_samples;
	}
	std::cout << "leyendo " << fileOutput << std::endl;
	//ir al final
	infile.seekg(0, std::ios::end);
	//obtener la posicion en bytes
	int numBytes = infile.tellg();
	//volver al inicio
	infile.seekg(0, std::ios::beg);
	//convertir numero de bytes a numero de samples
	int numSamples = numBytes / sizeof(short);
	//leer todos los bytes del archivo
	audio_samples.resize(numSamples);
	infile.read(reinterpret_cast<char*>(audio_samples.data()), numBytes);
	return audio_samples;
}

template<typename T>
double getMaxValue(const std::vector<T> &audio_samples) {
	double max_sample = 0;
	for (T sample : audio_samples) {
		double d = std::fabs(sample);
		if (d > max_sample)
			max_sample = d;
	}
	return max_sample;
}

template<typename T>
void printVector(const std::string &vector_name, const std::vector<T> &vector_values) {
	std::cout << vector_name << ":";
	for (T value : vector_values) {
		std::cout << " " << value;
	}
	std::cout << std::endl;
}

void drawVector(cv::Mat &image, const std::vector<double> &vector_values, const cv::Scalar &color_background, const cv::Scalar &color_foreground,
		double &global_maximum) {
	//size de la imagen
	int width = std::min(400, (int) vector_values.size());
	image.create(400, width, CV_8UC3);
	//linea central
	int linea_base = image.rows / 2 - 1;
	int alto_max = image.rows / 2 - 1;
	//limpiar la imagen
	cv::rectangle(image, cv::Point(0, 0), cv::Point(image.cols, image.rows), color_background, cv::FILLED);
	cv::line(image, cv::Point(0, linea_base), cv::Point(image.cols, linea_base), cv::Scalar(0, 0, 0), 1);
	//calcular el valor maximo del vector
	double maxValue = getMaxValue(vector_values);
	//actualizar el maximo global
	if (maxValue > global_maximum) {
		global_maximum = maxValue;
	} else {
		maxValue = global_maximum;
	}
	//para evitar la division por cero
	if (maxValue == 0)
		maxValue = 1;
	//ciclo por columna de la imagen
	cv::Point prev(-1, -1), current;
	for (int i = 0; i < width; ++i) {
		//obtener el valor en proporcion del maximo
		double val = vector_values.at(i) / maxValue;
		//escalar el valor al alto de la imagen
		int alto = std::round(val * alto_max);
		//coordenadas del punto
		current.x = i;
		current.y = std::max(std::min(linea_base - alto, image.rows - 1), 0);
		//dibujar la linea
		if (prev.x >= 0 && current.x < image.cols)
			cv::line(image, prev, current, color_foreground, 1);
		prev = current;
	}
}
void drawSpectogram(cv::Mat &image_gray, cv::Mat &image_color, const std::vector<double> &vector_values, double global_maximum, int &position) {
	int height = std::min(1000, (int) vector_values.size());
	if (position < 0) {
		position = 0;
		image_gray.create(height, height, CV_8UC1);
		cv::rectangle(image_gray, cv::Point(0, 0), cv::Point(image_gray.cols, image_gray.rows), cv::Scalar::all(0), cv::FILLED);
	}
	//usar el valor maximo del vector para escalar grises
	double maxValue = global_maximum;
	//para evitar la division por cero
	if (maxValue == 0)
		maxValue = 1;
	for (int i = 0; i < height; ++i) {
		//obtener el valor gris en proporcion del maximo
		int gray = std::round(vector_values.at(i) / maxValue * 255);
		//asegurarse que esta en el rango de 8 bits
		gray = std::max(0, std::min(255, gray));
		//coordenadas del punto
		image_gray.at<uchar>(i, position) = gray;
	}
	position = (position + 1) % image_gray.cols;
	//convertir a colores
	cv::applyColorMap(image_gray, image_color, cv::COLORMAP_JET);
}

void ejemplo(const std::vector<short> &audio_samples, int samplerate) {
	//procesar el audio por ventanas
	std::size_t ventana_num_samples = 1024;
	std::size_t despl_num_samples = 128;
	//print sizes en milisegundos
	int audio_ms = std::round((1000.0 * audio_samples.size()) / samplerate);
	int ventana_ms = std::round((1000.0 * ventana_num_samples) / samplerate);
	int despl_ms = std::round((1000.0 * despl_num_samples) / samplerate);
	std::cout << "audio= " << audio_ms << " ms.(" << audio_samples.size() << " samples)  ventana=" << ventana_ms << " ms.(" << ventana_num_samples
			<< " samples)  desplazamiento= " << despl_ms << " ms.(" << despl_num_samples << " samples)" << std::endl;
	//procesar el audio por ventanas
	std::vector<double> ventana_samples;
	ventana_samples.resize(ventana_num_samples);
	//preparar la FT
	//el numero de coeficientes esta dado por la libreria FFTW3
	std::size_t num_coeficientes_ft = ventana_num_samples / 2 + 1;
	//espacio para los complejos de salida, cada fftw_malloc debe tener un fftw_free
	fftw_complex *coeficientes_ft = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_coeficientes_ft);
	//preparar la FT. r2c=real to complex. recibe los arrays de entrada y salida
	fftw_plan plan_ft = fftw_plan_dft_r2c_1d(ventana_num_samples, ventana_samples.data(), coeficientes_ft, FFTW_MEASURE);
	//vector para guardar el espectro (magnitud de los complejos)
	std::vector<double> energias_espectro;
	energias_espectro.resize(num_coeficientes_ft);
	//parametros de mfcc
	int numFilters = 48; // number of filters for MFCC calc
	int numCoeffs = 48; // number of MFCC coefficients to calculate
	//libreria que calcula MFCC a partir del espectro
	Mfcc mfcc;
	mfcc.init(samplerate, numFilters, num_coeficientes_ft, numCoeffs);
	std::vector<double> mfcc_descriptor;
	//imagenes a mostrar
	cv::Mat image_samples, image_spectrum, image_spectogram, image_spectogram_color, image_mfcc;
	///valor del maximo para normalizar la visualizacion
	double max_sample = getMaxValue(audio_samples);
	std::cout << "samplerate=" << samplerate << "  num_coeficientes_ft=" << num_coeficientes_ft << std::endl;
	//no se conocen a priori estos maximos, se iran escalando de a poco
	double max_energy = 0;
	double max_mfcc = 0;
	int spectogram_position = -1;
	//ciclo por ventada
	for (std::size_t start = 0; start + ventana_num_samples < audio_samples.size(); start += despl_num_samples) {
		//obtengo los valores de la ventana
		for (std::size_t i = 0; i < ventana_num_samples; ++i) {
			ventana_samples[i] = audio_samples[start + i];
			//se puede multiplicar la ventana por una funcion que suavice los bordes: Hann
		}
		//dibujar el audio
		drawVector(image_samples, ventana_samples, cv::Scalar(0, 127, 127), cv::Scalar(255, 255, 127), max_sample);
		cv::imshow("samples", image_samples);
		//calcular la FT
		fftw_execute(plan_ft);
		//obtener las magnitudes para la visualizacion
		for (std::size_t i = 0; i < num_coeficientes_ft; i++) {
			double real = coeficientes_ft[i][0];
			double imag = coeficientes_ft[i][1];
			energias_espectro[i] = std::sqrt(real * real + imag * imag);
		}
		//dibujar el espectro
		drawVector(image_spectrum, energias_espectro, cv::Scalar(0, 127, 0), cv::Scalar(0, 255, 255), max_energy);
		cv::imshow("spectrum", image_spectrum);
		//dibujar el espectograma
		drawSpectogram(image_spectogram, image_spectogram_color, energias_espectro, max_energy, spectogram_position);
		cv::imshow("spectogram", image_spectogram_color);
		//calcular mfcc
		mfcc.getCoefficients(energias_espectro, mfcc_descriptor);
		//dibujar el descriptor
		drawVector(image_mfcc, mfcc_descriptor, cv::Scalar(127, 127, 127), cv::Scalar(255, 255, 255), max_mfcc);
		//printVector("mfcc", mfcc_descriptor);
		cv::imshow("mfcc", image_mfcc);
		//esperar una tecla. ESC=salir, espacio=pausa
		int c = cv::waitKey(1);
		if (c == 27)
			break;
		else if (c == ' ')
			cv::waitKey(0);
	}
	fftw_destroy_plan(plan_ft);
	fftw_free(coeficientes_ft);
}

const double pi = 3.14159265358979323846;

std::vector<short> generateSamplesAndSave(int samplerate) {
	std::vector<short> audio_samples;
	double hertz1 = 500;
	double hertz2 = 4000;
	double amplitud = 20000;
	for (int j = 0; j < 10; ++j) {
		for (int i = 0; i < samplerate / 2; ++i) {
			short sample1 = (short) (amplitud * std::cos(i * 2 * pi / samplerate * hertz1));
			short sample2 = (short) (amplitud * std::cos(i * 2 * pi / samplerate * hertz2));
			short sample = sample1+sample2;
			audio_samples.push_back(sample);
		}
	}
	std::string newfilename = "samples.raw";
	std::ofstream outfile;
	outfile.open(newfilename, std::ios::trunc | std::ios::binary);
	if (!outfile.is_open()) {
		std::cout << "error escribiendo " << newfilename << std::endl;
		return audio_samples;
	}
	outfile.write((char*) audio_samples.data(), sizeof(short) * audio_samples.size());
	outfile.close();
	std::cout << "guardado " << newfilename << std::endl;
	std::cout << "ffplay -f s16le -acodec pcm_s16le -ar " << samplerate << " " << newfilename << std::endl;
	return audio_samples;
}

}

int main(int argc, char** argv) {
	try {
		std::vector<std::string> args = get_args_vector(argc, argv);
		std::cout << "Ejemplo 6 AUDIO" << std::endl;
		if (args.size() <= 1) {
			std::cout << "Uso: " << args[0] << " [video_filename]" << std::endl;
			//return 1;
		}
		//calidad del audio
		int samplerate = 22000;
		std::vector<short> audio_samples;
		if (args.size() <= 1) {
			audio_samples = generateSamplesAndSave(samplerate);
		} else {
			std::string filename = args[1];
			if (!existe_archivo(filename)) {
				std::cout << "no encuentro " << filename << std::endl;
				return 1;
			}
			//obtener los samples del audio decodificado
			audio_samples = loadAudioSamples(filename, samplerate);
			if (audio_samples.size() == 0)
				return 1;
		}
		ejemplo(audio_samples, samplerate);
	} catch (const std::exception& ex) {
		std::cout << "Ha ocurrido un ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cout << "Ha ocurrido ERROR desconocido" << std::endl;
	}
	return 0;
}
