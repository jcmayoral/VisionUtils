#include<monocularvision/matcher.h>
#include<opencv2/imgproc.hpp>

#ifndef STATICS_TOOLS_H
#define STATICS_TOOLS_H
class MyStatics{
    public:
    MyStatics();
    ~MyStatics();
    static void getKMeans(const Matcher input);

};
#endif // STATICS_TOOLS_H
