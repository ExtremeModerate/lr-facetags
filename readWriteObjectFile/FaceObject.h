enum ObjectType
{
	otFace,
	otDontCareFace
};

enum OcclusionLevel
{
	olNotOccluded,
	olPartlyOccluded,
	olLargelyOccluded,
	olUnknown
};

struct FaceObject
{
	ObjectType objectType;
	OcclusionLevel occlusionLevel;
	int objectID, x, y, width, height;
	float truncationLevel;
	
	FaceObject();
}; 
