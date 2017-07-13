#include "../featuredetection/matcher.h"

Matcher::Matcher(): frame_(), matchPercentage_(0.10){

}

Matcher::~Matcher(){

}

void Matcher::setMatchPercentage(double val){
    matchPercentage_ = val;
}

void Matcher::matchD(MyFeatureExtractor ext1, MyFeatureExtractor ext2){
    match(ext1.descriptors_,ext2.descriptors_,matches_);
}

void Matcher::separateMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2){
    for (unsigned int i= 0; i< matches_.size();i++){
		query_.push_back(ext1.keypoints_[matches_[i].queryIdx].pt);
		train_.push_back(ext2.keypoints_[matches_[i].queryIdx].pt);
		//std::cout << matches_[i].distance << std::endl;
	}
}


void Matcher::separateBestMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2){
	for (unsigned int i= 0; i< best_matches_.size();i++){
		best_query_.push_back(ext1.keypoints_[best_matches_[i].queryIdx].pt);
		best_train_.push_back(ext2.keypoints_[best_matches_[i].queryIdx].pt);
		//std::cout << matches_[i].distance << std::endl;
	}
}

void Matcher::getBestMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2){
    /*From \cite{Mori2013} First Results in Deeting and Avoiding Frontal Obstacles from
    * A Monocular Camera fro Micro Unmanned Aerial Vehicles
    */
    for( int i = 0; i < ext1.descriptors_.rows; i++ ){
        if ((ext2.keypoints_[i].size > ext1.keypoints_[i].size)&& (matches_[i].distance<0.05)){
			best_matches_.push_back( matches_[i]);
		}
	}
}

void Matcher::drawBestMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2){
    drawMatches(ext1.frame_, ext1.keypoints_, ext2.frame_, ext2.keypoints_, best_matches_,frame_, Scalar::all(-1), Scalar::all(-1),std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
}

void Matcher::drawAllMatches(MyFeatureExtractor ext1, MyFeatureExtractor ext2){
	drawMatches(ext1.frame_, ext1.keypoints_, ext2.frame_, ext2.keypoints_, matches_,frame_, Scalar::all(-1), Scalar::all(-1),std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
}

void Matcher::show(std::string window_name){
    imshow(window_name, frame_);
}

void Matcher::clearing(){
	query_.clear();
	train_.clear();
	best_query_.clear();
	best_train_.clear();
	matches_.clear();
	best_matches_.clear();
}
