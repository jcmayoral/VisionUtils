/*
 * MVO.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//#include "../monocularvision/featuredetection.h"
#include "featuredetection/matcher.h"
#include "featuredetection/tracker.h"
#include "statics/statics_tools.h"
#include <memory>

using namespace cv;
using namespace cv::xfeatures2d;

class FaultDetection{
public:
  FaultDetection();
  FaultDetection(bool ros);
  ~FaultDetection();
  bool start();
  bool run();
  bool stop();
  void stopRequest();
  void runSURF();
  Matcher getMatcher();
  Point getMeanPoint();
  Point getVariance();
  Point getCurrentCenter();
  double getCovariance();
  double getPearson();
  double getCUSUM();
  void  updateHessianThreshold(double threshold);
  void setMatchPercentage(double value);


protected:
  MyFeatureExtractor first_;
  MyFeatureExtractor second_;
  Ptr<SURF> fDetector_;
  Matcher matcher_;
  Point currentMeanPoint_;
  Point currentVariancePoint_;
  Point currentCenter_;
  double pearson_;
  double covariance_;
  double cusum_;
  bool stop_requested_;
  VideoCapture camera_;
  std::shared_ptr<MyStatics> statics_tool;
};
