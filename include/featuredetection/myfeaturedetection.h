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
    Ptr<SurfFeatureDetector> fDetector_;
    //Ptr<DescriptorExtractor> fExtractor_;
    Ptr<SurfDescriptorExtractor> fExtractor_;
		//cv::Ptr<cv::DescriptorMatcher> descriptorMatcher;
		//featureDetector = cv::FeatureDetector::create("FAST");
		//descriptorExtractor = cv::DescriptorExtractor::create("FAST");
		void setFrame(Mat new_frame);

		void show(std::string window_name);

		void read(VideoCapture v);

		void detect();

		void compute();

		void drawKP();

		void convertD();

		void ORB();

		MyFeatureExtractor();
    MyFeatureExtractor(const MyFeatureExtractor& other);
    ~MyFeatureExtractor();
};

#endif /* MYFEATUREDETECTION_H_ */
