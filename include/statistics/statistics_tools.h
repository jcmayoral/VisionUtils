#include<opencv2/imgproc.hpp>
//#include <opencv2/plot.hpp>
#include "featuredetection/matcher.h"
#include <math.h>

#ifndef STATISTICS_TOOLS_H
#define STATISTICS_TOOLS_H
class MyStatistics{
  public:
    MyStatistics();
    ~MyStatistics();
    Point getKMeans(const Matcher input);
    Point calculateMean(Matcher match);
    Point calculateVariance(Matcher match, Point mean);
    double CalculateCovariance(Matcher match , double meanx, double meany);
    double CalculatePearsonCorrelation(Matcher match , double meanx, double meany, double varx, double vary);
    double CUSUM(Matcher input, double & last_mean, double & last_variance);
    double getBlur(Mat currentFrame);

};
#endif // STATISTICS_TOOLS_H
