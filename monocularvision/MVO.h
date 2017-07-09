/*
 * MVO.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//#include "../monocularvision/featuredetection.h"
#include <monocularvision/matcher.h>
#include <monocularvision/tracker.h>
#include <statics/statics_tools.h>

class MVO{
public:
	MVO();
	virtual ~MVO();
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
