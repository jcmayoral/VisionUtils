/*
 * tracker.cpp

 *
 *  Created on: Nov 29, 2016
 *      Author: jose
 */

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <featuredetection/tracker.h>

Tracker::Tracker(){

};

Tracker::~Tracker(){

};

void Tracker::featureTracking(MyFeatureExtractor f1, MyFeatureExtractor f2, Matcher& match)	{

//this function automatically gets rid of points for which tracking fails
  std::vector<float> err;
  std::vector<uchar> status;
  Size winSize=Size(3,3);
  TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 10, 0.01);

  Mat flow;
  cv::calcOpticalFlowPyrLK(f1.frame_,f2.frame_,match.best_train_,match.best_query_,status,err,winSize,3,criteria,0.001);
  int indexCorrection = 0;
  assert (match.best_query_.size() == match.best_train_.size());

  for( uint i=0; i<status.size(); i++)
      {  Point2f pt = match.best_query_.at(i- indexCorrection);
         if ((status.at(i) == 0)||(pt.x<0)||(pt.y<0))	{
               if((pt.x<0)||(pt.y<0))	{
                 status.at(i) = 0;
               }
               match.best_train_.erase (match.best_train_.begin() + (i - indexCorrection));
               match.best_query_.erase (match.best_query_.begin() + (i - indexCorrection));
               indexCorrection++;
         }

      }

  std::cout << "Remaining correspondences: " << match.best_train_.size();


}
