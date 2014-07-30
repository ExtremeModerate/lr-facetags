// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#ifndef RECOGNITIONOPENCV_H
#define RECOGNITIONOPENCV_H

#include "./FaceObject.h"

void recognizeLBPHistogramsOpenCV(std::vector<std::vector<FaceObject> > & faceObjects, std::vector<cv::Mat> images, std::vector<int> labels);

void recognizeFisherfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects, std::vector<cv::Mat> images, std::vector<int> labels);

void recognizeEigenfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects, std::vector<cv::Mat> images, std::vector<int> labels);

#endif // RECOGNITIONOPENCV_H
