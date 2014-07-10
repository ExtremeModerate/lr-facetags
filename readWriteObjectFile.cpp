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
    ifObjFile >> fo.fileName;
    if (fo.fileName == "unknown") continue;
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
		
	  if(ifObjFile)	vfo.push_back(fo);
	  }
	return vfo;
}

// ________________________________________________________________________________________________
bool writeObjectFile(const std::vector<FaceObject> &vfo, const std::string &sPath, bool append)
{
	std::ofstream ofObjFile;
	if(append)
		ofObjFile.open(sPath.c_str(), std::ofstream::app);
	else
		ofObjFile.open(sPath.c_str());
	if(!ofObjFile) return false;
	for(size_t i=0; i<vfo.size(); i++)	{
    ofObjFile << vfo[i].fileName << " ";		
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

// ________________________________________________________________________________________________
bool writeObjectFileVector(const std::vector<std::vector<FaceObject> > &vfo, const std::string &sFolder, bool append)
{
  std::ofstream ofObjFile;
  std::string fullPath, fileName;  
  for (size_t j = 0; j < vfo.size(); j++) {
    fileName = vfo[j].front().fileName;
    fullPath = sFolder + fileName;
	  ofObjFile.clear();
	  if(append)
		  ofObjFile.open(fullPath.c_str(), std::ofstream::app);
	  else
		  ofObjFile.open(fullPath.c_str());
	  if(!ofObjFile) return false;
	  for(size_t i=0; i<vfo[j].size(); i++)	{
      ofObjFile << vfo[j][i].fileName << " ";		
      ofObjFile << static_cast<int>(vfo[j][i].objectType) << " ";
		  ofObjFile << vfo[j][i].objectID << " ";
		  ofObjFile << vfo[j][i].x << " ";
		  ofObjFile << vfo[j][i].y << " ";
		  ofObjFile << vfo[j][i].width << " ";
		  ofObjFile << vfo[j][i].height << " ";
		  ofObjFile << vfo[j][i].truncationLevel << " ";
		  ofObjFile << static_cast<int>(vfo[j][i].occlusionLevel);
		  ofObjFile << std::endl;
	   }
	
	   if(!ofObjFile) return false;
	   ofObjFile.flush();
	  }
	return true;
 }
