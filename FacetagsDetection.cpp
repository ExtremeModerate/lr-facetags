// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace cv;

// ____________________________________________________________________________
void detectFaces(string & path, string & classifier)
{
  string face_cascade_name = "./Classifier/" + classifier + ".xml";
  CascadeClassifier face_cascade; 
  face_cascade.load(face_cascade_name);
  std::vector<Rect> faces;
  Mat frame_gray;
  Mat frame = imread(path);
  if (!frame.empty()) {  
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray); 
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    cout << path << endl << "Number of Faces: " << faces.size() << endl; 
 
    faces.clear();  
    }
}





