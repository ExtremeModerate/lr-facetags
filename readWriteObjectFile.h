#ifndef READWRITEOBJECTFILE_H
#define READWRITEOBJECTFILE_H

/* Read and write functions for FaceObjects

File Definition:

Object Storage Format Definition

For each image we assume there is a corresponding .txt file. Named with the 
source image file name as prefix and the additional extension ".txt". (!case-sensitive)
e.G. for the image "lara.jpg" we assume the object file to be named "lara.jpg.txt".

The object files are separately stored for each directoryin a sub-folder
called ".metaface".

Example structure:
[/]
├── lara.jpg
├── 221.JPG
├── .metaface
│     ├── lara.jpg.txt
│     ├── 221.JPG.txt

In this files, each row defines an object in the following way:

[ObjectType] [ObjectId] [x] [y] [width] [height] [truncated] [occluded]

e.G.: Face 000001 15 15 60 60 0.5 3

The 8 columns represent:
#Values    Name      Description
----------------------------------------------------------------------------
   1    ObjectType   Describes the type of object: 0 = Face, 1 = DontCareFace
   1    ObjectId     Identification for grouping the same faces
   4    bbox         2D bounding box of object in the image:
                     contains left, top, width, height
   1    truncated    Float from 0 (non-truncated) to 1 (truncated), where
                     truncated refers to the object leaving image boundaries
   1    occluded     Integer (0,1,2,3) indicating occlusion state:
                     0 = fully visible, 1 = partly occluded
                     2 = largely occluded, 3 = unknown

Here, 'DontCareFace' labels denote regions in which objects have not been labeled,
for example because they don't appear anywhere else in the dataset. */

#include<vector>
#include<fstream>
#include "./FaceObject.h"

std::vector<FaceObject> readObjectFile(const std::string &sFilename);

bool writeObjectFile(const std::vector<FaceObject> &vfo, const std::string &sFilename, bool append=false);


#endif // READWRITEOBJECTFILE_H
