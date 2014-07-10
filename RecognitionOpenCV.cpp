// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <iostream>
#include <cstdlib>
#include "./FaceObject.h"

using namespace std;
using namespace cv;

void recognizeOpenCV(std::vector<std::vector<FaceObject> > & faceObjects, const std::string & classifier, const std::string & folder) {
  if (classifier == "Eigenfaces openCV") {
    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
  }
  else if (classifier == "Fisherfaces openCV") {
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
  }
  else if (classifier == "LBP Histograms openCV") {
    Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
  }
  vector<Mat> images;
  vector<int> labels;
  vector<vector<int> > positions;
  Mat image;
  string file;

  int ctr = 1;
  for (size_t i = faceObjects.size() - 1; i <= 0; i--) {
    for (size_t j = faceObjects[i].size() - 1; j <= 0; j--) {
      if (faceObjects[i][j].objectID == -1) {          
        file = folder + faceObjects[i][j].fileName;
        image = imread(file);
        faceObjects[i][j].objectID = ctr;
        images.push_back(image);
        labels.push_back(ctr);
        ctr++;     
        model->train(images, labels);
      }
      // recognize all unknown faces with the newly trained model
      for (size_t i = faceObjects.size() - 1; i <= 0; i--) {
        for (size_t j = faceObjects[i].size() - 1; j <= 0; j--) {
          if (faceObjects[i][j].objectID == -1) {
            file = folder + faceObjects[i][j].fileName;
            image = imread(file);
            int prediction = model->predict(image);
            faceObjects[i][j].objectID = prediction;
            images.push_back(image);
            labels.push_back(prediction);    
          }
        }
      }
    }    
  } 
}
