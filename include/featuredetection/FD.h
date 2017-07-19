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

class FaultDetection{
public:
    FaultDetection();
    FaultDetection(bool ros);
    virtual ~FaultDetection();
    bool start();
    bool run();
    bool stop();
    Matcher getMatcher();
    Point getMeanPoint();
    Point getVariance();
    Point getCurrentCenter();
    double getCovariance();
    double getPearson();

private:
    Matcher matcher_;
    Point currentMeanPoint_;
    Point currentVariancePoint_;
    Point currentCenter_;
    double pearson_;
    double covariance_;
    VideoCapture camera_;
    MyStatics* statics_tool;
    MyFeatureExtractor first_;
    MyFeatureExtractor second_;


};
