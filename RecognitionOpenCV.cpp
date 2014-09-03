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

void recognizeLBPHistogramsOpenCV(vector<vector<FaceObject> > & faceObjects, vector<Mat> images, vector<int> labels) {
  Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
  int ctr = *max_element(labels.begin(), labels.end()), prediction;
  double confidence;

  // train model with given training set and labels
  model->train(images, labels);

  // iterate over every face
  for (size_t k = 0; k < faceObjects.size(); k++) {
    for (size_t l = 0; l < faceObjects[k].size(); l++) {
      if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) {
         model->predict(faceObjects[k][l].image, prediction, confidence);
         cout << faceObjects[k][l].fileName<<" "<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
         if (confidence > 75) {
           faceObjects[k][l].objectID = prediction;
           images.push_back(faceObjects[k][l].image);
           labels.push_back(prediction);
           //model->update(images, labels);
         }
         // new ID if face is unknown
         else {
           faceObjects[k][l].objectID = ctr;
           cout<<"creating new objectID: "<<faceObjects[k][l].objectID<<" for "<<faceObjects[k][l].fileName<<" "<< endl;
           images.push_back(faceObjects[k][l].image);
           labels.push_back(ctr);
           ctr++;
           //model->update(images, labels);
        }
         if(k<40)
             model->update(images, labels);
      }
    }
    if(k%10 == 0)
        model->update(images, labels);
    cout << "k=" << k << endl;
  }
}


void recognizeFisherfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects, vector<Mat> images, vector<int> labels) {
  Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
  int ctr = *max_element(labels.begin(), labels.end()), prediction;
  double confidence;

  // train model with given training set and labels
  model->train(images, labels);

  // iterate over every face
  for (size_t k = 0; k < faceObjects.size(); k++) {
    for (size_t l = 0; l < faceObjects[k].size(); l++) {
      if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) {
         model->predict(faceObjects[k][l].image, prediction, confidence);
         cout << faceObjects[k][l].fileName<<" "<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
         if (confidence > 300) {
             faceObjects[k][l].objectID = prediction; //cout << "Test 1" << endl;
           images.push_back(faceObjects[k][l].image); //cout << "Test 2" << endl;
           labels.push_back(prediction); //cout << "Test 3" << endl;
           //model->train(images, labels);
         }
         // new ID if face is unknown
         else {
           faceObjects[k][l].objectID = ctr;
           cout<<"creating new objectID: "<<faceObjects[k][l].objectID<<" for "<<faceObjects[k][l].fileName<<" "<< endl;
           images.push_back(faceObjects[k][l].image);
           labels.push_back(ctr);
           ctr++;
           //model->train(images, labels);
        }
          //cout << "Test 4" << endl;
         if(k<40)
             model->train(images, labels);
          //cout << "Test 5" << endl;
      }
      //cout << "l=" << l << endl;
    }
    if(k%10 == 0)
        model->train(images, labels);
    cout << "k=" << k << endl;
  }
}

void recognizeEigenfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects, vector<Mat> images, vector<int> labels) {
  Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
  int ctr = *max_element(labels.begin(), labels.end()), prediction;
  double confidence;

  // train model with given training set and labels
  model->train(images, labels);

  // iterate over every face
  for (size_t k = 0; k < faceObjects.size(); k++) {
    for (size_t l = 0; l < faceObjects[k].size(); l++) {
      if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) {
         model->predict(faceObjects[k][l].image, prediction, confidence);
         cout << faceObjects[k][l].fileName<<" "<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
         if (confidence > 2000) {
           faceObjects[k][l].objectID = prediction;
           images.push_back(faceObjects[k][l].image);
           labels.push_back(prediction);
           //model->train(images, labels);
         }
         // new ID if face is unknown
         else {
           faceObjects[k][l].objectID = ctr;
           cout<<"creating new objectID: "<<faceObjects[k][l].objectID<<" for "<<faceObjects[k][l].fileName<<" "<< endl;
           images.push_back(faceObjects[k][l].image);
           labels.push_back(ctr);
           ctr++;
           //model->train(images, labels);
        }
         if(k<40)
             model->train(images, labels);
      }
    }
    if(k%10 == 0)
        model->train(images, labels);
    cout << "k=" << k << endl;
  }
}
