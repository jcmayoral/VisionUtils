/*
 * MVO.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <featuredetection/FD.h>
//#include <statistics/statistics_tools.h>

using namespace cv;
using namespace std;

void FaultDetection::updateHessianThreshold(double threshold){
    fDetector_->setHessianThreshold(threshold);
}

void FaultDetection::setMatchPercentage(double value){
    matcher_.setMatchPercentage(value);
}

void FaultDetection::runSURF(){

  Mat img,descriptors;
  img = first_.getFrame();
  std::vector<cv::KeyPoint> k1;

  Mat tmp;
  fDetector_->detectAndCompute(img,tmp, k1, descriptors);
  drawKeypoints(img,k1,tmp);


  if (descriptors.type()!=CV_32F) {
    descriptors.convertTo(descriptors, CV_32F);
  }

  first_.setFrame(tmp);
  first_.setDescriptors(descriptors);
  first_.setKeyPoints(k1);
}

void FaultDetection::stopRequest(){
    cout << "Stop Requested";
    stop_requested_=true;
}

FaultDetection::FaultDetection(): camera_( 0 ),first_(),second_(),stop_requested_(false), last_mean_(0.0), last_variance_(0.0){
  // TODO Auto-generated constructor stub
  fDetector_ = SURF::create();
  fDetector_->setHessianThreshold(400);
  matcher_.setMatchPercentage(0.05);
  cout << "FD Constructor" << endl;
}

FaultDetection::FaultDetection(bool ros): camera_(0), first_(),second_(){
  fDetector_ = SURF::create(400,4,3,true,true);
  matcher_.setMatchPercentage(0.05);
  cout << "ROS Constructor" << endl;
}

FaultDetection::~FaultDetection() {
	// TODO Auto-generated destructor stub
  //delete this->statistics_tool;
  cout << "FD destroyed";
}

Matcher FaultDetection::getMatcher(){
  return matcher_;
}

Point FaultDetection::getMeanPoint(){
  return currentMeanPoint_;
}

Point FaultDetection::getVariance(){
  return currentVariancePoint_;
}

Point FaultDetection::getCurrentCenter(){
  return currentCenter_;
}

double FaultDetection::getCovariance(){
  return covariance_;
}

double FaultDetection::getPearson(){
  return pearson_;
}

double FaultDetection::getCUSUM(){
  return cusum_;
}

double FaultDetection::getBlur(){
  return blur_;
}

bool FaultDetection::start(){
  if (!camera_.isOpened()){
    cerr  << "Could not open the input video: " << endl;
    return false;
  }

  first_.read(camera_);
  runSURF();
  return true;
}

bool FaultDetection::run(){
  if (stop_requested_){
      cout << "request " << stop_requested_;
      return false;
  }
  Tracker tracker;
  try{
    second_ = first_;
    first_.read(camera_);
    matcher_.clearing();
    runSURF();
    matcher_.matchD(first_,second_);
    matcher_.separateMatches(first_,second_);
    matcher_.getBestMatches(first_,second_);
    matcher_.separateBestMatches(first_,second_);
    matcher_.drawBestMatches(first_,second_);
    matcher_.show("BestMatchesDisplay");
    currentMeanPoint_ = statistics_tool->calculateMean(matcher_);
    currentVariancePoint_ = statistics_tool->calculateVariance(matcher_,currentMeanPoint_);
    covariance_ = statistics_tool->CalculateCovariance(matcher_,currentMeanPoint_.x,currentMeanPoint_.y);
    pearson_ = statistics_tool->CalculatePearsonCorrelation(matcher_,currentMeanPoint_.x,currentMeanPoint_.y, currentVariancePoint_.x, currentVariancePoint_.y);
    cusum_ = statistics_tool->CUSUM(matcher_, last_mean_, last_variance_);
    blur_ = statistics_tool->getBlur(second_.getFrame());
    return true;
  }

  catch(Exception e){
    e.what();
    return false;
  }
}

bool FaultDetection::stop(){
  try{
    camera_.release();
    matcher_.clearing();
    destroyAllWindows();
    cout << "MVO finishing correctly" << endl;
    return true;
  }
  catch (Exception e){
    e.what();
    return false;
  }

}
