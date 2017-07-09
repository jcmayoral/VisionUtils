#include<monocularvision/matcher.h>
#include<opencv2/imgproc.hpp>

#ifndef STATICS_TOOLS_H
#define STATICS_TOOLS_H
class MyStatics{
    public:
    MyStatics();
    ~MyStatics();
    static void getKMeans(const Matcher input);
    static void getGaussian(const Matcher input);
    Point calculateDiff(std::vector<Point2f> train, std::vector<Point2f> query);

};
#endif // STATICS_TOOLS_H
