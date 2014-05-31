#include "readWriteObjectFile.h"

using namespace std;

int main()
{
	vector<FaceObject> vfo;
	
	FaceObject fo;
	fo.objectType = otFace;
	fo.objectID = 12345;
	fo.x = 15;
	fo.y = 20;
	fo.width = 60;
	fo.height = 50;
	fo.truncationLevel = 0.1;
	fo.occlusionLevel = olNotOccluded;
	
	vfo.push_back(fo);
	
	fo.objectType = otDontCareFace;
	fo.occlusionLevel = olUnknown;
	
	vfo.push_back(fo);
	
	// WRITE EXAMPLE 1
	writeObjectFile(vfo,"testObjectFile001.txt");
	
	vfo.clear();
	FaceObject fo2;
	vfo.push_back(fo2);
	
	// WRITE EXAMPLE 2, append to existing file.
	writeObjectFile(vfo,"testObjectFile001.txt",true);
	
	// READ EXAMPLE
	vector<FaceObject> vfo2 = readObjectFile("testObjectFile001.txt");
	
	for(int i=0; i<vfo2.size(); i++)
	{
		printf("___Objekt %i___\n",i);
		printf("objectType=%i\n",vfo2[i].objectType);
		printf("objectID=%i\n",vfo2[i].objectID);
		printf("x=%i\n",vfo2[i].x);
		printf("y=%i\n",vfo2[i].y);
		printf("width=%i\n",vfo2[i].width);
		printf("height=%i\n",vfo2[i].height);
		printf("truncationLevel=%f\n",vfo2[i].truncationLevel);
		printf("occlusionLevel=%i\n",vfo2[i].occlusionLevel);
	}
	
	return  0;
}
