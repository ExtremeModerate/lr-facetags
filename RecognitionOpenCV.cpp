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
              if (confidence > 250) {
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

/*
void recognizeFisherfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects) {
  Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
  vector<Mat> images;
  vector<int> labels;
  vector<vector<int> > positions;
  Mat image;
  string file;
  int ctr = 1, prediction;
  double confidence;
  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      if (faceObjects[i][j].objectID == -1) {          
        file = folder + faceObjects[i][j].fileName;
        image = imread(file);
        if (!image.empty()) {
          // crop the face
          Rect myROI(faceObjects[i][j].x, faceObjects[i][j].y, faceObjects[i][j].width, faceObjects[i][j].height);
          image = image(myROI);

          // convert to grayscale
          Mat image_gray;
          cvtColor(image, image_gray, COLOR_BGR2GRAY);
          equalizeHist(image_gray, image_gray);


          
          faceObjects[i][j].objectID = ctr;
          cout<<"creating new objectID: "<<faceObjects[i][j].objectID<<" for "<<faceObjects[i][j].fileName<<" face "<<j<< endl;
          images.push_back(image_gray);
          labels.push_back(ctr);
          ctr++;   
          model->train(images, labels);
        }
        // recognize all unknown faces with the newly trained model
        for (size_t k = 0; k < faceObjects.size(); k++) {
          for (size_t l = 0; l < faceObjects[k].size(); l++) {
            if (faceObjects[k][l].objectID == -1) { 
              file = folder + faceObjects[k][l].fileName;
              image = imread(file);
              if (!image.empty()) {
                // crop the face
                Rect myROI(faceObjects[k][l].x, faceObjects[k][l].y, faceObjects[k][l].width, faceObjects[k][l].height);
                image = image(myROI);

                // convert to grayscale
                Mat image_gray;
                cvtColor(image, image_gray, COLOR_BGR2GRAY);
                equalizeHist(image_gray, image_gray);

                model->predict(image_gray, prediction, confidence);
                if (confidence > 300) {
                  faceObjects[k][l].objectID = prediction;
                  images.push_back(image_gray);
                  labels.push_back(prediction);
                  cout << faceObjects[k][l].fileName<<" face: "<<l<<" recognized objectID: "<<faceObjects[k][l].objectID<<" confidence: " << confidence << endl;
                }
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
  string file;
  int ctr = 1, prediction;
  double confidence;
  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      if (faceObjects[i][j].objectID == -1) {          
        file = folder + faceObjects[i][j].fileName;
        image = imread(file);
        if (!image.empty()) {
          // crop the face
          Rect myROI(faceObjects[i][j].x, faceObjects[i][j].y, faceObjects[i][j].width, faceObjects[i][j].height);
          image = image(myROI);

          // convert to grayscale
          Mat image_gray;
          cvtColor(image, image_gray, COLOR_BGR2GRAY);
          equalizeHist(image_gray, image_gray);


          
          faceObjects[i][j].objectID = ctr;
          cout<<"creating new objectID: "<<faceObjects[i][j].objectID<<" for "<<faceObjects[i][j].fileName<<" face "<<j<< endl;
          images.push_back(image_gray);
          labels.push_back(ctr);
          ctr++;   
          model->train(images, labels);
        }
        // recognize all unknown faces with the newly trained model
        for (size_t k = 0; k < faceObjects.size(); k++) {
          for (size_t l = 0; l < faceObjects[k].size(); l++) {
            if (faceObjects[k][l].objectID == -1) { 
              file = folder + faceObjects[k][l].fileName;
              image = imread(file);
              if (!image.empty()) {
                // crop the face
                Rect myROI(faceObjects[k][l].x, faceObjects[k][l].y, faceObjects[k][l].width, faceObjects[k][l].height);
                image = image(myROI);

                // convert to grayscale
                Mat image_gray;
                cvtColor(image, image_gray, COLOR_BGR2GRAY);
                equalizeHist(image_gray, image_gray);

                model->predict(image_gray, prediction, confidence);
                if (confidence > 300) {
                  faceObjects[k][l].objectID = prediction;
                  images.push_back(image_gray);
                  labels.push_back(prediction);
                  cout << faceObjects[k][l].fileName<<" face: "<<l<<" recognized objectID: "<<faceObjects[k][l].objectID<<" confidence: " << confidence << endl;
                }
              }
            }
          }
        }          
      }
    }    
  } 
} */
