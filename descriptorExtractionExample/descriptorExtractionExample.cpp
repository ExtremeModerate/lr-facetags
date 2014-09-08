#include <stdio.h>
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

int main(int argc, char **argv)
{
	std::string sImgFilename = "../Images/detection01.jpg";
	cv::Mat img = cv::imread(sImgFilename, CV_LOAD_IMAGE_GRAYSCALE);
	std::vector<cv::KeyPoint> keypoints;

	cv::SiftFeatureDetector detector(64);
	detector.detect(img, keypoints);

	cv::SiftDescriptorExtractor extractor;
	cv::Mat descriptors;
	extractor.compute(img, keypoints, descriptors);

	cv::FileStorage fsWrite(sImgFilename+".xml", cv::FileStorage::WRITE);
	fsWrite << "keypoints" << keypoints;
	fsWrite << "descriptors" << descriptors;
	fsWrite.release();

	std::vector<cv::KeyPoint> keypoints_read;
	cv::Mat descriptors_read;

	cv::FileStorage fsRead(sImgFilename+".xml", cv::FileStorage::READ);
	cv::read(fsRead["keypoints"], keypoints_read);
	fsRead["descriptors"] >> descriptors_read;
	fsRead.release();

	cv::Mat imgOut;
	cv::drawKeypoints(img, keypoints, imgOut);
	cv::imshow("Keypoints", imgOut);

	cv::waitKey(0);
}
