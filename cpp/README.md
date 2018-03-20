# OpenCV para C++

## Versión binaria para Linux

En Ubuntu instalar el package: `apt-get install libopencv-dev`

## Versión binaria para Windows

* Primero se debe escoger un compilador de C++.
	* En C++ no es posible mezclar librerías generadas por compiladores diferentes, es decir, al compilar un programa con `g++` no es posible linkear con librerías generadas por `cl` (Visual Studio). Esto se debe a que cada compilador usa un "name mangling" diferente para guardar las funciones (como dato extra, sí es posible mezclar compiladores usando C ya que no existe overloading de funciones).

* **Visual Studio**: Compilador oficial para Windows.
	* Ventajas: es que se obtienen aplicaciones nativas de windows con posibilidad de usar GPU.
	* Desventajas: el compilador (llamado `cl`) no cumple con C++11 y utiliza API exclusiva de Microsoft por lo se vuelve difícil lograr que el mismo programa compile en Windows y Linux.
	* La distribución oficial de OpenCV incluye las DLL para Visual Studio:
		1. Entra a `https://opencv.org/releases.html`, descargar `opencv-3.4.1-vc14_vc15.exe` y descomprimir en `C:\[ZZZ]\opencv`
		2. Las librerías están en `C:\[ZZZ]\opencv\build\x64\vc15\bin`. Agregar al PATH la ruta `C:\[ZZZ]\opencv\build\x64\vc15\bin`.
		3. Agregar al PATH la ruta `C:\[ZZZ]\opencv\build\bin`. Si no se realiza este paso no se podrán leer archivos `.mp4` ya que los codecs están en `opencv_ffmpeg341.dll`.

* **Cygwin**: Es un port de linux para windows que instala la mayoria de los comandos linux (incluido `g++` y `bash`).
	* Ventajas: exactamente el mismo codigo fuente se puede compilar en linux y windows.
	* Desventajas: requiere una biblioteca de "emulación" de linux sobre windows por lo que la ejecución es más lenta.

* **MinGW**: Es un intermedio entre las dos opciones anteriores: es un compilador g++ que puede crear binarios nativos de windows.
	* Ventajas: Con pocos ajustes el mismo código puede obtener una aplicación en Windows y Linux.
	* Desventajas: Tiene algunas diferencias en acceso al filesystem (como `scandir`, `mkdir`, `stat`, `realpath`), funciones de strings (como `vsnprintf`) y manejo de procesos (no existe `fork`, `waitpid`, `ioctl`).
	* Para instalar **MinGW** lo más simple es a través de **MSYS2**, el cual es un entorno con comandos de Linux (bash, grep, find, etc.) que incluye un administrador de paquetes (`pacman`).
		1. Descargar **MSYS2** desde http://www.msys2.org/ e instalarlo en `C:\msys64`
		2. Abrir el terminal de MSYS2 y actualizar: `pacman -Syu` . Esto se debe realizar varias veces hasta que no actualice nada.
		3. Instalar paquetes de desarrollo: `pacman -S --needed base-devel`
		4. Instalar el compilador **MinGW 64 bits**: `pacman -S --needed mingw-w64-x86_64-toolchain` (para 32 bit cambiar `x86_64` por `i686`)
		5. Instalar **OpenCV**: `pacman -S --needed mingw-w64-x86_64-opencv`
		6. Instalar otros comandos útiles: `pacman -S --needed mingw-w64-x86_64-ffmpeg mingw-w64-x86_64-imagemagick` La lista de dependencias opcionales de OpenCV se obtiene con `pacman -Si mingw-w64-x86_64-opencv`
		7. Para usar `g++` se debe abrir la ventana "MSYS2 MinGW 64-bits" o en una ventana agregar al PATH `C:\msys64\usr\bin;C:\msys64\mingw64\bin` y agregar a PKG_CONFIG_PATH `C:\msys64\mingw64\lib\pkgconfig:C:\msys64\usr\lib\pkgconfig`

## Compilar fuentes de OpenCV en Linux

  * Primero se debe instalar FFmpeg (para poder abrir videos):
    * Binarios Ubuntu: `sudo apt-get install libavutil-dev libavdevice-dev libavcodec-dev libavfilter-dev libavformat-dev libswresample-dev`
    * Binarios Windows:  (MSYS2) `mingw-w64-x86_64-ffmpeg` (DLLS) https://ffmpeg.zeranoe.com/builds/
    * Para compilar los fuentes, se deben descargar desde http://www.ffmpeg.org/ y luego `./configure  [opciones]; make; make install`. Se deben compilar los codecs, especialmente x264.
  * Instalar otras dependencias para OpenCV: `sudo apt-get install cmake python-dev python-numpy libtbb-dev libeigen3-dev libgtk2.0-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtiff4-dev libjpeg-dev libjasper-dev`
  * Descargar los fuentes de OpenCV desde https://github.com/opencv/opencv/releases y desde  https://github.com/opencv/opencv_contrib/releases
  * Descomprimirlos y ejecutar los siguientes pasos:

