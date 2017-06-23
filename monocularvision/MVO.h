/*
 * MVO.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//#include "../monocularvision/featuredetection.h"
#include <monocularvision/matcher.h>
#include <monocularvision/tracker.h>
#include <monocularvision/visualizer.h>


class MVO {
public:
	MVO();
	virtual ~MVO();
    bool run();
	Point calculateDiff(std::vector<Point2f> train, std::vector<Point2f> query);
};
