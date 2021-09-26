#include "helper.h"
#include "matching2D.hpp"

int readImage(std::string dataPath, int imgIndex,boost::circular_buffer<DataFrame> *dataBuffer){
    double t = (double)cv::getTickCount();
    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)
    std::string imgPrefix = "000000"; // left camera, color
    std::string imgFileType = ".png";
    std::ostringstream imgNumber;
    imgNumber << std::setfill('0') << std::setw(imgFillWidth) << imgIndex;
    std::string imgFullFilename = dataPath + imgPrefix + imgNumber.str() + imgFileType;
    // load image from file and convert to grayscale
    cv::Mat img ,imgGray;
    img = cv::imread(imgFullFilename);
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    // push image into data frame buffer
    DataFrame frame;
    frame.cameraImg = imgGray;
    dataBuffer->push_back(frame);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    return 1000 * t / 1.0;
}

int detectKeypoints(boost::circular_buffer<DataFrame> *dataBuffer,int detType){

    //// STUDENT ASSIGNMENT
    //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
    //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT
    std::vector<cv::KeyPoint> keypoints;

    double t = (double)cv::getTickCount();
    switch(detType){
    case 0: // SHITOMASI:
        detKeypointsShiTomasi(keypoints, (dataBuffer->end() - 1)->cameraImg, false);break;
    case 1: //HARRIS:
        detKeypointsHarris(keypoints, (dataBuffer->end() - 1)->cameraImg, false);break;
    case 2: case 3: case 4: case 5: case 6: //FAST: case BRISK: case ORB: case SIFT: case AKAZE:
        detKeypointsModern(keypoints, (dataBuffer->end() - 1)->cameraImg, detType, false); break;
    default: ;
    }

{
//        std::string windowName = detectorType_to_string(detType)+"  keypoints on  camera images";
//        cv::namedWindow(windowName, 7);
//        cv::Mat visImage = img.clone();
//        cv::drawKeypoints(img, keypoints, visImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//        cv::imshow(windowName, visImage);
//        std::cout << "Press key to continue to next image" << std::endl;
//        cv::waitKey(0); // wait for key to be pressed
//        continue;
}

    //// STUDENT ASSIGNMENT
    //// TASK MP.3 -> only keep keypoints on the preceding vehicle

    // only keep keypoints on the preceding vehicle

    bool bFocusOnVehicle = true;
    cv::Rect vehicleRect(535, 180, 180, 150);
    if (bFocusOnVehicle)
    {
        std::vector<cv::KeyPoint> vehiclekeypoints;
        for (auto kp : keypoints) {
            if (vehicleRect.contains(kp.pt)) vehiclekeypoints.push_back(kp);
        }
        keypoints = vehiclekeypoints;
{
//            std::string windowName = detectorType_to_string(detType)+" keypoint detection results";
//            cv::namedWindow(windowName);
//            cv::Mat visImage = img.clone();
//            cv::drawKeypoints(img, keypoints, visImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//            cv::imshow(windowName, visImage);
//            cv::waitKey(0);
//            continue;
}
    }

    //// EOF STUDENT ASSIGNMENT

    // optional : limit number of keypoints (helpful for debugging and learning)
    bool bLimitKpts = false;
    if (bLimitKpts)
    {
        int maxKeypoints = 50;

        if (detType==0)//SHITOMASI
        { // there is no response info, so keep the first 50 as they are sorted in descending quality order
            keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
        }
        cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
//      std::cout << " NOTE: Keypoints have been limited!" << std::endl;

    }

    // push keypoints and descriptor for current frame to end of data buffer

    (dataBuffer->end()-1)->keypoints = keypoints;

    return (((double)cv::getTickCount() - t)*1000.0) / cv::getTickFrequency();

    //// EOF STUDENT ASSIGNMENT
}
int descKeypoints_helper(boost::circular_buffer<DataFrame> *dataBuffer,  int descType){
return descKeypoints(dataBuffer,   descType);
}
int matchDescriptors_helper( boost::circular_buffer<DataFrame>  *dataBuffer,  int descType, int matcherType, int selectorType){
    return matchDescriptors( dataBuffer,  descType,  matcherType,  selectorType);
}
