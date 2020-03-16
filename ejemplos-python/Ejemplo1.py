import sys
import cv2
import os
from utils import utils

def procesar_imagen(filename):
    print("abriendo {}".format(filename))
    imagen_color = cv2.imread(filename, cv2.IMREAD_COLOR)
    if imagen_color is None:
        print("no puedo abrir imagen {}".format(filename))
        return
    imagen_gris = cv2.cvtColor(imagen_color, cv2.COLOR_BGR2GRAY)
    threshold, imagen_bin = cv2.threshold(imagen_gris, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
    window_name = os.path.basename(filename)
    cv2.imshow(window_name, imagen_color)
    cv2.imshow(window_name + " BINARIA", imagen_bin)
    print("{}: size={} threshold_otsu={}".format(window_name, imagen_color.shape, threshold))

def procesar_archivos(filenames):
    if len(filenames) == 0:
        filenames = utils.ui_select_filenames()
    if len(filenames) == 0:
        return
    for filename in filenames:
        procesar_imagen(filename)
    print("Presione una tecla...")
    cv2.waitKey(0)
    cv2.destroyAllWindows()


print("CC5213 - Ejemplo 1 OTSU")
print("Usando OpenCV {} con Python {}.{}.{}".format(cv2.__version__, sys.version_info.major, sys.version_info.minor, sys.version_info.micro))

if utils.print_help(sys.argv):
    print("Uso: {} [filenames]".format(sys.argv[0]))
else:
    procesar_archivos(sys.argv[1:])

print("fin")
