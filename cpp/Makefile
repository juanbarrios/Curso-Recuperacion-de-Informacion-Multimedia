# CC5213 - Recuperación de Información Multimedia

# parametros para compilación: usar C++ 11 y con todos los warnings
CFLAGS += -std=c++11 -Wall -Wextra

#compilar con optimizaciones
CFLAGS += -O3
#compilar con información de debug
#CFLAGS += -O0 -ggdb

#usar opencv para compilación y linkeo
CFLAGS  += $(shell pkg-config --cflags opencv fftw)
LDFLAGS += $(shell pkg-config --libs   opencv fftw)

##si no funciona pkg-config se deben configurar las rutas de instalacion de opencv
#CFLAGS  += -I[ruta al opencv/include]
#LDFLAGS += -L[ruta al opencv/lib] -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

#otras librerías que se podrían necesitar
#LDFLAGS  += -lm -lpthread

########## archivos a compilar ##########

EJEMPLOS_CPP := $(sort $(wildcard src/Ejemplo*.cpp))
UTIL_CPP     := $(sort $(wildcard src/util*.cpp) src/Mfcc.cpp)
UTIL_HEADERS := $(sort $(wildcard src/util*.hpp) src/Mfcc.hpp)

########## archivos a generar ##########

EJEMPLOS_BIN := $(patsubst src/%,build/%,$(basename $(EJEMPLOS_CPP)))
UTIL_O       := $(patsubst src/%,build/object/%,$(UTIL_CPP:.cpp=.o))

########## reglas de compilación ##########

#reglas all y clean no corresponden a archivos
.PHONY: all clean

#no borrar archivos intermedios
.PRECIOUS: build/object/%.o

#por defecto se generan todos los ejecutables de los ejemplos
all: $(EJEMPLOS_BIN)

#para un ejecutable se requiere el object correspondiente más los utils 
build/Ejemplo%: build/object/Ejemplo%.o $(UTIL_HEADERS) $(UTIL_O)
	g++ $< -o $@ $(UTIL_O) $(LDFLAGS)

#para generar un object se requiere el fuente correspondiente más los headers
build/object/%.o: src/%.cpp $(UTIL_HEADERS)
	mkdir -p "$(@D)"
	g++ -c $(CFLAGS) -o $@ $<

#limpiar todos los archivos de compilación
clean:
	rm -rf build/
