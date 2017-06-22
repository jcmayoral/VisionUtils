/*
 * MVO.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//#include "../monocularvision/featuredetection.h"
#include "matcher.h"
#include "tracker.h"
#include "visualizer.h"

class MVO {
public:
	MVO();
	virtual ~MVO();
	bool run();
	Point calculateDiff(std::vector<Point2f> train, std::vector<Point2f> query);
};
