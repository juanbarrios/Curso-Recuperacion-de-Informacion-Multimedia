# CC5213 - Recuperación de Información Multimedia

# Instalar Python y OpenCV

Existen varias formas de instalar Python. Se puede descargar directamente o usar una distribución como Anaconda o Miniconda.

**Miniconda** es una distribución de python que ofrece un administrador de paquetes (`conda`) que permite descargar versiones compiladas las librerías.

Para usar OpenCV:
  1. **Instalar Miniconda**: Entrar a https://docs.conda.io/en/latest/miniconda.html descargar la versión Python 3.7.
  1. **Actualizar**: En un terminal escribir `conda activate` y luego `conda update --all` (varias veces hasta que diga que está todo actualizado).
  1. **Instalar OpenCV**: `conda install -c conda-forge opencv` ( instala la versión 4.2.0)
  1. **Otros**: `conda install -c conda-forge pyqt`

## Entorno de desarrollo (IDE) para Python

**Spyder** es un IDE que viene incluido con Anaconda. Se puede instalar con: `conda install -c anaconda spyder`.

**Jupyter Notebook** es un IDE web que viene incluido con Anaconda. Se puede instalar con: `conda install -c anaconda jupyter`.

**PyCharm** es un IDE avanzado. La versión profesional es pagada pero existe una versión gratuita llamada "Community". Se descarga desde https://www.jetbrains.com/pycharm/download/
  - Al crear un proyecto, configurar la ruta donde está instalado Miniconda como intérprete para usar el ambiente donde se instaló OpenCV.
