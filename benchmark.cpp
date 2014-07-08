#include "benchmark.h" 

double precision(int truePositives, int falsePositives)
{
	return (double) truePositives / (truePositives + falsePositives);
}

double recall(int truePositives, int falseNegatives)
{
	return (double) truePositives / (truePositives + falseNegatives);
}

double getOverlapAbs(const FaceObject &fo1, const FaceObject &fo2)
{
	// Compute center of each rectangle
	double cx1 = fo1.x + fo1.width * 0.5;
	double cy1 = fo1.y + fo1.height * 0.5;
	double cx2 = fo2.x + fo2.width * 0.5;
	double cy2 = fo2.y + fo2.height * 0.5;
	
	// Compute potential overlap in x and y direction
	double ox = fo1.width * 0.5 + fo2.width * 0.5 - std::abs(cx1 - cx2);
	double oy = fo1.height * 0.5 + fo2.height * 0.5 - std::abs(cy1 - cy2);
	
	// Check whether the rectangles overlap
	if(ox < 0 || oy < 0)
		return 0.0;
	
	// Compute overlap
	ox = std::min(ox, (double) std::min(fo1.width, fo2.width));
	oy = std::min(oy, (double) std::min(fo1.height, fo2.height));
	
	// Return overlapping area
	return ox * oy;
}

double getOverlapRel(const FaceObject &fo1, const FaceObject &fo2)
{
	double oa = getOverlapAbs(fo1, fo2); // overlapping area
	double a1 = fo1.width * fo1.height; // area rect 1
	double a2 = fo2.width * fo2.height; // area rect 2
	return oa / (a1 + a2 - oa);
}

void benchmark(const std::string &sAlgo, const std::string &sGrndtr, double threshold, bool useIDs)
{
	char sLogFilename[64];
	QString qAlgo = sAlgo.c_str();
	QString qGrndtr = sGrndtr.c_str();
	QDir dirAlgo = qAlgo;
	QDir dirGrndtr = qGrndtr;
	std::string sFullpathAlgo, sFilename, sFullpathGrndtr;
	int tp = 0;
	int tpTotal = 0;
	int fpTotal = 0;
	int fnTotal = 0;
	
	// Determine the name of the logfile
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sLogFilename,64,"%Y-%m-%d_%H-%M-%S",timeinfo);
	sprintf(sLogFilename,"%s.log",sLogFilename);
	printf("Log File: %s\n",sLogFilename);
	
	// Open logfile
	std::ofstream ofLog;
	ofLog.open(sLogFilename);
	
	// Write logfile header
	ofLog << sLogFilename << std::endl;
	ofLog << std::endl;
	ofLog << "Algorithm:    " << sAlgo << std::endl;
	ofLog << "Ground truth: " << sGrndtr << std::endl;
	ofLog << "Threshold = " << threshold << std::endl;
	ofLog << "Use IDs = " << useIDs << std::endl;
	ofLog << std::endl;
	ofLog << "=====================================" << std::endl;
	ofLog << std::endl;

	// How many TP do we get if we match GrndtrID to AlgoID
	std::map<int, std::map<int, int> > mTP; // TruePositives = mTP[GrndtrID][AlgoID]
	
	// Iterate folders
	dirAlgo.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
	QDirIterator itDirAlgo(dirAlgo);
	while(itDirAlgo.hasNext())
	{
		itDirAlgo.next();
		sFullpathAlgo = itDirAlgo.filePath().toUtf8().constData();
		sFilename = itDirAlgo.fileName().toUtf8().constData();
		sFullpathGrndtr = sGrndtr + "/" + sFilename;
		std::vector<FaceObject> vAlgo = readObjectFile(sFullpathAlgo);
		std::vector<FaceObject> vGrndtr = readObjectFile(sFullpathGrndtr);
		
		if(vAlgo.size() != 0 && vGrndtr.size() != 0)
		{
			// Compare FaceObjects of Algo and Grndtr
			double overlap[vAlgo.size()][vGrndtr.size()];
			for(int i=0; i<vAlgo.size(); i++)
			{
				for(int j=0; j<vGrndtr.size(); j++)
				{
					overlap[i][j] = getOverlapRel(vAlgo[i], vGrndtr[j]);
				}
			}
			
			// Count (possible) number of TP
			for(int k=0; k<vAlgo.size(); k++)
			{
				double dHighestOverlap = -1.0;
				int iHighest, jHighest;
				
				// get highest overlap value
				for(int i=0; i<vAlgo.size(); i++)
				{
					for(int j=0; j<vGrndtr.size(); j++)
					{
						if(overlap[i][j] > dHighestOverlap)
						{
							dHighestOverlap = overlap[i][j];
							iHighest = i;
							jHighest = j;
						}
					}
				}
				
				// Check whether it is a (possible) TP
				if(dHighestOverlap >= threshold)
				{
					if(useIDs)
						mTP[vGrndtr[jHighest].objectID][vAlgo[iHighest].objectID]++;
					else
						tp++;
				}
				else
				{
					break;
				}
				
				// Set row & col to -1 => Don't consider them in future
				for(int i=0; i<vAlgo.size(); i++)
				{
					overlap[i][jHighest] = -1.0;
				}
				for(int j=0; j<vGrndtr.size(); j++)
				{
					overlap[iHighest][j] = -1.0;
				}
			}
		}
		
		if(useIDs)
		{
			fpTotal += vAlgo.size();
			fnTotal += vGrndtr.size();
		}
		else
		{
			int fp = vAlgo.size() - tp;
			int fn = vGrndtr.size() - tp;
			
			tpTotal += tp;
			fpTotal += fp;
			fnTotal += fn;
			
			// Write logfile entry
			ofLog << sFilename << std::endl;
			ofLog << "tp = " << tp << ", fp = " << fp << ", fn = " << fn;
			ofLog << ", pr = " << precision(tp, fp);
			ofLog << ", rc = " << recall(tp, fn) << std::endl;
			
			tp = 0;
		}
	}
	
	// Only relevant with useIDs = true
	std::map<int, std::map<int, int> >::iterator itGrndtr;
	ofLog << "AlgoID -> GrndtrID : Number of matches (= True Positives)" << std::endl;
	for(itGrndtr=mTP.begin(); itGrndtr!=mTP.end(); itGrndtr++)
	{
		int max = 0;
		int maxID;
		std::map<int, int>::iterator itAlgo;
		for(itAlgo=itGrndtr->second.begin(); itAlgo!=itGrndtr->second.end(); itAlgo++)
		{
			if(itAlgo->second > max)
			{
				max = itAlgo->second;
				maxID = itAlgo->first;
			}
		}
		tpTotal += max;
		fpTotal -= max;
		fnTotal -= max;
		
		// Write logfile entry
		ofLog << maxID << " -> " << itGrndtr->first << " : " << max << std::endl;
	}
	
	// Write logfile summary
	ofLog << std::endl;
	ofLog << "=====================================" << std::endl;
	ofLog << std::endl;
	ofLog << "Summary" << std::endl;
	ofLog << std::endl;
	ofLog << "True Positives  = " << tpTotal << std::endl;
	ofLog << "False Positives = " << fpTotal << std::endl;
	ofLog << "False Negatives = " << fnTotal << std::endl;
	ofLog << std::endl;
	ofLog << "Precision = " << precision(tpTotal, fpTotal) << std::endl;
	ofLog << "Recall    = " << recall(tpTotal, fnTotal) << std::endl;
	ofLog << std::endl;
}
