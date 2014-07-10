// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdlib>
#include "./FaceObject.h"

using namespace std;
using namespace cv;

// ____________________________________________________________________________
std::vector<FaceObject> detectFaces(const string & folder, const string & file, const string & classifier)
{
  string face_cascade_name = "./Classifier/" + classifier + ".xml";
  CascadeClassifier face_cascade; 
  face_cascade.load(face_cascade_name);
  string path = folder + "/" + file;  
  Mat frame = imread(path);
  vector<Rect> faces;
  vector<FaceObject> faceObjects;

  if (!frame.empty()) {
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray); 
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    for (size_t i = 0; i < faces.size(); i++) {
      FaceObject faceObject;
      faceObject.fileName = file;
      faceObject.x = faces[i].x;
      faceObject.y = faces[i].y;
      faceObject.width = faces[i].width;
      faceObject.height = faces[i].height;
      faceObjects.push_back(faceObject);
    }
    cout << path  << " Number of Faces: " << faces.size() << endl;
    faces.clear();
  }
  return faceObjects;
}





