#include "readWriteObjectFile.h"

// ______________________________________________________________________________________________
std::vector<FaceObject> readObjectFile(const std::string &sFilename)
{
	std::vector<FaceObject> vfo;
	std::ifstream ifObjFile(sFilename.c_str());
	int iObjectType;
	int iOcclusionLevel;
	
	while(ifObjFile) {
		FaceObject fo;
		ifObjFile >> iObjectType;
		fo.objectType = static_cast<ObjectType>(iObjectType);
		ifObjFile >> fo.objectID;
		ifObjFile >> fo.x;
		ifObjFile >> fo.y;
		ifObjFile >> fo.width;
		ifObjFile >> fo.height;
		ifObjFile >> fo.truncationLevel;
		ifObjFile >> iOcclusionLevel;
		fo.occlusionLevel = static_cast<OcclusionLevel>(iOcclusionLevel);
		
		if(ifObjFile)
			vfo.push_back(fo);
	}
	
	return vfo;
}


// ________________________________________________________________________________________________
bool writeObjectFile(const std::vector<FaceObject> &vfo, const std::string &sFilename, bool append)
{
	std::ofstream ofObjFile;
	if(append)
		ofObjFile.open(sFilename.c_str(), std::ofstream::app);
	else
		ofObjFile.open(sFilename.c_str());
	if(!ofObjFile) return false;
	for(int i=0; i<vfo.size(); i++)	{
		ofObjFile << static_cast<int>(vfo[i].objectType) << " ";
		ofObjFile << vfo[i].objectID << " ";
		ofObjFile << vfo[i].x << " ";
		ofObjFile << vfo[i].y << " ";
		ofObjFile << vfo[i].width << " ";
		ofObjFile << vfo[i].height << " ";
		ofObjFile << vfo[i].truncationLevel << " ";
		ofObjFile << static_cast<int>(vfo[i].occlusionLevel);
		ofObjFile << std::endl;
	}
	
	if(!ofObjFile) return false;
	ofObjFile.flush();
	
	return true;
}
