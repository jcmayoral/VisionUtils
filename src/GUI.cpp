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
	cvNamedWindow("main1",CV_WINDOW_NORMAL);
	const char* button = "Button";
	int a = 0;
	//cv::createButton(button,callbackButton,NULL, CV_CHECKBOX,0);

}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

