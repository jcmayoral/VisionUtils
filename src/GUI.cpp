/*
 * GUI.cpp
 *
 *  Created on: Dec 1, 2016
 *      Author: jose
 */

#include "../gui/GUI.h"

using namespace cv;
using namespace std;

GUI::GUI() {
	// TODO Auto-generated constructor stub
	cvNamedWindow("main", CV_WINDOW_AUTOSIZE);
	//const char* button = "Button";
	Mat image;
	int a = 0;
	int alpha_slider = 0;
  //image = imread("../img/kvothe.jpg",CV_LOAD_IMAGE_COLOR);
	createButton("Calibration",GUI::callbackButton,&a,CV_PUSH_BUTTON);
	createTrackbar("trackbar", "Linear Blend", &alpha_slider, 100, NULL);
  //imshow("main", image);
}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
	cvDestroyAllWindows();
}

void GUI::callbackButton(int state, void* userdata){
	cout << "Inside Callback";
}
