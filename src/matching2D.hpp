#ifndef matching2D_hpp
#define matching2D_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <boost/circular_buffer.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"


int detKeypointsHarris(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis=false);
int detKeypointsShiTomasi(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis=false);
int detKeypointsModern(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, int detectorType, bool bVis=false);
int descKeypoints(boost::circular_buffer<DataFrame> *dataBuffer,  int descType);
int matchDescriptors( boost::circular_buffer<DataFrame>  *dataBuffer,  int descType, int matcherType, int selectorType);

//void matchDescriptors(std::vector<cv::KeyPoint> &kPtsSource, std::vector<cv::KeyPoint> &kPtsRef, cv::Mat &descSource, cv::Mat &descRef,
//                      std::vector<cv::DMatch> &matches, std::string descriptorType, std::string matcherType, std::string selectorType);


#endif /* matching2D_hpp */
