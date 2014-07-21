// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#ifndef RECOGNITIONOPENCV_H
#define RECOGNITIONOPENCV_H

#include "./FaceObject.h"

void recognizeLBPHistogramsOpenCV(std::vector<std::vector<FaceObject> > & faceObjects);

void recognizeFisherfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects);

void recognizeEigenfacesOpenCV(std::vector<std::vector<FaceObject> > & faceObjects);

#endif // RECOGNITIONOPENCV_H
