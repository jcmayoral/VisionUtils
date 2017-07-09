#include<monocularvision/matcher.h>
#include<opencv2/imgproc.hpp>
#include <monocularvision/matcher.h>


#ifndef STATICS_TOOLS_H
#define STATICS_TOOLS_H
class MyStatics{
    public:
    MyStatics();
    ~MyStatics();
    static void getKMeans(const Matcher input);
    static void getGaussian(const Matcher input);
    Point calculateDiff(Matcher match);

};
#endif // STATICS_TOOLS_H
