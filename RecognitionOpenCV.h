// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#ifndef RECOGNITIONOPENCV_H
#define RECOGNITIONOPENCV_H

#include "./FaceObject.h"

void recognizeOpenCV(std::vector<std::vector<FaceObject> > & faceObjects, const std::string & classifier, const std::string & folder);

#endif // RECOGNITIONOPENCV_H
