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

#include "readWriteObjectFile.h"

double precision(int truePositives, int falsePositives);
double recall(int truePositives, int falseNegatives);

// Computes absolute overlap of two FaceObjects
double getOverlapAbs(const FaceObject &fo1, const FaceObject &fo2);
// Computes relative overlap of two FaceObjects
double getOverlapRel(const FaceObject &fo1, const FaceObject &fo2);
// Compares algo and ground truth.
// threshold: range 0 to 1. Face is a True Positive, if overlap >= threshold.
// useIDs: Whether to run benchmark for detection or recognition.
void benchmark(const std::string &sAlgo, const std::string &sGrndtr, double threshold, bool useIDs);

#endif
