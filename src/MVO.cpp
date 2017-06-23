/*
 * MVO.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <monocularvision/MVO.h>

using namespace cv;
using namespace std;

MVO::MVO() {
	// TODO Auto-generated constructor stub
    cout << "MVO Constructor" << endl;

}

Point MVO::calculateDiff(std::vector<Point2f> train, std::vector<Point2f> query){
	Point tmp;
	tmp.x = 0;
	tmp.y = 0;

	for (unsigned int i=0; i<train.size();i++){
		tmp.x += (train[i].x-query[i].x);
		tmp.y += (train[i].y-query[i].y);

	}

	if (train.size() > 0){
		tmp.x /=train.size();
		tmp.y /=train.size();
	}

	return tmp;
}

MVO::~MVO() {
	// TODO Auto-generated destructor stub
	//cout << "MVO destroyed";
    //cvDestroyAllWindows();
}

bool MVO::run(){

	VideoCapture cap( 0 );
    MyFeatureExtractor first;
    Matcher matcher;
    Tracker tracker;
    Visualizer visualizer;
    cout << "run " << endl;


    if (!cap.isOpened()){
    	cerr  << "Could not open the input video: " << endl;
	    return false;
	}

    Mat frame;
    cap >> frame;
    visualizer = Visualizer (frame);
    /*
	VideoWriter video;
	int width = (int) cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
				   (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	video.open("output.avi",cap.get(CV_CAP_PROP_FOURCC),
	    			cap.get(CV_CAP_PROP_FPS), S,true);

	if ( !video.isOpened() )
	{
		   std::cout << "ERROR: Failed to write the video" << std::endl;
		   return -1;
	}
	*/

	//namedWindow("Keypoints1",WINDOW_AUTOSIZE );
	//namedWindow("Keypoints2",WINDOW_AUTOSIZE );
	namedWindow("BestMatchesDisplay",WINDOW_AUTOSIZE );

	cout << "Press ESC to EXIT" << endl;

	first.read(cap);
	first.ORB();

	while(1){
		MyFeatureExtractor second(first);
		first.read(cap);
		matcher.clearing();
		first.ORB();
		matcher.matchD(first,second);
		matcher.separateMatches(first,second);
		matcher.getBestMatches(first,second);
		matcher.separateBestMatches(first,second);

		matcher.drawBestMatches(first,second);
		matcher.show("BestMatchesDisplay");

		try{
			//cout << matcher.best_train_[0] <<endl;
			//Mat matrix = findFundamentalMat(matcher.best_train_, matcher.best_query_, CV_FM_8POINT, 3, 0.99);
			Mat H = findHomography(matcher.query_,matcher.train_, RANSAC);
			//waitKey(100);
			//cvWriteFrame( writer, matcher.frame_);
			//video.write(first.frame_);
			//Point thisPoint = calculateDiff(matcher.best_train_,matcher.best_query_);
			//std::cout<<E<< std::endl;
			visualizer.MyLine(H);

		}
		catch (exception e){
			e.what();
		}


		/*

		Point thisPoint = calculateDiff(matcher.best_train_,matcher.best_query_);
		if (thisPoint.x!=0 && thisPoint.y!= 0){
			visualizer.MyLine(thisPoint);
		}
		*/

		if (char(waitKey(10)) == 27){
			break;
		}
	}
    cap.release();
    //matcher.destroyWindow("BestMatchesDisplay");
	//video.release();
	cout << "MVO finishing correctly" << endl;
	return true;
}
