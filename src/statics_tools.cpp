#include<statics/statics_tools.h>

using namespace std;
using namespace cv;

MyStatics::MyStatics(){
}

MyStatics::~MyStatics(){
}

void MyStatics::getKMeans(const Matcher input){
    Mat labels(30, 40, DataType<float>::type);
    Mat centers(1, 1, DataType<float>::type);
    Mat img(300, 400, DataType<float>::type);
    Scalar colorTab[] =
        {
            Scalar(0, 0, 255),
            Scalar(0,255,0),
            Scalar(255,100,100),
            Scalar(255,0,255),
            Scalar(0,255,255)
        };

    kmeans(input.best_train_, 1, labels,
               TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
                  3, KMEANS_PP_CENTERS, centers);

    for(uint i = 0; i < input.best_matches_.size(); i++ )
            {
                int clusterIdx = labels.at<int>(i);
                Point ipt = input.best_train_.at(i);
                circle( img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA );
            }
    imshow("clusters", img);
}
