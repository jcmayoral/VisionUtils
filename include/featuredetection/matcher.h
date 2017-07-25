#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "myfeaturedetection.h"
using namespace cv;

#ifndef MATCHER_H_
#define MATCHER_H_

class Matcher:FlannBasedMatcher{

	public:
		Matcher();
		~Matcher();
		void show(std::string window_name);
		void setMatchPercentage(double val);
		void getBestMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);
		void matchD(MyFeatureExtractor ext1, MyFeatureExtractor ext2);
		void separateMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);
		void separateBestMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);
		void drawBestMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);
		void drawAllMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2);
		void clearing();
		int getSize(int index);
		std::vector<Point2f> getVector(int index);
		std::vector<DMatch> getBestMatches();

	protected:
		std::vector<Point2f> query_;
		std::vector<Point2f> train_;
		std::vector<Point2f> best_query_;
		std::vector<Point2f> best_train_;
		std::vector<DMatch> matches_;
		std::vector<DMatch> best_matches_;
		Mat frame_;
		double matchPercentage_;

};

#endif /* MATCHER_H_ */
