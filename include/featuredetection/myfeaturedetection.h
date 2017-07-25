/*
 * myfeaturedetection.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace cv::xfeatures2d;

#ifndef MYFEATUREDETECTION_H_
#define MYFEATUREDETECTION_H_

class MyFeatureExtractor{
	public:
		Mat descriptors_;
		std::vector<cv::KeyPoint> keypoints_;
		Mat frame_;
    //Ptr<FeatureDetector> fDetector_;
    Ptr<SURF> fDetector_;
    //Ptr<SurfDescriptorExtractor> fExtractor_;
		void setFrame(Mat new_frame);

		void show(std::string window_name);

		virtual void read(VideoCapture v);

		MyFeatureExtractor();
    MyFeatureExtractor(const MyFeatureExtractor& other);
    ~MyFeatureExtractor();
};

#endif /* MYFEATUREDETECTION_H_ */
