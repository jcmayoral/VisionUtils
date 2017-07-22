#include <statics/statics_tools.h>
#include<random>

using namespace std;
using namespace cv;

MyStatics::MyStatics(){
}

MyStatics::~MyStatics(){
}

Point MyStatics::calculateMean(Matcher match){

    int number_points = match.best_query_.size();
    Point tmp;
    tmp.x = 0;
    tmp.y = 0;

    for (unsigned int i=0; i<match.best_train_.size();i++){
        tmp.x = tmp.x + (match.best_query_[i].x);
        tmp.y = tmp.y + (match.best_query_[i].y);
    }

    if (number_points > 0){
        tmp.x /= number_points;
        tmp.y /= number_points;
    }

    return tmp;
}

Point MyStatics::calculateVariance(Matcher match, Point mean){
    int number_points = match.best_query_.size();
    Point tmp;
    tmp.x = 0;
    tmp.y = 0;
    for (unsigned int i=0; i<match.best_query_.size();i++){
        tmp.x += std::pow(match.best_query_[i].x - mean.x,2);
        tmp.y += std::pow(match.best_query_[i].y - mean.y,2);
    }

    if (number_points > 1){
        tmp.x /= (number_points-1);
        tmp.y /= (number_points-1);
    }

    else{
        tmp.x =0.0;
        tmp.y = 0.0;
    }

    return tmp;
}

double MyStatics::CalculateCovariance(Matcher match , double meanx, double meany){

    int number_points = match.best_query_.size();
    double tmp=0.0;

    if (number_points == 0){
        return 0.0;
    }

    for (unsigned int i=0; i<match.best_query_.size();i++){
        tmp += (match.best_query_[i].x - meanx) * (match.best_query_[i].y -meany);
    }

    if(number_points>0){
        tmp/=number_points;
    }
    else{
        tmp = 0.0;
    }
    return tmp;
}

double MyStatics::CalculatePearsonCorrelation(Matcher match , double meanx, double meany, double varx, double vary){

    int number_points = match.best_query_.size();
    double tmp=0.0;

    if (number_points == 0){
        return 0.0;
    }

    for (unsigned int i=0; i<match.best_query_.size();i++){
        tmp += (match.best_query_[i].x - meanx) * (match.best_query_[i].y -meany);
    }

    if((varx*vary)>1e-20){
        tmp/=(varx*vary);
    }

    return tmp;
}

double MyStatics::CUSUM(Matcher input){

    double cusum = 0.0;
    for (unsigned int i=0; i<input.best_matches_.size();i++){
      cusum += input.best_matches_[i].distance;
    }
    std::cout << "Cusum current value " << cusum << std::endl;
    return cusum;
}

Point MyStatics::getKMeans(const Matcher input){
    Point tmp(0,0);
    Mat labels(1, 1, DataType<float>::type);
    Mat centers(1, 1, DataType<float>::type);
    Mat img(300, 400, DataType<float>::type);
    Scalar colorTab[] ={
        Scalar(0, 0, 255),
        Scalar(0,255,0),
        Scalar(255,100,100),
        Scalar(255,0,255),
        Scalar(0,255,255)
    };

    try{
        kmeans(input.best_query_, 1, labels,
        TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
              3, KMEANS_PP_CENTERS, centers);

        for(uint i = 0; i < input.best_query_.size(); i++ ){
            int clusterIdx = labels.at<int>(i);
            Point ipt = input.best_query_.at(i);
            circle( img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA );
        }
    }
    catch(Exception e){
        e.what();
    }
   //imshow("centers", img);
  return tmp;

}
