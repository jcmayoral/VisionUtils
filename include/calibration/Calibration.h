/*
 * Calibration.h
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//Based on http://docs.opencv.org/trunk/d4/d94/tutorial_camera_calibration.html

#include "Settings.h"
using namespace std;

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

class Calibration {
public:
	Calibration();
	virtual ~Calibration();
	bool Calibrate();
	bool getSettings();
	bool runCalibrationAndSave(Settings& s, Size imageSize, Mat& cameraMatrix, Mat& distCoeffs,
	                           vector<vector<Point2f> > imagePoints);
	bool runCalibration( Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, \
	                            vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs,\
	                            vector<float>& reprojErrs,  double& totalAvgErr);
	double computeReprojectionErrors( const vector<vector<Point3f> >& objectPoints,
	                                         const vector<vector<Point2f> >& imagePoints,
	                                         const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	                                         const Mat& cameraMatrix , const Mat& distCoeffs,
	                                         vector<float>& perViewErrors);
	void saveCameraParams( Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
	                              const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	                              const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints,
	                              double totalAvgErr );

	Settings settings;

};

#endif /* CALIBRATION_H_ */
