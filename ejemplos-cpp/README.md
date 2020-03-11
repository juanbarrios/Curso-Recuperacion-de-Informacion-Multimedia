# CC5213 - Recuperación de Información Multimedia

# Instalar C++ y OpenCV

En Windows existen varios compiladores de C++, como `cl` (Visual Studio de Microsoft) y distintos sabores de `g++`, mientras que en Linux lo más común es usar `g++` de GNU.

En Windows se debe escoger sabiamente el compilador porque no es posible mezclar librerías generadas por compiladores diferentes. Esto se debe a que cada compilador usa un "name mangling" diferente para guardar las funciones. Por tanto al compilar un programa con `g++` no es posible linkear con librerías generadas por `cl` (nota al margen: sí es posible mezclar DLL con funciones en C de distintos compiladores porque no existe overload de funciones ni name mangling).

### Windows: usar MinGW-w64 (recomendado)

**MinGW-w64** es un compilador `g++` que genera binarios nativos de Windows. Con pocas modificaciones se puede lograr que el mismo código fuente compile en Windows y Linux.

Se debe tener cuidado con algunas diferencias entre Windows y Linux, de lo que he descubierto son distintas las funciones de acceso al filesystem (`scandir`, `mkdir`, `stat`, `realpath`), las funciones de manejo de procesos (no existen `fork`, `waitpid`, `ioctl`) y una función de strings (`vsnprintf`).

Al usar MinGW-w64 no se puede usar directamente GPU porque las DLL de cuda están compiladas con Visual Studio y como dice más arriba no se pueden linkear librerías de diferentes compiladores.

Además del compilador, se necesitan herramientas básicas de Linux (como `bash`, `make`, `find`, `grep`). Un proyecto que ofrece versiones de esos comandos para windows se llama **MSYS2** que ofrece un administrador de paquetes (`pacman`) y permite descargar versiones compiladas de todas las librerías.

Para usar OpenCV:
  1. **Descargar MSYS2**: Entrar a https://sourceforge.net/projects/msys2/ descargar (actualmente`msys2-x86_64-20190524.exe`) e instalar en `C:\msys64`.
  1. **Actualizar**: En el terminal "MSYS2 MinGW 64-bits" escribir `pacman -Syu`. Ejecutar nuevamente `pacman -Syu` hasta que diga que está todo actualizado.
     - (bugfix) Actualmente al actualizar ocurre un error `connection timed out after 10000 milliseconds` porque no está disponible el mirror http://repo.msys2.org. Para corregirlo, entrar a la carpeta `C:\msys64\etc\pacman.d\`, modificar los archivos `mirrorlist.*` y comentar el repositorio `http://repo.msys2.org`. Ojo que la actualización puede modificar los mirrors por lo que nuevamente hay que comentar `http://repo.msys2.org` de `mirrorlist.*`.
  1. **Instalar paquetes para development**: `pacman -S --needed base-devel msys2-devel` (aceptar los valores por defecto)
  1. **Instalar MinGW-w64 64 bits**: `pacman -S --needed mingw-w64-x86_64-toolchain` (aceptar los valores por defecto)
  1. **Instalar OpenCV**: `pacman -S --needed mingw-w64-x86_64-opencv` actualmente instala OpenCV 4.2.0.
  1. **Otros útiles**: `pacman -S --needed mingw-w64-x86_64-ffmpeg mingw-w64-x86_64-fftw mingw-w64-x86_64-imagemagick mingw-w64-x86_64-qt5`

Una vez instalado todo, para usar el compilador `g++` se debe abrir una ventana "MSYS2 MinGW 64-bits". Otra opción es agregar la ruta `C:\msys64\usr\bin;C:\msys64\mingw64\bin` al `PATH` de Windows y también la ruta `C:\msys64\mingw64\lib\pkgconfig:C:\msys64\usr\lib\pkgconfig` a la variable `PKG_CONFIG_PATH` para usar el compilador desde un terminal normal.

Es posible compilar los fuentes de OpenCV con MinGW-w64 de forma similar a como se compila en Linux.

#### Alternativa en Windows: Usar Cygwin

