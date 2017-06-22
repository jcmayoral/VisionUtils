/*
 * tracker.cpp

 *
 *  Created on: Nov 29, 2016
 *      Author: jose
 */

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <monocularvision/tracker.h>

Tracker::Tracker(){

};

Tracker::~Tracker(){

};

void Tracker::featureTracking(MyFeatureExtractor f1, MyFeatureExtractor f2, Matcher& match)	{

//this function automatically gets rid of points for which tracking fails
  std::vector<float> err;
  std::vector<uchar> status;
  Size winSize=Size(21,21);
  TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 10, 0.01);

  Mat flow;
  //calcOpticalFlowPyrLK(f1.frame_, f2.frame_, match.best_train_, match.best_query_, status, err, winSize, 3, termcrit, 0, 0.001);
  //calcOpticalFlowSF	(f1.frame_, f2.frame_, flow,  1,2,4);


  // Process
  cv::calcOpticalFlowPyrLK(f1.frame_,f2.frame_,match.best_train_,match.best_query_,status,err,winSize,3,criteria,0.001);

  //calcOpticalFlowPyrLK(f1.frame_, f2.frame_, match.best_train_, match.best_query_, status, err, winSize, 3, termcrit, 0, 0.001);
  //getting rid of points for which the KLT tracking failed or those who have gone outside the frame
  int indexCorrection = 0;
  assert (match.best_query_.size() == match.best_train_.size());

  for( unsigned int i=0; i < match.best_query_.size(); i++){
	   Point2f pt = match.best_query_.at(i- indexCorrection);
	   if ((pt.x<0)||(pt.y<0)){
		   match.best_train_.erase(match.best_train_.begin() + i - indexCorrection);
		   match.best_query_.erase(match.best_query_.begin() + i - indexCorrection);
		   indexCorrection++;
	   }

   }

}
