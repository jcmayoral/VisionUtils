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

class FaultDetection{
public:
  FaultDetection();
  FaultDetection(bool ros);
  virtual ~FaultDetection();
  virtual bool start();
  virtual bool run();
  virtual bool stop();
  Matcher getMatcher();
  Point getMeanPoint();
  Point getVariance();
  Point getCurrentCenter();
  double getCovariance();
  double getPearson();
  double getCUSUM();

protected:
  MyFeatureExtractor first_;
  MyFeatureExtractor second_;

  Matcher matcher_;
  Point currentMeanPoint_;
  Point currentVariancePoint_;
  Point currentCenter_;
  double pearson_;
  double covariance_;
  double cusum_;
  VideoCapture camera_;
  std::shared_ptr<MyStatics> statics_tool;
};
