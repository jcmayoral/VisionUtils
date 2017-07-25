/*
 * myfeacturedetection.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include "featuredetection/myfeaturedetection.h"
#include "opencv2/videoio.hpp"

MyFeatureExtractor::MyFeatureExtractor(): descriptors_(), keypoints_(),frame_(){
    fDetector_ = SURF::create();
    std::cout << "MyFeatureExtractor Constructor" << std::endl;
}

MyFeatureExtractor::MyFeatureExtractor(const MyFeatureExtractor& other): descriptors_(other.descriptors_),
                                            keypoints_(other.keypoints_), frame_(other.frame_){
    fDetector_ = SURF::create();
    cv::cvtColor(frame_,frame_,cv::COLOR_RGB2GRAY);
}

MyFeatureExtractor::~MyFeatureExtractor(){
    frame_.release();
}

void MyFeatureExtractor::show(std::string window_name){
	imshow(window_name, frame_);
}

void MyFeatureExtractor::setFrame(Mat new_frame){
  frame_ = new_frame;
}


void MyFeatureExtractor::read(VideoCapture v){
    v  >> frame_;
    cv::cvtColor(frame_,frame_,cv::COLOR_BGR2GRAY);
}

void MyFeatureExtractor::detect(){
  std::cout << "During Detect";
	fDetector_->detect(frame_,keypoints_);
}

void MyFeatureExtractor::compute(){
  fDetector_->compute(frame_, keypoints_, descriptors_);
}

void MyFeatureExtractor::drawKP(){
    drawKeypoints(frame_, keypoints_, frame_);
}

void MyFeatureExtractor::convertD(){
    if (descriptors_.type()!=CV_32F) {
            descriptors_.convertTo(descriptors_, CV_32F);
    }
}

void MyFeatureExtractor::ORB(){
  std::cout << "Before Detect";
	detect();
  std::cout << "After Detect";
	compute();
	drawKP();
	convertD();
}