```bash
#cambiar a donde estan los fuentes descargados
cd opencv
#crear un directorio para compilar
mkdir compilacion
#entrar al directorio
cd compilacion

#generar los makefilas con las siguientes opciones (notar que `..` hace referencia a los fuentes)
cmake \
  -D CMAKE_INSTALL_PREFIX=$HOME/mi_opencv  \
  -D BUILD_SHARED_LIBS=ON                  \
  -D BUILD_PYTHON_SUPPORT=ON               \
  -D BUILD_EXAMPLES=ON                     \
  -D WITH_FFMPEG=ON                        \
  -D WITH_TBB=ON                           \
  -D WITH_EIGEN=ON                         \
  -D WITH_GTK=ON                           \
  -D WITH_GTK3=ON                          \
  -D WITH_OPENMP=ON                        \
  -D INSTALL_PYTHON_EXAMPLES=ON            \
  -D CMAKE_BUILD_TYPE=RELEASE              \
  -D CMAKE_VERBOSE=ON                      \
  -D CMAKE_VERBOSE_MAKEFILE=ON             \
 ..

#compilar con -j para que sea en paralelo
make -j4

#copiar el resultado en el directorio definido por CMAKE_INSTALL_PREFIX
make install
```

Si se instaló en un directorio fuera de `/usr/` es posible que en tiempo de ejecución no se encuentren las librerias (`error: cannot open shared object file`). El comando `ld` da información de como se esta resolviendo las dependencias.

Para resolver dependencias faltantes en tiempo de ejecución hay dos opciones:
  * Opción 1: Agregar el directorio `$HOME/mi_opencv/lib` a la variable de entorno `LD_LIBRARY_PATH` para que el sistema operativo busque ahí librerías requeridas para la ejecución.
  * Opción 2: Compilar con el parámetro `-Wl,-rpath,$HOME/mi_opencv/lib` para que el linker además del nombre incluya el path compmleto de la libreria usada.

## Compilar fuentes de OpenCV en Windows

Se requiere bajar e instalar CMake desde https://cmake.org/download/

Si se usa **MinGW** los pasos son muy similares a la compilación en Linux.

Para **Visual Studio** con CMake se genera un archivo `solution` el cual se abre con Visual Studio y se presion sobre compilar.

## Compilación de un programa en C++

Para las tareas del curso puede ser suficiente usar un editor como Notepad++ y compilar por línea de comandos.

Para compilar un código fuente en C++ usualmente se requieren dos pasos:

* Paso 1: Convertir código fuente en código binario (object file). Para cada .cpp ejecutar: `g++ -c -o archivo1.o archivo1.cpp`.
 
    * El compilador lee el fuente en el `.cpp` y resuelve todas las instrucciones `#include <librería.hpp>`
    * Con `-I`ruta se configuran lugares para buscar headers además de `/usr/include/`
    * Agregar `-std=c++11` para usar C++11
    * Agregar `-Wall` para warnings
    * Si el código fuente no tiene problemas se creará un object file `.o` con la versión binaria del fuente.

* Paso 2: Linkeo para crear ejecutable o librería
    * Se reúnen todos los object file y se asocian cada llamada a método con su implementación, ya sea entre object files o con librerías externas (linkage)
    * Para un ejecutable, debe existir un método `main()` entre todos los `.o`: `g++ -o ejemplo archivo1.o archivo2.o`
    * Para una librería (`.so`, `.dll`): `g++ -shared -o libejemplo.so archivo1.o archivo2.o`
    * Con `-L`ruta se configuran lugares para buscar librerías además de `/usr/lib/`.
    * Con `-l`nombre se declaran las librerías externas a buscar (se buscará `libnombre.so` en las rutas definidas).

Es posible compilar y linkear en un solo comando: `g++ -o ejemplo -Idir *.cpp -Ldir -llibreria`

El utilitario `pkg-config` entrega los parámetros de compilación al usar librerías externas.

   * Compilacion: `pkg-config --cflags libreria1 libreria2`
   * Linkeo: `pkg-config --libs libreria1 libreria2`

Usualmente se crea un archivo de nombre `Makefile` con las instrucciones de compilación que luego se ejecuta con el comando `make`.

## IDE

Otra opción es utilizar un IDE. Los más usados para C++ son: Codeblocks, Eclipse CDT, QtCreator.

Eclipse CDT se puede descargar desde http://www.eclipse.org/ide/ versión C/C++. (Descargar el `.tar.gz` o `.zip` y descomprimir). Además es útil instalar un plugin para usar pkg-config. Ver https://marketplace.eclipse.org/content/pkg-config-support-eclipse-cdt
