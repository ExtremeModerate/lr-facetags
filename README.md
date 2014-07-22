lr-facetags
===========

# Installation

Requirements: OpenCV, QT

1. qmake
2. make
3. ./lr-facetags


# Usage

For the datatool usage see: [Datasettools2](https://github.com/mll-freiburg/lr-facetags/wiki/Datasettools2)

1. Select a image folder with the "Open Folder" button or by typing the path into box beside the button
  - Subfolders are not considered
  - The image folder path musst always be correct

2. Face Detection 
  - Select the detection classifier in the drop down box
  - Press "Detect Faces"

3. Face Recognition
  - Check that you detected Faces at least once
  - Select the recognition algorithm in the drop down box
  - Press "Recognize Faces"

4. Benchmarking 
  - Check if the ground truth exists, if not create one with the datatool
  - For each detection run a subfolder with the timestamp will be created in: ImageFolder/.metaface/TIMESTAMP and a target will be added to the benchmarking selection
  - By pressing "Laod Single Run" or "Load All Runs" you can previous runs for benchmarking
  - Press "Compare Detection" to start the face detection benchmarking
  - Press "Compare Recognition"  to start the face recognition benchmarking


