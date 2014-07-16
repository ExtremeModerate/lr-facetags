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
};

double precision(int truePositives, int falsePositives);
double recall(int truePositives, int falseNegatives);

// Computes absolute overlap of two FaceObjects
double getOverlapAbs(const FaceObject &fo1, const FaceObject &fo2);
// Computes relative overlap of two FaceObjects
double getOverlapRel(const FaceObject &fo1, const FaceObject &fo2);
// Compares algo and ground truth.
// sAlgo: Directory of face object files of algorithm
// sGrndtr: Directory of face object files of ground truth.
// threshold: range 0 to 1. Face is a True Positive, if overlap >= threshold.
benchmarkResult benchmarkDetection(const std::string &sAlgo, const std::string &sGrndtr, double threshold);
benchmarkResult benchmarkRecognition(const std::string &sAlgo, const std::string &sGrndtr, double threshold);

// Help functions
void openLogfile(std::ofstream &ofLog, const std::string &sAlgo, const std::string &sGrndtr, double threshold, const std::string &sFunction);
void writeSummaryToLogFile(std::ofstream &ofLog, const benchmarkResult &bRes, int iNumFacesGrndtr, int iNumFacesAlgo);

#endif
