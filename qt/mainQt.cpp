/*
 * main.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include <QApplication>
#include <../qt/mainwindow.h>

int main(int argc, char ** argv){

	//GUI gui = GUI();
	QApplication app(argc, argv);
	MainWindow w;
  w.show();

  return app.exec();
}
