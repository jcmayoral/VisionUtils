/*
 * MVO.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <monocularvision/MVO.h>
#include <statics/statics_tools.h>

using namespace cv;
using namespace std;

MVO::MVO() {
	// TODO Auto-generated constructor stub
    cout << "MVO Constructor" << endl;

}

MVO::~MVO() {
	// TODO Auto-generated destructor stub
	//cout << "MVO destroyed";
    //destroyWindow("clusters");
}

bool MVO::run(){

	VideoCapture cap( 0 );
    MyFeatureExtractor first;
    Tracker tracker;
    cout << "run " << endl;


    if (!cap.isOpened()){
    	cerr  << "Could not open the input video: " << endl;
	    return false;
	}

    Mat frame;
    cap >> frame;

    namedWindow("BestMatchesDisplay",WINDOW_AUTOSIZE );
    namedWindow("clusters",WINDOW_AUTOSIZE );

	cout << "Press ESC to EXIT" << endl;

	first.read(cap);
	first.ORB();

	while(1){
		MyFeatureExtractor second(first);
		first.read(cap);
        matcher_.clearing();
		first.ORB();
        matcher_.matchD(first,second);
        matcher_.separateMatches(first,second);
        matcher_.getBestMatches(first);
        matcher_.separateBestMatches(first,second);

        matcher_.drawBestMatches(first,second);
        matcher_.show("BestMatchesDisplay");
        cout<< matcher_.best_train_.size();


		try{
            Mat H = findHomography(matcher_.best_query_,matcher_.best_train_, RANSAC);
		}
		catch (exception e){
			e.what();
		}

		if (char(waitKey(10)) == 27){
			break;
		}
	}
    cap.release();
    matcher_.clearing();
    destroyAllWindows();
    cout << "MVO finishing correctly" << endl;
	return true;
}
