# Curso Recuperación de Información Multimedia

  1. [Introducción](#intro)
  2. [Material Docente](#material)
  3. [Código Fuente](#codigo)
  4. [Bibliografía](#bibliografia)
  5. [Información del curso](#info)
 

## Introducción <a name="intro"></a>

La *Recuperación de Información Multimedia*, [Multimedia Information Retrieval](https://en.wikipedia.org/wiki/Multimedia_information_retrieval) (MIR), estudia el problema de extraer y buscar información en imágenes, audio, videos, textos y, en general, cualquier documento no estructurado.

En los sistemas de Recuperación de Información Multimedia destacan dos fases principales:

  1. **Representación de contenido** donde se extrae información relevante para describir el contenido de cada documento.

  2. **Búsqueda por similitud** donde se analizan y comparan descriptores de contenido con el objetivo de buscar y ordenar los documentos relevantes a la consulta.

Este curso estudia ambas fases, esto es, técnicas de representación de contenido para audio, imagen, video y texto, y varios algoritmos de búsqueda eficientes y efectivos para grandes cantidades de datos.

## Material Docente <a name="material"></a>

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


## Código Fuente <a name="codigo"></a>

Código fuente [para C++ 11](ejemplos-cpp/):
  * En un terminal cambiar al directorio donde está el archivo de `Makefile` y escribir `make`.
  * Ejecutar:
    * Linux: `build/Ejemplo1`
    * Windows: `build\Ejemplo1.exe`

Código fuente [para Python 3](ejemplos-python/):
  * Los archivos `.py` se ejecutan desde un terminal con el comando `python`.
  * Los archivos `.ipynb` deben ser abiertos con **Jupyter**.

## Bibliografía <a name="bibliografia"></a>

 * Handbook of Multimedia Information Retrieval. Eidenberger. 2012.
 * Modern Information Retrieval. Baeza-Yates, Ribeiro-Neto, 2011.
 * Multimedia Retrieval. Blanken, de Vries, Blok, Feng. 2007.
 * Foundations of Multidimensional and Metric Data Structures. Samet. 2006.
 * Deep Learning with Python. Chollet. 2018.
 * The Essential Guide to Image/Video Processing. Bovik. 2009.
 * H.264 and MPEG-4 Video Compression. Richardson. 2003.
 * Digital Image Processing. Gonzalez, Woods. 2008.
 * Data Mining: The Textbook. Aggarwal. 2015.
 * Similarity Search The Metric Space Approach. Zezula, Amato, Dohnal, Batko. 2006.
 * Computer Vision. Algorithms and Applications. Szeliski. 2011.
 * Deep Learning: A Practitioner's Approach. Patterson, Gibson. 2017.


## Información del curso <a name="info"></a>

El curso CC5213 se dicta en el [Departmento de Ciencias de la Computación de la Universidad de Chile](https://www.dcc.uchile.cl/). Es un curso electivo de la carrera de ingeniería civil en computación y es tomado por estudiantes de pregrado de ingeniería (computación, eléctrica, industrial) y estudiantes de posgrado (magíster y doctorado en computación). 

Actualmente (Otoño 2020) el curso [se está dictando](https://juan.cl/mir/) en la FCFM, Universidad de Chile.

Parte del material de este curso también se usa en el curso Recuperación de Información del [Diplomado de Ciencia de Datos](https://www.dcc.uchile.cl/datos).
