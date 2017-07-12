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

FaultDetection::FaultDetection(): camera_( 0 ){
	// TODO Auto-generated constructor stub
    matcher_.setMatchPercentage(0.05);
    cout << "FD Constructor" << endl;

}

FaultDetection::~FaultDetection() {
	// TODO Auto-generated destructor stub
    cout << "FD destroyed";
    camera_.release();
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

bool FaultDetection::start(){
    if (!camera_.isOpened()){
        cerr  << "Could not open the input video: " << endl;
        return false;
    }

    first_.read(camera_);
    first_.ORB();
    return true;
}


bool FaultDetection::run(){

    Tracker tracker;
    second_ = first_;
    first_.read(camera_);
    matcher_.clearing();
    first_.ORB();
    matcher_.matchD(first_,second_);
    matcher_.separateMatches(first_,second_);
    //tracker.featureTracking(first_, second_,matcher_);
    matcher_.getBestMatches(first_,second_);
    matcher_.separateBestMatches(first_,second_);
    matcher_.drawBestMatches(first_,second_);
    matcher_.show("BestMatchesDisplay");
    currentMeanPoint_ = statics_tool->calculateMean(matcher_);
    currentCenter_ = statics_tool->getKMeans(matcher_);
    currentVariancePoint_ = statics_tool->calculateVariance(matcher_,currentCenter_);
    covariance_ = statics_tool->CalculateCovariance(matcher_,currentMeanPoint_.x,currentMeanPoint_.y);
    return true;
}

bool FaultDetection::stop(){
    try{
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

