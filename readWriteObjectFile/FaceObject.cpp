#include "FaceObject.h"

FaceObject::FaceObject()
{
	objectType = otDontCareFace;
	occlusionLevel = olUnknown;
	objectID = -1;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	truncationLevel = 0.0;
}
