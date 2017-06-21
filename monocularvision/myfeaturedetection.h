/*
 * myfeaturedetection.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

#ifndef MYFEATUREDETECTION_H_
#define MYFEATUREDETECTION_H_


class MyFeatureExtractor{
	public:
		Mat descriptors_;
		std::vector<cv::KeyPoint> keypoints_;
		Mat frame_;
		Ptr<FeatureDetector> fDetector_;
		Ptr<DescriptorExtractor> fExtractor_;
		//cv::Ptr<cv::DescriptorMatcher> descriptorMatcher;
		//featureDetector = cv::FeatureDetector::create("FAST");
		//descriptorExtractor = cv::DescriptorExtractor::create("FAST");

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
