// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;
using namespace cv;

// ____________________________________________________________________________
void detectFaces(string & path, string & classifier)
{
  string face_cascade_name = "./Classifier/" + classifier + ".xml";
  CascadeClassifier face_cascade; 
  face_cascade.load(face_cascade_name);
  Mat frame_gray;
  std::vector<Rect> faces;
  Mat frame = imread(path);
  if (!frame.empty()) {  
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    // Detect faces   
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    cout << path << endl << "Number of Faces: " << faces.size() << endl; 
/*
    // save face rectangles to a file
    detectedFaces.open("detectedFaces.csv", ios::app);
    for (size_t i = 0; i < faces.size(); i++) {
    detectedFaces << image << ";" << faces[i].x << ";" << faces[i].y << ";" << faces[i].width << ";" << faces[i].height << "\n";
    }
    detectedFaces.close();*/
      
    faces.clear();  
    }
    else {
      printf("--ERROR: this is no frame\n");
    }
}




