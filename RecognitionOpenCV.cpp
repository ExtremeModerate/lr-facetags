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

void recognizeLBPHistogramsOpenCV(std::vector<std::vector<FaceObject> > & faceObjects) {
  Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
  vector<Mat> images;
  vector<int> labels;
  vector<vector<int> > positions;
  Mat image;
  int ctr = 1, prediction;
  double confidence;

  // fill the training set with two images, otherwise confidence varys too much
  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      if (faceObjects[i][j].objectID == -1 && !faceObjects[i][j].image.empty()) {          
        faceObjects[i][j].objectID = ctr;
        cout<<"creating new objectID: "<<faceObjects[i][j].objectID<<" for "<<faceObjects[i][j].fileName<<" "<<j<< endl;
        images.push_back(faceObjects[i][j].image);
        labels.push_back(ctr);
        model->train(images, labels);
        ctr++;
        if (ctr == 2) goto complete;

        for (size_t k = 0; k < faceObjects.size(); k++) {
          for (size_t l = 0; l < faceObjects[k].size(); l++) {
            if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) { 
              model->predict(faceObjects[k][l].image, prediction, confidence);
 cout << faceObjects[k][l].fileName<<" "<<l<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
              if (confidence > 1000) {
                faceObjects[k][l].objectID = prediction;
                images.push_back(faceObjects[k][l].image);
                labels.push_back(prediction);
                goto complete;
              }
            }
          }
        }          
      }
    }    
  }
complete: 


  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      if (faceObjects[i][j].objectID == -1 && !faceObjects[i][j].image.empty()) {          
        faceObjects[i][j].objectID = ctr;
        cout<<"creating new objectID: "<<faceObjects[i][j].objectID<<" for "<<faceObjects[i][j].fileName<<" "<<j<< endl;
        images.push_back(faceObjects[i][j].image);
        labels.push_back(ctr);
        ctr++;   
        model->train(images, labels);
       
        // recognize all unknown faces with the newly trained model
        for (size_t k = 0; k < faceObjects.size(); k++) {
          for (size_t l = 0; l < faceObjects[k].size(); l++) {
            if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) { 
              model->predict(faceObjects[k][l].image, prediction, confidence);
 cout << faceObjects[k][l].fileName<<" "<<l<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
              if (confidence > 50) {
                faceObjects[k][l].objectID = prediction;
                images.push_back(faceObjects[k][l].image);
                labels.push_back(prediction);
               
              }
            }
          }
        }          
      }
    }    
  }
}


void recognizeFisherfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects) {
   Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
  vector<Mat> images;
  vector<int> labels;
  vector<vector<int> > positions;
  Mat image;
  int ctr = 1, prediction;
  double confidence;

  // fill the training set with two images, otherwise confidence varys too much
  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      if (faceObjects[i][j].objectID == -1 && !faceObjects[i][j].image.empty()) {          
        faceObjects[i][j].objectID = ctr;
        cout<<"creating new objectID: "<<faceObjects[i][j].objectID<<" for "<<faceObjects[i][j].fileName<<" "<<j<< endl;
        images.push_back(faceObjects[i][j].image);
        labels.push_back(ctr);
        model->train(images, labels);
        ctr++;
        if (ctr == 2) goto complete;

        for (size_t k = 0; k < faceObjects.size(); k++) {
          for (size_t l = 0; l < faceObjects[k].size(); l++) {
            if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) { 
              model->predict(faceObjects[k][l].image, prediction, confidence);
 cout << faceObjects[k][l].fileName<<" "<<l<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
              if (confidence > 1000) {
                faceObjects[k][l].objectID = prediction;
                images.push_back(faceObjects[k][l].image);
                labels.push_back(prediction);
                goto complete;
              }
            }
          }
        }          
      }
    }    
  }
complete: 


  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      if (faceObjects[i][j].objectID == -1 && !faceObjects[i][j].image.empty()) {          
        faceObjects[i][j].objectID = ctr;
        cout<<"creating new objectID: "<<faceObjects[i][j].objectID<<" for "<<faceObjects[i][j].fileName<<" "<<j<< endl;
        images.push_back(faceObjects[i][j].image);
        labels.push_back(ctr);
        ctr++;   
        model->train(images, labels);
       
        // recognize all unknown faces with the newly trained model
        for (size_t k = 0; k < faceObjects.size(); k++) {
          for (size_t l = 0; l < faceObjects[k].size(); l++) {
            if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) { 
              model->predict(faceObjects[k][l].image, prediction, confidence);
 cout << faceObjects[k][l].fileName<<" "<<l<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
              if (confidence > 50) {
                faceObjects[k][l].objectID = prediction;
                images.push_back(faceObjects[k][l].image);
                labels.push_back(prediction);
               
              }
            }
          }
        }          
      }
    }    
  }
}

void recognizeEigenfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects) {
  Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
  vector<Mat> images;
  vector<int> labels;
  vector<vector<int> > positions;
  Mat image;
  int ctr = 1, prediction;
  double confidence;

  // fill the training set with two images, otherwise confidence varys too much
  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      if (faceObjects[i][j].objectID == -1 && !faceObjects[i][j].image.empty()) {          
        faceObjects[i][j].objectID = ctr;
        cout<<"creating new objectID: "<<faceObjects[i][j].objectID<<" for "<<faceObjects[i][j].fileName<<" "<<j<< endl;
        images.push_back(faceObjects[i][j].image);
        labels.push_back(ctr);
        model->train(images, labels);
        ctr++;
        if (ctr == 2) goto complete;

        for (size_t k = 0; k < faceObjects.size(); k++) {
          for (size_t l = 0; l < faceObjects[k].size(); l++) {
            if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) { 
              model->predict(faceObjects[k][l].image, prediction, confidence);
 cout << faceObjects[k][l].fileName<<" "<<l<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
              if (confidence > 1000) {
                faceObjects[k][l].objectID = prediction;
                images.push_back(faceObjects[k][l].image);
                labels.push_back(prediction);
                goto complete;
              }
            }
          }
        }          
      }
    }    
  }
complete: 


  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      if (faceObjects[i][j].objectID == -1 && !faceObjects[i][j].image.empty()) {          
        faceObjects[i][j].objectID = ctr;
        cout<<"creating new objectID: "<<faceObjects[i][j].objectID<<" for "<<faceObjects[i][j].fileName<<" "<<j<< endl;
        images.push_back(faceObjects[i][j].image);
        labels.push_back(ctr);
        ctr++;   
        model->train(images, labels);
       
        // recognize all unknown faces with the newly trained model
        for (size_t k = 0; k < faceObjects.size(); k++) {
          for (size_t l = 0; l < faceObjects[k].size(); l++) {
            if (faceObjects[k][l].objectID == -1 && !faceObjects[k][l].image.empty()) { 
              model->predict(faceObjects[k][l].image, prediction, confidence);
 cout << faceObjects[k][l].fileName<<" "<<l<<" recognized objectID: "<<prediction<<" confidence: " << confidence << endl;
              if (confidence > 50) {
                faceObjects[k][l].objectID = prediction;
                images.push_back(faceObjects[k][l].image);
                labels.push_back(prediction);
               
              }
            }
          }
        }          
      }
    }    
  }
}
