/*
 * Settings.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include<calibration/Settings.h>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

Settings::Settings() {
	// TODO Auto-generated constructor stub

}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
}

void Settings::write(FileStorage& fs) const {

	fs << "{"
	   << "BoardSize_Width"  << boardSize.width
	   << "BoardSize_Height" << boardSize.height
	   << "Square_Size"         << squareSize
	   << "Calibrate_NrOfFrameToUse" << nrFrames
	   << "Calibrate_FixAspectRatio" << aspectRatio
	   << "Calibrate_AssumeZeroTangentialDistortion" << calibZeroTangentDist
	   << "Calibrate_FixPrincipalPointAtTheCenter" << calibFixPrincipalPoint
	   << "Write_DetectedFeaturePoints" << writePoints
	   << "Write_extrinsicParameters"   << writeExtrinsics
	   << "Write_outputFileName"  << outputFileName
	   << "Show_UndistortedImage" << showUndistorsed
	   << "Input_FlipAroundHorizontalAxis" << flipVertical
	   << "Input_Delay" << delay
	   << "Input" << input
	   << "}";
}

void Settings::read(const FileNode& node)                          //Read serialization for this class
{

	node["BoardSize_Width" ] >> boardSize.width;
	node["BoardSize_Height"] >> boardSize.height;
	node["Square_Size"]  >> squareSize;
	node["Calibrate_NrOfFrameToUse"] >> nrFrames;
	node["Calibrate_FixAspectRatio"] >> aspectRatio;
	node["Write_DetectedFeaturePoints"] >> writePoints;
	node["Write_extrinsicParameters"] >> writeExtrinsics;
	node["Write_outputFileName"] >> outputFileName;
	node["Calibrate_AssumeZeroTangentialDistortion"] >> calibZeroTangentDist;
	node["Calibrate_FixPrincipalPointAtTheCenter"] >> calibFixPrincipalPoint;
	node["Input_FlipAroundHorizontalAxis"] >> flipVertical;
	node["Show_UndistortedImage"] >> showUndistorsed;
	node["Input"] >> input;
	node["Input_Delay"] >> delay;
}
