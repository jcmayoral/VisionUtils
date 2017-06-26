#include<statics/statics_tools.h>

using namespace std;
using namespace cv;

MyStatics::MyStatics(){
}

MyStatics::~MyStatics(){
}

void MyStatics::getGaussian(const Matcher input){

      const int nrolls=input.best_train_.size();  // number of experiments
      const int nstars=100;    // maximum number of stars to distribute

      Mat img(nrolls,nrolls, DataType<float>::type);

      double meanX = 0;
      double meanY = 0;

      //for (int k=0; k< nrolls; k++){
      //    meanX = meanX + input.best_train_[0].at(k);
      //    meanY = meanY + input.best_train_[0]-at(k);
      //}

      int p[10]={};

      for (int i=0; i<nrolls; ++i) {
        double number =0.0;
        if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
      }

      std::cout << "normal_distribution (5.0,2.0):" << std::endl;

      for (int i=0; i<10; ++i) {
        std::cout << i << "-" << (i+1) << ": ";
        std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
      }

    imshow("clusters", img);
}

void MyStatics::getKMeans(const Matcher input){
    Mat labels(1, 1, DataType<float>::type);
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

    try{
        kmeans(input.best_query_, 1, labels,
               TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
                  3, KMEANS_PP_CENTERS, centers);

        for(uint i = 0; i < input.best_query_.size(); i++ )
            {
                int clusterIdx = labels.at<int>(i);
                Point ipt = input.best_query_.at(i);
                circle( img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA );
            }
        imshow("clusters", img);
    }
    catch(Exception e){

    }
}
