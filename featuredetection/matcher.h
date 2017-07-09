#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <featuredetection/myfeaturedetection.h>
using namespace cv;

#ifndef MATCHER_H_
#define MATCHER_H_

class Matcher:FlannBasedMatcher{
	public:
		std::vector<Point2f> query_;
		std::vector<Point2f> train_;
		std::vector<Point2f> best_query_;
		std::vector<Point2f> best_train_;
		std::vector<DMatch> matches_;
		std::vector<DMatch> best_matches_;
		Mat frame_;

		Matcher(){

		};
		~Matcher(){
		};

		void matchD(MyFeatureExtractor ext1, MyFeatureExtractor ext2);

		void separateMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);

		void separateBestMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);

        void getBestMatches(MyFeatureExtractor ext1);

        void drawBestMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);

		void drawAllMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);

		void show(std::string window_name);

		void clearing();

};
  
#endif /* MATCHER_H_ */
