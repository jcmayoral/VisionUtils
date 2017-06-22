/*
 * GUI.h
 *
 *  Created on: Dec 1, 2016
 *      Author: jose
 */

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;

#ifndef GUI_H_
#define GUI_H_

class GUI {
public:
	GUI();
	~GUI();
	static void callbackButton(int state, void* userdata);
};

#endif /*GUI_H_ */
