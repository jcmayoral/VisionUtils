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
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace cv::xfeatures2d;

#ifndef MYFEATUREDETECTION_H_
#define MYFEATUREDETECTION_H_

class MyFeatureExtractor{
	public:
		void setFrame(Mat new_frame);
		Mat getFrame();
		void show(std::string window_name);
		void read(VideoCapture v);
		void setDescriptors(Mat desc);
		Mat getDescriptors();
		std::vector<cv::KeyPoint> getKeyPoints();
		void setKeyPoints(std::vector<cv::KeyPoint> kp);

		MyFeatureExtractor();
    MyFeatureExtractor(const MyFeatureExtractor& other);
    ~MyFeatureExtractor();

	protected:
		Mat frame_;
		Mat descriptors_;
		std::vector<cv::KeyPoint> keypoints_;

};

#endif /* MYFEATUREDETECTION_H_ */