**Cygwin** es un port de Linux para Windows que permite usar una gran cantidad de comandos de Linux  en Windows (como `bash`, `g++`, `make`, `grep`, etc.). El código fuente de los programas de Linux pueden ser compilados en Windows prácticamente sin modificaciones.

La desventaja es que los programas usan una DLL para la "emulación" de Linux sobre Windows lo que hace más lenta la ejecución.

#### Alternativa en Windows: Usar Visual Studio

**Visual Studio** es el entorno de desarrollo oficial para Windows. Su compilador de C++ se llama `cl`. Produce aplicaciones nativas de Windows para 32 y 64 bits con la posibilidad de usar GPU.

Una gran desventaja es que el compilador no cumple con C++11. Además Visual Studio fomenta el uso de la API exclusiva de Microsoft lo que vuelve difícil migrar después el programa a Linux.

Se debe descargar Visual Studio del sitio de Microsoft. La versión profesional es pagada pero existe una versión gratuita llamada "Community".

Para usar OpenCV:
	1. Descargar la distribución para Windows de `https://opencv.org/releases.html`, descargar `opencv-xxx-vc14_vc15.exe` y descomprimir en `C:\[ZZZ]\opencv`
	1. La descarga incluye las DLL para Visual Studio por lo que basta agregar al PATH la ruta `C:\[ZZZ]\opencv\build\x64\vc15\bin`.
	1. Además se debe agregar al PATH la ruta `C:\[ZZZ]\opencv\build\bin` para usar la DLL `opencv_ffmpeg.dll` que contiene distintos codecs. Si no se realiza este paso no se podrán leer archivos `.mp4` ni otros videos.

También es posible compilar los fuentes de OpenCV. Para esto se requiere bajar e instalar CMake desde https://cmake.org/download/. Al ejecutar cmake sobre los fuentes se genera un archivo `.solution` el cual se abre con Visual Studio. En el IDE se presiona sobre el botón compilar y (luego de mucho tiempo) genera las DLLs.

### Linux (Ubuntu) instalar C++ y OpenCV

En Ubuntu instalar los comandos:
  - `apt-get install build-essentials`
  - `apt-get install libopencv-dev`

### Compilar los fuentes de OpenCV

Para compilar los OpenCV se deben instalar algunas dependencias:
  - FFmpeg: `sudo apt-get install libavutil-dev libavdevice-dev libavcodec-dev libavfilter-dev libavformat-dev libswresample-dev`
  - Otras: `sudo apt-get install cmake python-dev python-numpy libtbb-dev libeigen3-dev libgtk2.0-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtiff4-dev libjpeg-dev libjasper-dev`

Descargar los fuentes de OpenCV desde https://github.com/opencv/opencv/releases y https://github.com/opencv/opencv_contrib/releases y ejecutar los siguientes pasos:

```
#descomprimir las descargas
unzip opencv-xxx.zip
unzip opencv_contrib-xxx.zip
#cambiar a donde estan los fuentes descargados
cd opencv-xxx/opencv
#crear un directorio para compilar y entrar
mkdir compilacion
cd compilacion
```

En el directorio creado se debe usar cmake:

```
#esta es una única línea que termina con un `..` al final
cmake                                                     \
    -D CMAKE_INSTALL_PREFIX=$HOME/mi_opencv               \
    -D CMAKE_BUILD_TYPE=RELEASE                           \
    -D OPENCV_ENABLE_NONFREE=ON                           \
    -D OPENCV_EXTRA_MODULES_PATH=[ruta contrib]/modules   \
    -D BUILD_SHARED_LIBS=ON                               \
    -D BUILD_PYTHON_SUPPORT=ON                            \
    -D BUILD_EXAMPLES=OFF                                 \
    -D WITH_FFMPEG=ON                                     \
    -D WITH_TBB=ON                                        \
    -D WITH_EIGEN=ON                                      \
    -D WITH_GTK=ON                                        \
    -D WITH_GTK3=ON                                       \
    -D WITH_OPENMP=ON                                     \
    -D INSTALL_PYTHON_EXAMPLES=ON                         \
    -D CMAKE_VERBOSE=OFF                                  \
    -D CMAKE_VERBOSE_MAKEFILE=OFF                         \
    ..
```

