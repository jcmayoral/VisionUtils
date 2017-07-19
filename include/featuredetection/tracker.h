#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "featuredetection/myfeaturedetection.h"
#include "featuredetection/matcher.h"
using namespace cv;

class Tracker{

	public:
		Tracker();
		~Tracker();
		void featureTracking(MyFeatureExtractor f1, MyFeatureExtractor f2, Matcher& match);
};
