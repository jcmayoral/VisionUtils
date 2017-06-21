/*
 * visualizer.h
 *
 *  Created on: Nov 29, 2016
 *      Author: jose
 */

#include "opencv2/opencv.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class Visualizer {
public:
	Mat view_;
	Point3f point_;
	Visualizer();
	Visualizer(Mat frame);
	virtual ~Visualizer();
	void MyLine(Mat H);
};
