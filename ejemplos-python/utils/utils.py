from PyQt5.QtWidgets import QApplication, QFileDialog


def ui_select_filenames():
    app = QApplication(list());
    options = QFileDialog.Options()
    files, _ = QFileDialog.getOpenFileNames(None, "Imagenes", ".", "Imagenes (*.jpg *.png)", options=options)
    return files


def print_help(argv):
    return "--help" in argv
