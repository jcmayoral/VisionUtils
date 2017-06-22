/*
 * myfeacturedetection.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include<monocularvision/myfeaturedetection.h>
#include "opencv2/videoio.hpp"


MyFeatureExtractor::MyFeatureExtractor(){
	fDetector_ = ORB::create();
	fExtractor_ = ORB::create();

}

MyFeatureExtractor::MyFeatureExtractor(const MyFeatureExtractor& other):frame_(other.frame_),
		keypoints_(other.keypoints_), descriptors_(other.descriptors_){
	fDetector_ = other.fDetector_;
	fExtractor_ = other.fExtractor_;
}


MyFeatureExtractor::~MyFeatureExtractor(){

}

void MyFeatureExtractor::show(std::string window_name){
	imshow(window_name, frame_);
}

void MyFeatureExtractor::read(VideoCapture v){
	v >> frame_;
}

void MyFeatureExtractor::detect(){
	fDetector_->detect(frame_,keypoints_);
}

void MyFeatureExtractor::compute(){
	fExtractor_->compute(frame_, keypoints_, descriptors_);
}

void MyFeatureExtractor::drawKP(){
	drawKeypoints(frame_, keypoints_, frame_);
}

void MyFeatureExtractor::convertD(){
	if(descriptors_.type()!=CV_32F) {
		descriptors_.convertTo(descriptors_, CV_32F);
	}
}

void MyFeatureExtractor::ORB(){
	detect();
	compute();
	drawKP();
	convertD();

}


