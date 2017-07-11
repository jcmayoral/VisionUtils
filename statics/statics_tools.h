#include<featuredetection/matcher.h>
#include<opencv2/imgproc.hpp>
#include <opencv2/plot.hpp>
#include <featuredetection/matcher.h>
#include <math.h>

#ifndef STATICS_TOOLS_H
#define STATICS_TOOLS_H
class MyStatics{
    public:
    MyStatics();
    ~MyStatics();
    Point getKMeans(const Matcher input);
    static void getGaussian(const Matcher input);
    Point calculateMean(Matcher match);
    Point calculateVariance(Matcher match, Point mean);

};
#endif // STATICS_TOOLS_H
