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

  if((varx*vary)>1e-10){
    tmp/=(varx*vary);
  }

  return tmp;
}


void MyStatics::getGaussian(const Matcher input){

  const int nrolls=input.best_train_.size();  // number of experiments
  const int nstars=100;    // maximum number of stars to distribute

  Mat img(nrolls,nrolls, DataType<float>::type);
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(5.0,2.0);

  //for (int k=0; k< nrolls; k++){
  //    meanX = meanX + input.best_train_[0].at(k);
  //    meanY = meanY + input.best_train_[0]-at(k);
  //}
  int p[10]={};

  for (int i=0; i<nrolls; ++i) {
    double number = distribution(generator);
    if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
  }

  std::cout << "normal_distribution (5.0,2.0):" << std::endl;

  for (int i=0; i<10; ++i) {
    std::cout << i << "-" << (i+1) << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }

  imshow("clusters", img);
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
  /*
  Mat plot_result;
  */
  centers.convertTo(centers,CV_64F);
  tmp.x = centers.at<double>(0,0);
  tmp.y = centers.at<double>(0,1);

  /*
  Ptr<cv::plot::Plot2d> plot;
  plot = cv::plot::createPlot2d(centers);
  plot->render(plot_result);
  imshow("centers", plot_result);
  */
  //imshow("centers", img);
  return tmp;

}
