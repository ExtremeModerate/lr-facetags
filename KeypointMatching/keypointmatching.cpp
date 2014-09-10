#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

const double THRESHOLD = 30;

// calculates the euclid distance
double euclidDistance(Mat& vec1, Mat& vec2) {
  double sum = 0.0;
  int dim = vec1.cols;
  for (int i = 0; i < dim; i++) {
    sum += (vec1.at<uchar>(0,i) - vec2.at<uchar>(0,i)) * (vec1.at<uchar>(0,i) -     vec2.at<uchar>(0,i));
  }
  return sqrt(sum);
}

// finds the index of nearest neighbor points of the keypoints
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
  int neighbor = -1;
  double minDist = 1e6;
  for (int i = 0; i < descriptors.rows; i++) {
    KeyPoint pt = keypoints[i];
    Mat v = descriptors.row(i);
    double d = euclidDistance(vec, v);
    //printf("%d %f\n", v.cols, d);
    if (d < minDist) {
      minDist = d;
      neighbor = i;
    }
  }
  if (minDist < THRESHOLD) {
    return neighbor;
    }
  return -1;
}

// finds points with smallest distance between them (pairs)
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
vector<KeyPoint>& keypoints2, Mat& descriptors2,
vector<Point2f>& srcPoints, vector<Point2f>& dstPoints) {
  for (int i = 0; i < descriptors1.rows; i++) {
    KeyPoint pt1 = keypoints1[i];
    Mat desc1 = descriptors1.row(i);
    int nn = nearestNeighbor(desc1, keypoints2, descriptors2);
    if (nn >= 0) {
      KeyPoint pt2 = keypoints2[nn];
      srcPoints.push_back(pt1.pt);
      dstPoints.push_back(pt2.pt);
    }
  }
}

// TODO: Main fnct which uses sift features for the NN-Algorithm
int main(int argc, char** argv) {
  if (argc < 2) {
    cerr << "Too few arguments" << endl;
    return -1;
  }
} 
