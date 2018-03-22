#include <statistics/statistics_tools.h>
#include<random>

using namespace std;
using namespace cv;

MyStatistics::MyStatistics(){
}

MyStatistics::~MyStatistics(){
}

Point MyStatistics::calculateMean(Matcher match){

    int number_points = match.getSize(2);
    std::vector<Point2f> v = match.getVector(2);
    Point tmp;
    tmp.x = 0;
    tmp.y = 0;

    for (unsigned int i=0; i<match.getSize(2);i++){
        tmp.x = tmp.x + (v.at(i).x);
        tmp.y = tmp.y + (v.at(i).y);
    }

    if (number_points > 0){
        tmp.x /= number_points;
        tmp.y /= number_points;
    }

    return tmp;
}

Point MyStatistics::calculateVariance(Matcher match, Point mean){
    int number_points = match.getSize(2);
    std::vector<Point2f> v = match.getVector(2);
    Point tmp;
    tmp.x = 0;
    tmp.y = 0;
    for (unsigned int i=0; i<match.getSize(2);i++){
        tmp.x += std::pow(v.at(i).x - mean.x,2);
        tmp.y += std::pow(v.at(i).y - mean.y,2);
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

double MyStatistics::CalculateCovariance(Matcher match , double meanx, double meany){

    int number_points = match.getSize(2);
    std::vector<Point2f> v = match.getVector(2);
    double tmp=0.0;

    if (number_points == 0){
        return 0.0;
    }

    for (unsigned int i=0; i<match.getSize(2);i++){
        tmp += (v[i].x - meanx) * (v[i].y -meany);
    }

    if(number_points>0){
        tmp/=number_points;
    }
    else{
        tmp = 0.0;
    }
    return tmp;
}

double MyStatistics::CalculatePearsonCorrelation(Matcher match , double meanx, double meany, double varx, double vary){

    int number_points = match.getSize(2);
    std::vector<Point2f> v = match.getVector(2);
    double tmp=0.0;

    if (number_points == 0){
        return 0.0;
    }

    for (unsigned int i=0; i<match.getSize(2);i++){
        tmp += (v[i].x - meanx) * (v[i].y -meany);
    }

    if((varx*vary)>1e-20){
        tmp/=(varx*vary);
    }
    else{
      return 0.0;
    }

    return tmp;
}

double MyStatistics::CUSUM(Matcher input,double & last_mean, double & last_variance){

    double cusum_mean, cusum_var, cusum, std_deviation, last_std_deviation = 0.0;
    std::vector<DMatch> v = input.getBestMatches();
    double max_value = input.getMatchPercentage();

    if (input.getSize(4)>1){
      for (unsigned int i=0; i<input.getSize(4);i++){
        cusum_mean += v[i].distance/max_value;
      }

      cusum_mean = cusum_mean/input.getSize(4);

      for (unsigned int i=0; i<input.getSize(4);i++){
          cusum_var += std::pow(v[i].distance - cusum_mean,2);
      }

      cusum_var = cusum_var/(input.getSize(4)-1);
      // BLANKE
      // s_z = (-np.power(z-m1,2) + np.power(z-m0,2))/(2*v1)
      std_deviation = sqrt(cusum_var);
      last_std_deviation = sqrt(last_variance);

      double constant = ((1/last_std_deviation) - (1/std_deviation))/2;
      double prefix_constant = log(last_std_deviation/std_deviation);

      for (unsigned int i=0; i<input.getSize(4);i++){
        cusum += prefix_constant + constant * pow((v[i].distance/max_value)-cusum_mean,2);
      }
    }
    last_mean = cusum_mean;
    last_variance = cusum_var;

    return cusum;
}

double MyStatistics::getBlur(Mat currentFrame){
  cv::Mat lap;
  cv::Laplacian(currentFrame, lap, CV_64F);

  cv::Scalar mu, sigma;
  cv::meanStdDev(lap, mu, sigma);

  double focusMeasure = sigma.val[0]*sigma.val[0];
  return focusMeasure;
}


Point MyStatistics::getKMeans(const Matcher input){
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

    Matcher c = input;
    std::vector<Point2f> v = c.getVector(2);

    try{
        kmeans(v, 1, labels,
        TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
              3, KMEANS_PP_CENTERS, centers);

        for(uint i = 0; i < v.size(); i++ ){
            int clusterIdx = labels.at<int>(i);
            Point ipt = v.at(i);
            circle( img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA );
        }
    }
    catch(Exception e){
        e.what();
    }
  return tmp;

}
