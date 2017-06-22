/*
 * Calibration.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

//Based on  http://docs.opencv.org/trunk/d4/d94/tutorial_camera_calibration.html
#include <iostream>
#include <string>
#include <ctime>

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"

#include "opencv2/opencv.hpp"
#include "../calibration/Calibration.h"
#include <unistd.h>

using namespace std;
using namespace cv;

Calibration::Calibration() {
	// TODO Auto-generated constructor stub

}

Calibration::~Calibration() {
	// TODO Auto-generated destructor stub
	cvDestroyAllWindows();
}

static inline void read(const FileNode& node, Settings& x, const Settings& default_value = Settings())
{
    if(node.empty()){
    	cout << "first";
    	x = default_value;
    }
    else{
    	x.read(node);
    }

}

static inline void write(FileStorage& fs, const String&, const Settings& s )
{
	cout << "write";
    s.write(fs);
}

bool Calibration::getSettings(){

	const string inputSettingsFile = "camcalibration.xml";
    FileStorage fs(inputSettingsFile, FileStorage::READ); // Read the settings

    if (!fs.isOpened())
	{
		cout << "Could not open the configuration file: \"" << inputSettingsFile << "\"" << endl;
		return false;
	}

	fs["Calibration"] >> settings;
	fs.release();
	return true;
}

bool Calibration::Calibrate(){


	if (!getSettings()){
    	cout << "Settings not gotten" << endl;
    	return false;
    }

    vector <Mat> calImages;
    vector<vector<Point2f> > imagePoints;
    Mat cameraMatrix, distCoeffs;
    Size imageSize;

    const Scalar RED(0,0,255), GREEN(0,255,0);
    bool isCalibrated;
    char key = '0';
    VideoCapture inputCapture(0);

    if (!inputCapture.isOpened()){
    	cerr << "camera not initialized" <<endl;
    	return false;
    }

    namedWindow( "Video", WINDOW_AUTOSIZE );
    //key = (char)waitKey();//(char)cin.get();
    cout << "Press 'e' to leave or 'a' to take a calibration picture" << endl;

    while(key != 'e'){
    //while(true){
    	Mat view;

    	inputCapture >> view;
    	imshow("Video",view);

    	key = char();
    	key = (char)waitKey(100);

    	if (key != 'a' && key != 'e'){
    		continue;
    	}

    	if(key =='a'){
    		cout<< "taking picture";
    		calImages.push_back(view);
    		imageSize = view.size();
    		vector<Point2f> pointBuf;

    		bool found;
    		int chessBoardFlags = CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE;

    		found = findChessboardCorners( view, settings.boardSize, pointBuf, chessBoardFlags);

    		if (found)                // If done with success,
    		{
    			// improve the found corners' coordinate accuracy for chessboard
    			Mat viewGray;
    			cvtColor(view, viewGray, COLOR_BGR2GRAY);
    			cornerSubPix( viewGray, pointBuf, Size(11,11),
    			Size(-1,-1), TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 30, 0.1 ));

    			imagePoints.push_back(pointBuf);
				// Draw the corners.
    			drawChessboardCorners( view, settings.boardSize, Mat(pointBuf), found );
    		}
    		else{
    			cerr << "Chessboard not found picture popped"<<endl;
    			calImages.pop_back();
    		}
    	}

    	if(key =='e'){
    		inputCapture.release();
    		cout << "Camera released" << endl;
    	}
    }

    if (calImages.size()>1){
    	isCalibrated = runCalibrationAndSave(settings, imageSize,  cameraMatrix, distCoeffs, imagePoints);

		if( isCalibrated && settings.showUndistorsed )
		{
			int i;
			cout << "Selecting an image to see undistorted image from 1 to "<< imagePoints.size()-1;
			cin >> i;
			Mat temp = calImages.at(i);
			undistort(temp, calImages.at(i), cameraMatrix, distCoeffs);
			imshow("Undistorted", temp);
		}
    }

    destroyAllWindows();
	return true;
}


bool Calibration::runCalibrationAndSave(Settings& s, Size imageSize, Mat& cameraMatrix, Mat& distCoeffs,
                           vector<vector<Point2f> > imagePoints)
{
    vector<Mat> rvecs, tvecs;
    vector<float> reprojErrs;
    double totalAvgErr = 0;

    bool ok = runCalibration(s, imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs, reprojErrs,
                             totalAvgErr);
    cout << (ok ? "Calibration succeeded" : "Calibration failed")
         << ". avg re projection error = " << totalAvgErr << endl;

    if (ok){
        saveCameraParams(s, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, reprojErrs, imagePoints,
                         totalAvgErr);
        cout << "Calibration File saved";
    }
    return ok;
}

bool Calibration::runCalibration( Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
                            vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs, \
                            vector<float>& reprojErrs,  double& totalAvgErr)
{
    //! [fixed_aspect]
    cameraMatrix = Mat::eye(3, 3, CV_64F);
    if( s.flag & CALIB_FIX_ASPECT_RATIO )
        cameraMatrix.at<double>(0,0) = s.aspectRatio;

    distCoeffs = Mat::zeros(8, 1, CV_64F);

    vector<vector<Point3f> > objectPoints(1);

    objectPoints.resize(imagePoints.size(),objectPoints[0]);

    //Find intrinsic and extrinsic camera parameters
    double rms;
    rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs,\
    		settings.flag);

    cout << "Re-projection error reported by calibrateCamera: "<< rms << endl;

    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

    totalAvgErr = computeReprojectionErrors(objectPoints, imagePoints, rvecs, tvecs, cameraMatrix,
                                            distCoeffs, reprojErrs);

    return ok;
}

double Calibration::computeReprojectionErrors( const vector<vector<Point3f> >& objectPoints,
                                         const vector<vector<Point2f> >& imagePoints,
                                         const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                                         const Mat& cameraMatrix , const Mat& distCoeffs,
                                         vector<float>& perViewErrors)
{
    vector<Point2f> imagePoints2;
    size_t totalPoints = 0;
    double totalErr = 0, err;
    perViewErrors.resize(objectPoints.size());

    for(size_t i = 0; i < objectPoints.size(); ++i )
    {
        projectPoints(objectPoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);
        err = norm(imagePoints[i], imagePoints2, NORM_L2);

        size_t n = objectPoints[i].size();
        perViewErrors[i] = (float) std::sqrt(err*err/n);
        totalErr        += err*err;
        totalPoints     += n;
    }

    return std::sqrt(totalErr/totalPoints);
}


void Calibration::saveCameraParams( Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
                              const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                              const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints,
                              double totalAvgErr )
{
    FileStorage fs( s.outputFileName, FileStorage::WRITE );

    time_t tm;
    time( &tm );
    struct tm *t2 = localtime( &tm );
    char buf[1024];
    strftime( buf, sizeof(buf), "%c", t2 );

    fs << "calibration_time" << buf;

    if( !rvecs.empty() || !reprojErrs.empty() )
        fs << "nr_of_frames" << (int)std::max(rvecs.size(), reprojErrs.size());
    fs << "image_width" << imageSize.width;
    fs << "image_height" << imageSize.height;
    fs << "board_width" << s.boardSize.width;
    fs << "board_height" << s.boardSize.height;
    fs << "square_size" << s.squareSize;

    if( s.flag & CALIB_FIX_ASPECT_RATIO )
        fs << "fix_aspect_ratio" << s.aspectRatio;

    fs << "camera_matrix" << cameraMatrix;
    fs << "distortion_coefficients" << distCoeffs;

    fs << "avg_reprojection_error" << totalAvgErr;

    if (s.writeExtrinsics && !reprojErrs.empty())
        fs << "per_view_reprojection_errors" << Mat(reprojErrs);

    if(s.writeExtrinsics && !rvecs.empty() && !tvecs.empty() )
    {
        CV_Assert(rvecs[0].type() == tvecs[0].type());
        Mat bigmat((int)rvecs.size(), 6, CV_MAKETYPE(rvecs[0].type(), 1));
        bool needReshapeR = rvecs[0].depth() != 1 ? true : false;
        bool needReshapeT = tvecs[0].depth() != 1 ? true : false;

        for( size_t i = 0; i < rvecs.size(); i++ )
        {
            Mat r = bigmat(Range(int(i), int(i+1)), Range(0,3));
            Mat t = bigmat(Range(int(i), int(i+1)), Range(3,6));

            if(needReshapeR)
                rvecs[i].reshape(1, 1).copyTo(r);
            else
            {
                //*.t() is MatExpr (not Mat) so we can use assignment operator
                CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
                r = rvecs[i].t();
            }

            if(needReshapeT)
                tvecs[i].reshape(1, 1).copyTo(t);
            else
            {
                CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
                t = tvecs[i].t();
            }
        }

        fs << "extrinsic_parameters" << bigmat;
    }

    if(s.writePoints && !imagePoints.empty() )
    {
        Mat imagePtMat((int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
        for( size_t i = 0; i < imagePoints.size(); i++ )
        {
            Mat r = imagePtMat.row(int(i)).reshape(2, imagePtMat.cols);
            Mat imgpti(imagePoints[i]);
            imgpti.copyTo(r);
        }
        fs << "image_points" << imagePtMat;
    }
}

