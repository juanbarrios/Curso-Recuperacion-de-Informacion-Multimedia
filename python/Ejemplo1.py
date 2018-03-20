import sys
import cv2
import os

def mostrar_image(filename):
    print ("abriendo {}".format(filename))
    image_color = cv2.imread(filename, cv2.IMREAD_COLOR)
    if image_color is None:
        print ("error abriendo {}".format(filename))
        return
    image_gray = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY)
    threshold, image_bin = cv2.threshold(image_gray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
    window_name = os.path.basename(filename)
    cv2.imshow(window_name, image_color)
    cv2.imshow(window_name + " BIN", image_bin)
    print ("{}: size={} threshold={}".format(window_name, image_color.shape, threshold))


print ("Usando OpenCV {} Python {}.{}.{}".format(cv2.__version__, sys.version_info.major, sys.version_info.minor, sys.version_info.micro))

if len(sys.argv) < 2:
    print ("CC5213 - Ejemplo 1")
    print ("Uso: {} [filename]".format(sys.argv[0]))
    sys.exit(1)

filename = sys.argv[1]

mostrar_image(filename)
print ("Presione una tecla para salir...")
cv2.waitKey(0)
cv2.destroyAllWindows()
