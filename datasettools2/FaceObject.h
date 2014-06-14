// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#ifndef FACEOBJECT_H
#define FACEOBJECT_H

#include <string>

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
	ObjectType objectType;
	OcclusionLevel occlusionLevel;
    int x, y, width, height;
    std::string objectID;
	float truncationLevel;
	
	FaceObject();
}; 

#endif // FACEOBJECT_H
