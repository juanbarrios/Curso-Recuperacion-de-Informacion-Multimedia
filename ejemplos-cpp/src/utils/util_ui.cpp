#include "util_ui.hpp"
#include <iostream>
#include <QApplication>
#include <QFileDialog>

std::vector<std::string> ui_select_images() {
	int argc = 0;
	char **argv = 0;
	QApplication app(argc, argv);
	QFileDialog::Options options;
	QString selectedFilter;
	QStringList fileNames = QFileDialog::getOpenFileNames(nullptr,
			QString("Elegir Imagenes"), ".", QString("Imagenes (*.jpg *.png)"),
			&selectedFilter, options);
	std::vector<std::string> list;
	for (QString &fileName : fileNames) {
		list.push_back(fileName.toStdString());
	}
	return list;
}

std::string ui_select_video() {
	int argc = 0;
	char **argv = 0;
	QApplication app(argc, argv);
	QFileDialog::Options options;
	QString selectedFilter;
	QString filename = QFileDialog::getOpenFileName(nullptr,
			QString("Elegir Video"), ".", QString("Videos (*.mpg *.mp4 *.avi)"),
			&selectedFilter, options);
	return filename.toStdString();
}
