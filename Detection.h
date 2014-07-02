// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#ifndef DETECTION_H
#define DETECTION_H

#include "./FaceObject.h"

// Detect Faces using the openCV Algorithm and a given Classifier
std::vector<FaceObject> detectFaces(const std::string & path, const std::string & classifier);

#endif // DETECTION_H
