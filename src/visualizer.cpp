/*
 * visualizer.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: jose
 */


#include "../monocularvision/visualizer.h"

cv::Point3f operator*(cv::Mat M, const cv::Point3f& p)
{
    cv::Mat_<double> src(3/*rows*/,1 /* cols */);

    src(0,0)=p.x;
    src(1,0)=p.y;
    src(2,0)=p.z;

    cv::Mat_<double> dst = M*src; //USE MATRIX ALGEBRA
    return cv::Point3f(dst(0,0),dst(1,0),dst(2,0));
}

Visualizer::Visualizer() {

}
Visualizer::Visualizer(Mat frame) {
	// TODO Auto-generated constructor stub
	view_ = Mat(frame.rows,frame.cols, CV_8UC3, Scalar(255,255,255));
	namedWindow("Odometry",WINDOW_NORMAL );
	point_ = Point3f();
	point_.x = 0;
	point_.y = 0;
	point_.z = 1;
	std::cout << "beginning Point " << point_ << std::endl;
}

Visualizer::~Visualizer() {
	// TODO Auto-generated destructor stub
}

void Visualizer::MyLine(Mat H)
{

  int thickness = 2;
  int lineType = 8;
  Point3f tmp;
  std::cout << point_ << std::endl;
  tmp = H * point_;

  tmp.x /= tmp.z;
  tmp.y /= tmp.z;
  tmp.z /= tmp.z;
  std::cout << tmp << std::endl;

  line( view_,
		  Point(fabs(point_.x),fabs(point_.y)),
	          Point(fabs(tmp.x),fabs(tmp.y)),
	          Scalar( 0, 0, 255 ),
	          thickness,
	          lineType);
  point_.x = fabs(tmp.x);
  point_.y = fabs(tmp.y);
  point_.z = fabs(tmp.z);
  imshow("Odometry",view_);

};
