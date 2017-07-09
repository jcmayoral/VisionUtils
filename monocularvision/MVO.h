/*
 * MVO.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//#include "../monocularvision/featuredetection.h"
#include <monocularvision/matcher.h>
#include <monocularvision/tracker.h>

class MVO {
public:
	MVO();
	virtual ~MVO();
    bool run();
    Matcher matcher_;

};
