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

class FD{
public:
    FD();
    virtual ~FD();
    bool run();
    bool stop();
    Matcher getMatcher();
    Point getMeanPoint();
private:
    Matcher matcher_;
    Point currentMeanPoint_;
    VideoCapture camera_;
    MyStatics* statics_tool;

};
