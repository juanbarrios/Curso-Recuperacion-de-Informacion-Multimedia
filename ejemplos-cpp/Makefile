# CC5213 - Recuperación de Información Multimedia

# parametros para compilación: usar C++ 11 y con todos los warnings
CFLAGS += -std=c++11 -Wall -Wextra

#compilar con optimizaciones. Para debug poner -O0 -ggdb
CFLAGS += -O3

#usar opencv para compilación y linkeo
CFLAGS  += $(shell pkg-config --cflags opencv4 fftw3 Qt5Widgets)
LDFLAGS += $(shell pkg-config --libs   opencv4 fftw3 Qt5Widgets)

##si no funciona pkg-config se deben configurar las rutas de instalacion de opencv
#CFLAGS  += -I[ruta al opencv/include]
#LDFLAGS += -L[ruta al opencv/lib] -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

#otras librerías que se podrían necesitar
#LDFLAGS  += -lm -lpthread

########## archivos a compilar ##########

EJEMPLOS_CPP  := $(sort $(wildcard src/Ejemplo*.cpp))
UTILS_CPP     := $(wildcard src/utils/*.cpp)
UTILS_HEADERS := $(wildcard src/utils/*.hpp)

########## archivos a generar ##########

EJEMPLOS_BIN  := $(patsubst src/%,build/%,$(basename $(EJEMPLOS_CPP)))
UTILS_O       := $(patsubst src/%,build/object/%,$(UTILS_CPP:.cpp=.o))

########## reglas de compilación ##########

#reglas all y clean no corresponden a archivos
.PHONY: all clean

#no borrar archivos intermedios
.PRECIOUS: build/object/%.o

#por defecto se generan todos los ejecutables de los ejemplos
all: $(EJEMPLOS_BIN)

#para cada ejecutable se requiere el object correspondiente más los utils 
build/Ejemplo%: build/object/Ejemplo%.o $(UTILS_HEADERS) $(UTILS_O)
	g++ $< -o $@ $(UTILS_O) $(LDFLAGS)

#para generar un object se usa el fuente cpp correspondiente más los headers
build/object/%.o: src/%.cpp $(UTILS_HEADERS)
	mkdir -p "$(@D)"
	g++ -c $(CFLAGS) -o $@ $<

#limpiar todos los archivos de compilación
clean:
	rm -rf build/
