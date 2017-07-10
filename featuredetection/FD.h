/*
 * MVO.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//#include "../monocularvision/featuredetection.h"
#include <featuredetection/matcher.h>
#include <featuredetection/tracker.h>
#include <statics/statics_tools.h>

class FaultDetection{
public:
    FaultDetection();
    virtual ~FaultDetection();
    bool start();
    bool run();
    bool stop();
    Matcher getMatcher();
    Point getMeanPoint();
    Point getVariance();
private:
    Matcher matcher_;
    Point currentMeanPoint_;
    Point currentVariancePoint_;
    VideoCapture camera_;
    MyStatics* statics_tool;
    MyFeatureExtractor first_;
    MyFeatureExtractor second_;


};
