import os
import numpy
import cv2
from PyQt5.QtWidgets import QApplication, QFileDialog

## Declaracion de algunas funciones utiles

def ui_select_filenames():
    app = QApplication(list());
    options = QFileDialog.Options()
    files, _ = QFileDialog.getOpenFileNames(None, "Imagenes", ".", "Imagenes (*.jpg *.png)", options=options)
    return files

def ui_select_video():
    app = QApplication(list());
    options = QFileDialog.Options()
    filename, _ = QFileDialog.getOpenFileName(None, "Videos", ".", "Videos (*.mp4 *.mpg)", options=options)
    if not filename:
        return "0"
    return filename

def agregar_texto(imagen, texto):
    fontFace = cv2.FONT_HERSHEY_SIMPLEX
    fontScale = 1
    thickness = 2
    textSize = cv2.getTextSize(texto, fontFace, fontScale, thickness)
    position1 = (20,20)
    position2 = (30,30)
    cv2.rectangle(imagen, position1, position2, (0,255,0), -1)
    cv2.putText(imagen, texto, (20,20), fontFace, fontScale, (255,0,0), thickness, cv2.LINE_AA)

def escalar(imagen, valorAbsoluto = False, escalarMin0Max255 = False):
    img = imagen
    if valorAbsoluto:
        img = numpy.abs(imagen)
    if escalarMin0Max255:
        img2 = cv2.normalize(img, dst=None, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8U)
        img = img2
    return img

def mostrar_imagen(window_name, imagen):
    #reducir tamaño
    MAX_WIDTH = 700
    MAX_HEIGHT = 500
    if imagen.shape[0] > MAX_HEIGHT or imagen.shape[1] > MAX_WIDTH:
        fh = MAX_HEIGHT / imagen.shape[0]
        fw = MAX_WIDTH / imagen.shape[1]
        escala = min(fh,fw)
        imagen = cv2.resize(imagen, (0,0), fx=escala, fy=escala)
    #mostrar en pantalla
    cv2.imshow(window_name, imagen)

def abrir_imagen(filename):
    imagen_color = cv2.imread(filename, cv2.IMREAD_COLOR)
    if imagen_color is None:
        raise Exception("error abriendo {}".format(filename))
    print ("{}: size={}".format(filename, imagen_color.shape))
    return imagen_color

def abrir_video(filename):
    if filename is None:
        filename = 0
    elif filename.isdigit():
        filename = int(filename)
    capture = None
    if isinstance(filename, int):
        print("abriendo webcam {}...".format(filename))
        capture = cv2.VideoCapture(filename)
    if (os.path.isfile(filename)):
        print("abriendo video {}...".format(filename))
        capture = cv2.VideoCapture(filename)
    if capture is None or not capture.isOpened():
        raise Exception("no puedo abrir video {}".format(filename))
    return capture;

def print_help(argv):
    return "--help" in argv
