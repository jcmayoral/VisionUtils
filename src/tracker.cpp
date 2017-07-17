/*
 * tracker.cpp

 *
 *  Created on: Nov 29, 2016
 *      Author: jose
 */

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "featuredetection/tracker.h"
#include <iostream>
#include <iterator>

Tracker::Tracker(){

};

Tracker::~Tracker(){

};

void Tracker::featureTracking(MyFeatureExtractor f1, MyFeatureExtractor f2, Matcher& match)	{

//this function automatically gets rid of points for which tracking fails
  std::vector<float> err;
  std::vector<uchar> status;
  match.best_query_.clear();
  cv::calcOpticalFlowPyrLK(f2.frame_,f1.frame_,match.best_train_,match.best_query_,status,err);
  match.best_train_.clear();
  cv::calcOpticalFlowPyrLK(f1.frame_,f2.frame_,match.best_query_,match.best_train_,status,err);

}
