# Curso Recuperación de Información Multimedia
## Multimedia Information Retrieval (MIR)

La *Recuperación de Información Multimedia (MIR)* estudia el problema de buscar información en archivos multimedia de una colección dada y ordenarlos de acuerdo al grado de relevancia con respecto a la consulta del usuario.

En los sistemas de recuperación de información multimedia destacan dos fases principales:

  1. **Representación de contenido multimedia** donde se extrae información relevante para describir el contenido de cada documento.

  2. **Búsqueda por similitud** donde se analizan y comparan descriptores de contenido con el objetivo de buscar y ordenar los documentos relevantes a la consulta.

Este curso estudia ambas fases, esto es, técnicas de representación de contenido multimedia (específicamente audio, imagen, video y texto) y algoritmos de búsqueda eficientes y efectivos para grandes cantidades de datos.

# Material Docente

El material docente del curso está dividido en cuatro partes.

 1. **Preliminares**
     * [1a-Introducción Curso MIR](1a-IntroduccionCursoMIR.pdf)
     * [1b-C++ y OpenCV](1b-C%2B%2ByOpenCV.pdf)
     * [1c-Procesamiento de Imágenes](1c-ProcesamientoDeImagenes.pdf)
     * [1d-Detección Bordes](1d-DeteccionDeBordes.pdf)
     * [1e-Detección de Líneas](1e-DeteccionDeLineas.pdf)
     * [1f-Dominio de Frecuencias](1f-DominioDeFrecuencias.pdf)

 2. **Descripción de Contenido Multimedia**
     * [2a-Descriptores](2a-Descriptores.pdf)
     * [2b-Descriptores Globales Gris](2b-DescriptoresGlobalesGris.pdf)
     * [2c-Descriptores Globales Color](2c-DescriptoresGlobalesColor.pdf)
     * [2d-Descriptores de Audio](2d-DescriptoresDeAudio.pdf)
     * [2e-Procesamiento de Videos](2e-ProcesamientoDeVideos.pdf)

 3. **Búsquedas por Similitud**
     * [3a-Busquedas por Similitud](3a-BusquedasPorSimilitud.pdf)
     * [3b-Repaso Estructuras de Datos](3b-RepasoEstructurasDeDatos.pdf)
     * [3c-Índices Multidimensionales](3c-IndicesMultidimensionales.pdf)
     * [3d-PCA](3d-PCA.pdf)
     * [3e-Índices Métricos](3e-IndicesMetricos.pdf)
     * [3f-Evaluación de Efectividad](3f-EvaluacionDeEfectividad.pdf)

 4. **Métodos Avanzados**
     * [4a-Descriptores Locales](4a-DescriptoresLocales.pdf)
     * [4b-Codebooks](4b-Codebooks.pdf)
     * [4c-Descriptores de Texto](4c-DescriptoresDeTexto.pdf)
     * [4d-Repaso Machine Learning](4d-RepasoMachineLearning.pdf)
     * [4e-Deep Learning](4e-DeepLearning.pdf)


# Ejemplos para C++

1. En `/cpp/` están los ejemplos para C++. Requiere un compilador C++ 11 (Windows o Linux).
2. En un terminal cambiar al directorio donde está el archivo de `Makefile` y escribir `make`.
3. Ejecutar:
	* Linux: `build/Ejemplo1`
	* Windows: `build\Ejemplo1.exe`

# Ejemplos para Python

1. En `/python/` están los ejemplos para Python 3.
2. Los archivos `.py` se ejecutan desde un terminal con el comando `python`.
3. Los archivos `.ipynb` deben ser abiertos con **Jupyter**.
