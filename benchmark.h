// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <cmath>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <QDir>
#include <QDirIterator>
#include <map>
#include <sstream>

#include "readWriteObjectFile.h"

struct benchmarkResult
{
    benchmarkResult();
    std::string toString();
    int truePositives, falsePositives, falseNegatives;
    double precision, recall;
    std::string logFileName;
};

double precision(int truePositives, int falsePositives);
double recall(int truePositives, int falseNegatives);

// Computes absolute overlap of two FaceObjects
double getOverlapAbs(const FaceObject &fo1, const FaceObject &fo2);

// Computes relative overlap of two FaceObjects
// returns: overlapping area / total area
double getOverlapRelToTotalArea(const FaceObject &fo1, const FaceObject &fo2);

// Computes relative overlap of two FaceObjects
// returns: 1.0 if algo area is totally inside ground truth area
//			else: overlapping area / ground truth area
double getOverlapRelToGrndtr(const FaceObject &foAlgo, const FaceObject &foGrndtr);

// Compares algo and ground truth.
// sAlgo: Directory of face object files of algorithm
// sGrndtr: Directory of face object files of ground truth.
// threshold: range 0 to 1. Face is a True Positive, if overlap >= threshold.
// writeLogFile: Whether to write a logfile or not.
// vAlgo: returns a vector containing all FaceObjects of sAlgo.
// vGrndtr: returns a vector containing all FaceObjects of sGrndtr.
benchmarkResult benchmarkDetectionBase(const std::string &sAlgo, const std::string &sGrndtr, double threshold, bool writeLogFile, std::vector<FaceObject> &vAlgoGes, std::vector<FaceObject> &vGrndtrGes);
benchmarkResult benchmarkDetection(const std::string &sAlgo, const std::string &sGrndtr, double threshold);
benchmarkResult benchmarkRecognition(const std::string &sAlgo, const std::string &sGrndtr, double threshold);

// Help functions
std::string openLogfile(std::ofstream &ofLog, const std::string &sAlgo, const std::string &sGrndtr, double threshold, const std::string &sFunction);
void writeSummaryToLogFile(std::ofstream &ofLog, const benchmarkResult &bRes, int iNumFacesGrndtr, int iNumFacesAlgo);

#endif
