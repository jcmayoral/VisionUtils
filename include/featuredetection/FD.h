/*
 * MVO.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//#include "../monocularvision/featuredetection.h"
#include "featuredetection/matcher.h"
#include "featuredetection/tracker.h"
#include "statistics/statistics_tools.h"
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
  double getBlur();
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
  double blur_;
  double last_mean_;
  double last_variance_;
  bool stop_requested_;
  VideoCapture camera_;
  std::shared_ptr<MyStatistics> statistics_tool;
};