Al ejecutar el comando anterior se crean los makefiles. Ahora se debe compilar e instalar.
El parámetro `-jN` dice que use hasta N hilos en paralelo.
Al instalar se copian los binarios al directorio definido por `CMAKE_INSTALL_PREFIX`.

```
make -j4
make install
```

## Cómo compular un programa en C++

Para compilar un programa en C++ usualmente se requieren dos pasos:

  1. Paso 1 (`-c`): Convertir código fuente en código binario (object file).
    - Para cada `.cpp` se debe ejecutar `g++ -c -o archivo1.o archivo1.cpp`.
    - El compilador lee el fuente en el `.cpp`, resuelve todas las instrucciones `#include ...`  y si el código no tiene problemas generará un `.o` con la versión binaria del fuente.
    - Parámetros `-Iruta` configuran lugares para buscar headers además de `/usr/include/`
    - El parámetro `-std=c++11` para usar C++11
    - Los parámetros `-Wall` para warnings y `-Wextra` para aún más warnings.

  1. Paso 2 (linkeo): Crear el ejecutable o librería.
    - Se reúnen todos los object file `.o` y se asocia cada llamada a un método con su implementación, ya sea entre object files o con librerías externas (linkage).
    - Para crear ejecutable: `g++ -o ejemplo archivo1.o archivo2.o` Notar que entre todos los `.o` debe existir un único método `main()`.
    - Para crear librería compartida: `g++ -shared -o libejemplo.so archivo1.o archivo2.o`  (en linux son `.so`, en windows son `.dll`)
    - Parámetros `-Lruta` configuran lugares para buscar librerías compartidas (a parte de `/usr/lib/`).
    - Parámetros `-lnombre` declaran las librerías externas a buscar (se buscará `libnombre.so` en las rutas definidas por `-L`).

Notar que para proyectos pequeños, puede ser más fácil compilar y linkear en un solo comando, como `g++ -o ejemplo -Imi_opencv/include *.cpp -Lmi_opencv/lib -lopencv_core -lopencv_imgproc`

El comando `-L` permite linkear librerías `.so` que no están en una ruta por defecto. Luego de usarlo es muy probable que al ejecutar ese binario no se encuentren las librerías (aparecerá el mensaje `error: cannot open shared object file`). Para solucionarlo:
  - Opción 1: Agregar `$HOME/mi_opencv/lib` a la variable de entorno `LD_LIBRARY_PATH` para que el sistema operativo también busque ahí las librerías requeridas para la ejecución de un binario.
  - Opción 2: Compilar con el parámetro `-Wl,-rpath,mi_opencv/lib` para que el linker incluya el path completo (y no solo el nombre) en la lista de librerías requeridas.

El comando `ld` lista las dependencias declaradas por un binario y cómo las está resolviendo el sistema operativo. Permite saber qué librerías está usando en tiempo de ejecución (útil para descubrir choques entre versiones de librerías).

El comando `pkg-config` entrega los parámetros necesarios para compilar usando librerías externas. Para obtener los parámetros de compilación `pkg-config --cflags opencv`. Para los parámetros de linkeo `pkg-config --libs opencv`. Esos parámetros están definidos en archivos `.pc` ubicados en `/lib/pkgconfig/`. Si opencv se instaló en `$HOME/mi_opencv` se debe agregar la ruta `$HOME/mi_opencv/lib/pkgconfig` a la variable de entorno `PKG_CONFIG_PATH`.

Al desarrollar programas en C++ es común crear un archivo de nombre `Makefile` con las instrucciones de compilación. El comando `make` lee ese archivo y ejecuta las intrucciones necesarias. Para detalles ver el archivo Makefile de ejemplo.

## Entorno de desarrollo (IDE) para C++

Para las tareas del curso puede ser suficiente usar un editor de texto y compilar por línea de comandos. Sin embargo, es muy útil utilizar un IDE para programar. Los más usados para C++ son Codeblocks, Eclipse CDT, QtCreator.

**Eclipse CDT** se puede descargar desde https://www.eclipse.org/downloads/packages/ versión "Eclipse IDE for C/C++ Developers". Descargar el `.tar.gz` o `.zip` y descomprimir. Además puede ser útil instalar un plugin para usar `pkg-config` como https://marketplace.eclipse.org/content/pkg-config-support-eclipse-cdt
