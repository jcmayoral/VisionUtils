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
#include <statics/statics_tools.h>

using namespace cv;
using namespace std;

void FaultDetection::runSURF(){
  std::cout << "Before Detect";
  Mat descriptors = first_.getDescriptors();
  std::vector<cv::KeyPoint> k1 = first_.getKeyPoints();
  fDetector_->detect(first_.getFrame(),k1);
  fDetector_->compute(first_.getFrame(), k1, descriptors);
  Mat tmp;
  drawKeypoints(first_.getFrame(), first_.getKeyPoints(), tmp);
  first_.setFrame(tmp);

  if (descriptors.type()!=CV_32F) {
    descriptors.convertTo(descriptors, CV_32F);
    first_.setDescriptors(descriptors);
  }
}


FaultDetection::FaultDetection(): camera_( 0 ),first_(),second_(){
  // TODO Auto-generated constructor stub
  fDetector_ = SURF::create();
  matcher_.setMatchPercentage(0.05);
  cout << "FD Constructor" << endl;
}

FaultDetection::FaultDetection(bool ros): camera_(0), first_(),second_(){
  fDetector_ = SURF::create();
  matcher_.setMatchPercentage(0.05);
  cout << "ROS Constructor" << endl;
}

FaultDetection::~FaultDetection() {
	// TODO Auto-generated destructor stub
  //delete this->statics_tool;
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
  std::cout << "original RUN";
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
    //tracker.featureTracking(first_, second_,matcher_);
    matcher_.drawBestMatches(first_,second_);
    matcher_.show("BestMatchesDisplay");
    currentMeanPoint_ = statics_tool->calculateMean(matcher_);
    //currentCenter_ = statics_tool->getKMeans(matcher_);
    currentVariancePoint_ = statics_tool->calculateVariance(matcher_,currentMeanPoint_);
    covariance_ = statics_tool->CalculateCovariance(matcher_,currentMeanPoint_.x,currentMeanPoint_.y);
    pearson_ = statics_tool->CalculatePearsonCorrelation(matcher_,currentMeanPoint_.x,currentMeanPoint_.y, currentVariancePoint_.x, currentVariancePoint_.y);
    cusum_ = statics_tool->CUSUM(matcher_);
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
