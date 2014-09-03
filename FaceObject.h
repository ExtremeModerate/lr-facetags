// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#ifndef FACEOBJECT_H
#define FACEOBJECT_H

#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

enum ObjectType {
	otFace,
	otDontCareFace
};

enum OcclusionLevel {
	olNotOccluded,
	olPartlyOccluded,
	olLargelyOccluded,
	olUnknown
};

struct FaceObject {
    std::string fileName;
	ObjectType objectType;
	OcclusionLevel occlusionLevel;
    int objectID, x, y, width, height, iSequentialNumber;
	float truncationLevel;
	cv::Mat image; 
	FaceObject();
}; 

#endif // FACEOBJECT_H
