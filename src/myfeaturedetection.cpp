/*
 * myfeacturedetection.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include<featuredetection/myfeaturedetection.h>
#include "opencv2/videoio.hpp"

MyFeatureExtractor::MyFeatureExtractor(): descriptors_(), keypoints_(),frame_(){
    //fDetector_ = ORB::create();
    fDetector_ = SURF::create();
    fExtractor_ = SURF::create();
    std::cout << "MyFeatureExtractor Contructor" << std::endl;
}

MyFeatureExtractor::MyFeatureExtractor(const MyFeatureExtractor& other): descriptors_(other.descriptors_),
                                            keypoints_(other.keypoints_), frame_(other.frame_){
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


