# parametros para compilacion
CFLAGS   += -std=c++11 -Wall -Wextra

#compilar con optimizaciones
CFLAGS += -O3
#compilar con informacion de debug o compilar con optimizaciones
#CFLAGS += -O0 -ggdb

#usar opencv
CFLAGS  += $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs   opencv)

##configurar las rutas de instalacion de opencv
#CFLAGS  += -I[ruta al opencv/include]
#LDFLAGS += -L[ruta al opencv/lib] -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

#otras librerias que se pueden usar
#LDFLAGS  += -lm -lpthread

########## archivos necesarios para compilar ##########

EJEMPLOS_CPP := $(sort $(wildcard src/Ejemplo*.cpp))
UTIL_CPP     := $(sort $(wildcard src/util*.cpp))
UTIL_HEADERS := $(sort $(wildcard src/util*.hpp))

########## archivos generados ##########

EJEMPLOS_BIN := $(patsubst src/%,build/%,$(basename $(EJEMPLOS_CPP)))
UTIL_O       := $(patsubst src/%,build/object/%,$(UTIL_CPP:.cpp=.o))

########## reglas de compilacion ##########

#reglas all y clean no corresponden a archivos
.PHONY: all clean

#no borrar archivos intermedios
.PRECIOUS: build/object/%.o

#por defecto se generan todos los ejecutables de los ejemplos
all: $(EJEMPLOS_BIN)

#para un ejecutable se requiere el object correspondiente mas los utils 
build/Ejemplo%: build/object/Ejemplo%.o $(UTIL_HEADERS) $(UTIL_O)
	g++ $^ -o $@ $(LDFLAGS)

#para generar un object se requiere el fuente correspondiente mas los headers
build/object/%.o: src/%.cpp $(UTIL_HEADERS)
	mkdir -p "$(@D)"
	g++ -c $(CFLAGS) -o $@ $<

#limpiar todos los archivos de compilacion
clean:
	rm -rf build/
