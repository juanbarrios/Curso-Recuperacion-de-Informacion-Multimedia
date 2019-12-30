# Curso Recuperación de Información Multimedia
## Multimedia Information Retrieval (MIR)

La *Recuperación de Información Multimedia (MIR)* estudia el problema de buscar información en archivos multimedia de una colección dada y ordenarlos de acuerdo al grado de relevancia con respecto a la consulta del usuario.

En los sistemas de recuperación de información multimedia destacan dos fases principales:

  1. **Representación de contenido multimedia** donde se extrae información relevante para describir el contenido de cada documento.

  2. **Búsqueda por similitud** donde se analizan y comparan descriptores de contenido con el objetivo de buscar y ordenar los documentos relevantes a la consulta.

Este curso estudia ambas fases, esto es, técnicas de representación de contenido multimedia (específicamente audio, imagen, video y texto) y algoritmos de búsqueda eficientes y efectivos para grandes cantidades de datos.


# Material Docente

El material docentel del curso está dividido en cuatro partes.

 1. **Introducción y Preliminares**
   * [0-Introduccion](0-Introduccion.pdf)
   * [1a-C++ y OpenCV](1a-C++ y OpenCV.pdf)
   * [1b-ProcesamientoDeImagenes](1b-ProcesamientoDeImagenes.pdf)
   * [1c-DeteccionBordes](1c-DeteccionBordes.pdf)
   * [1d-DeteccionDeLineas](1d-DeteccionDeLineas.pdf)
   * [1e-DominioDeFrecuencias](1e-DominioDeFrecuencias.pdf)

 2. **Descripción de Contenido Multimedia**
   * [2a-Descriptores](2a-Descriptores.pdf)
   * [2b-DescriptoresGlobalesGris](2b-DescriptoresGlobalesGris.pdf)
   * [2c-DescriptoresGlobalesColor](2c-DescriptoresGlobalesColor.pdf)
   * [2d-DescriptoresAudio](2d-DescriptoresAudio.pdf)
   * [2e-ProcesamientoDeVideos](2e-ProcesamientoDeVideos.pdf)

 3. **Búsquedas por Similitud**
   * [3a-BusquedasPorSimilitud](3a-BusquedasPorSimilitud.pdf)
   * [3b-RepasoEstructurasDeDatos](3b-RepasoEstructurasDeDatos.pdf)
   * [3c-IndicesMultidimensionales](3c-IndicesMultidimensionales.pdf)
   * [3d-PCA](3d-PCA.pdf)
   * [3e-IndicesMetricos](3e-IndicesMetricos.pdf)
   * [3f-EvaluacionDeEfectividad](3f-EvaluacionDeEfectividad.pdf)

 4. **Métodos Avanzados**
   * [4a-DescriptoresLocales](4a-DescriptoresLocales.pdf)
   * [4b-Codebooks](4b-Codebooks.pdf)
   * [4c-DescriptoresTexto](4c-DescriptoresTexto.pdf)
   * [4d-RepasoMachineLearning](4d-RepasoMachineLearning.pdf)
   * [4e-DeepLearning](4e-DeepLearning.pdf)



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
