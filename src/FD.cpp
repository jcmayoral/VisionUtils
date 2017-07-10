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
    matcher_.setMatchPercentage(0.20);
    cout << "MVO Constructor" << endl;

}

FaultDetection::~FaultDetection() {
	// TODO Auto-generated destructor stub
	//cout << "MVO destroyed";
    //destroyWindow("clusters");
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

bool FaultDetection::run(){
    MyFeatureExtractor first;
    Tracker tracker;
    cout << "run " << endl;


    if (!camera_.isOpened()){
    	cerr  << "Could not open the input video: " << endl;
	    return false;
	}

    Mat frame;
    camera_ >> frame;

    namedWindow("BestMatchesDisplay",WINDOW_AUTOSIZE );

    first.read(camera_);
	first.ORB();
    MyFeatureExtractor second(first);
    first.read(camera_);
    matcher_.clearing();
    first.ORB();
    matcher_.matchD(first,second);
    matcher_.separateMatches(first,second);
    matcher_.getBestMatches(first);
    matcher_.separateBestMatches(first,second);

    matcher_.drawBestMatches(first,second);
    matcher_.show("BestMatchesDisplay");
    cout<< matcher_.best_train_.size();


    try{
        Mat H = findHomography(matcher_.best_query_,matcher_.best_train_, RANSAC);
    }
    catch (exception e){
        e.what();
    }

    currentMeanPoint_ = statics_tool->calculateMean(matcher_);
    currentVariancePoint_ = statics_tool->calculateVariance(matcher_,currentMeanPoint_);
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

