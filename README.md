# Curso Recuperación de Información Multimedia

La *Recuperación de Información Multimedia*, [Multimedia Information Retrieval](https://en.wikipedia.org/wiki/Multimedia_information_retrieval) (MIR), estudia el problema de extraer y buscar información en imágenes, audio, videos, textos y, en general, cualquier documento no estructurado. En los sistemas de Recuperación de Información Multimedia destacan dos fases principales:

  1. **Representación de contenido** donde se extrae información relevante para describir el contenido de cada documento.

  2. **Búsqueda por similitud** donde se analizan y comparan descriptores de contenido con el objetivo de buscar y ordenar los documentos relevantes a la consulta.

Este curso estudia ambas fases, esto es, técnicas de representación de contenido para audio, imagen, video y texto, y varios algoritmos de búsqueda eficientes y efectivos para grandes cantidades de datos.

## Material Docente

El material docente del curso está dividido en cuatro partes.

 1. **Preliminares**
     * [1a-Introducción MIR](slides/1a-IntroduccionMIR.pdf)
     * [1b-C++ y OpenCV](slides/1b-C%2B%2ByOpenCV.pdf)
     * [1c-Procesamiento de Imágenes](slides/1c-ProcesamientoDeImagenes.pdf)
     * [1d-Detección de Bordes](slides/1d-DeteccionDeBordes.pdf)
     * [1e-Detección de Líneas](slides/1e-DeteccionDeLineas.pdf)
     * [1f-Dominio de Frecuencias](slides/1f-DominioDeFrecuencias.pdf)

 2. **Descripción de Contenido Multimedia**
     * [2a-Descriptores de Contenido](slides/2a-Descriptores.pdf)
     * [2b-Descriptores Globales Gris](slides/2b-DescriptoresGlobalesGris.pdf)
     * [2c-Descriptores Globales Color](slides/2c-DescriptoresGlobalesColor.pdf)
     * [2d-Descriptores de Audio](slides/2d-DescriptoresDeAudio.pdf)
     * [2e-Procesamiento de Videos](slides/2e-ProcesamientoDeVideos.pdf)

 3. **Búsquedas por Similitud**
     * [3a-Busquedas por Similitud](slides/3a-BusquedasPorSimilitud.pdf)
     * [3b-Repaso Estructuras de Datos](slides/3b-RepasoEstructurasDeDatos.pdf)
     * [3c-Índices Multidimensionales](slides/3c-IndicesMultidimensionales.pdf)
     * [3d-PCA](slides/3d-PCA.pdf)
     * [3e-Índices Métricos](slides/3e-IndicesMetricos.pdf)
     * [3f-Evaluación de Efectividad](slides/3f-EvaluacionDeEfectividad.pdf)

 4. **Métodos Avanzados**
     * [4a-Descriptores Locales](slides/4a-DescriptoresLocales.pdf)
     * [4b-Codebooks](slides/4b-Codebooks.pdf)
     * [4c-Descriptores de Texto](slides/4c-DescriptoresDeTexto.pdf)
     * [4d-Repaso Machine Learning](slides/4d-RepasoMachineLearning.pdf)
     * [4e-Deep Learning](slides/4e-DeepLearning.pdf)


## Código Fuente

Código fuente [para C++ 11](ejemplos/cpp/):

	* En un terminal cambiar al directorio donde está el archivo de `Makefile` y escribir `make`.
	* Ejecutar:
		* Linux: `build/Ejemplo1`
		* Windows: `build\Ejemplo1.exe`

Código fuente [para Python 3](ejemplos/python/):

	* Los archivos `.py` se ejecutan desde un terminal con el comando `python`.
	* Los archivos `.ipynb` deben ser abiertos con **Jupyter**.
