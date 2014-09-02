#include <iostream>
#include "benchmark.h"

benchmarkResult::benchmarkResult()
{
    truePositives = 0;
    falsePositives = 0;
    falseNegatives = 0;
    precision = 0.0;
    recall = 0.0;
}

std::string benchmarkResult::toString()
{
    std::stringstream str;
    str << "TP=" << truePositives;
    str << " FP=" << falsePositives;
    str << " FN=" << falseNegatives;
    str << " PR=" << precision;
    str << " RC=" << recall;
    return str.str();
}

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

double getOverlapRelToTotalArea(const FaceObject &fo1, const FaceObject &fo2)
{
	double oa = getOverlapAbs(fo1, fo2); // overlapping area
	double a1 = fo1.width * fo1.height; // area rect 1
	double a2 = fo2.width * fo2.height; // area rect 2
	return oa / (a1 + a2 - oa);
}

double getOverlapRelToGrndtr(const FaceObject &foAlgo, const FaceObject &foGrndtr)
{
	double oa = getOverlapAbs(foAlgo, foGrndtr); // overlapping area
	double aAlgo = foAlgo.width * foAlgo.height; // area foAlgo
	double aGrndtr = foGrndtr.width * foGrndtr.height; // area foGrndtr
	if(oa >= aAlgo && aAlgo / aGrndtr > 0.1)
	{
		return 1.0;
	}
	return aAlgo / aGrndtr;
}

std::string openLogfile(std::ofstream &ofLog, const std::string &sAlgo, const std::string &sGrndtr, double threshold, const std::string &sFunction)
{
    char cLogFilename[256];
    char cTmp[256];

    // Determine the name of the logfile
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(cTmp,256,"%Y-%m-%d_%H-%M-%S",timeinfo);
    sprintf(cLogFilename,"log/%s_%s.log",cTmp,(sAlgo.substr(sAlgo.find_last_of('/')+1)).c_str());
    std::string sLogFilename(cTmp);
    sLogFilename += "_"+(sAlgo.substr(sAlgo.find_last_of('/')+1));
    //sprintf(sLogFilename,"log/%s",sLogFilename);
    printf("Log File: %s\n",cLogFilename);
    if(!QDir("log").exists())
        QDir().mkdir("log");

    // Open logfile
    ofLog.open(cLogFilename);

    // Write logfile header
    ofLog << cLogFilename << std::endl;
    ofLog << std::endl;
    ofLog << "Algorithm:    " << sAlgo << std::endl;
    ofLog << "Ground truth: " << sGrndtr << std::endl;
    ofLog << "Threshold = " << threshold << std::endl;
    ofLog << "Function = " << sFunction << std::endl;
    ofLog << std::endl;
    ofLog << "=====================================" << std::endl;
    ofLog << std::endl;
    ofLog.flush();
    return sLogFilename;
}

void writeSummaryToLogFile(std::ofstream &ofLog, const benchmarkResult &bRes, int iNumFacesGrndtr, int iNumFacesAlgo)
{
    // Write logfile summary
    ofLog << std::endl;
    ofLog << "=====================================" << std::endl;
    ofLog << std::endl;
    ofLog << "Summary" << std::endl;
    ofLog << std::endl;
    ofLog << "Number of faces in Ground Truth:" << iNumFacesGrndtr << std::endl;
    ofLog << "Number of faces detected by Algorithm:" << iNumFacesAlgo << std::endl;
    ofLog << std::endl;
    ofLog << "True Positives  = " << bRes.truePositives << std::endl;
    ofLog << "False Positives = " << bRes.falsePositives << std::endl;
    ofLog << "False Negatives = " << bRes.falseNegatives << std::endl;
    ofLog << std::endl;
    ofLog << "Precision = " << bRes.precision << std::endl;
    ofLog << "Recall    = " << bRes.recall << std::endl;
    ofLog << std::endl;
    ofLog.flush();
}

void writeLogfileEntry(std::ofstream &ofLog, const std::string &sFilename, int tp, int fp, int fn)
{
    ofLog << sFilename << std::endl;
    ofLog << "# faces: " << tp+fn;
    ofLog << ", # detected faces: " << tp+fp << std::endl;
    ofLog << "tp = " << tp << ", fp = " << fp << ", fn = " << fn;
    ofLog << ", pr = " << precision(tp, fp);
    ofLog << ", rc = " << recall(tp, fn) << std::endl;
    ofLog.flush();
}

benchmarkResult benchmarkDetection(const std::string &sAlgo, const std::string &sGrndtr, double threshold)
{
    std::vector<FaceObject> vDummy1, vDummy2;
    return benchmarkDetectionBase(sAlgo, sGrndtr, threshold, true, vDummy1, vDummy2);
}

benchmarkResult benchmarkDetectionBase(const std::string &sAlgo, const std::string &sGrndtr, double threshold, bool writeLogFile, std::vector<FaceObject> &vAlgoGes, std::vector<FaceObject> &vGrndtrGes)
{
    QString qAlgo = sAlgo.c_str();
    QDir dirAlgo = qAlgo;
    std::string sFullpathAlgo, sFilename, sFullpathGrndtr;
    int tp = 0;
    benchmarkResult bRes;
    int iNumFacesGrndtr = 0;
    int iNumFacesAlgo = 0;
    int iSeqNo = 0;

    // Open logfile
    std::ofstream ofLog;
    if(writeLogFile)
        bRes.logFileName = openLogfile(ofLog, sAlgo, sGrndtr, threshold, "benchmarkDetection");

    // Iterate folders
    dirAlgo.setFilter(QDir::Files);
    QDirIterator itDirAlgo(dirAlgo);
    while(itDirAlgo.hasNext())
    {
        itDirAlgo.next();
        sFullpathAlgo = itDirAlgo.filePath().toUtf8().constData();
        sFilename = itDirAlgo.fileName().toUtf8().constData();
        sFullpathGrndtr = sGrndtr + "/" + sFilename;
        std::vector<FaceObject> vAlgo = readObjectFile(sFullpathAlgo);
        std::vector<FaceObject> vGrndtr = readObjectFile(sFullpathGrndtr);

        if(!QFile(sFullpathAlgo.c_str()).exists() || !QFile(sFullpathGrndtr.c_str()).exists())
            continue; // Go on if ground truth file and algo file exist.

        iNumFacesAlgo += vAlgo.size();
        iNumFacesGrndtr += vGrndtr.size();

        if(vAlgo.size() != 0 && vGrndtr.size() != 0)
        {
            // Compare FaceObjects of Algo and Grndtr
            double overlap[vAlgo.size()][vGrndtr.size()];
            for(size_t i=0; i<vAlgo.size(); i++)
            {
                for(size_t j=0; j<vGrndtr.size(); j++)
                {
                    overlap[i][j] = getOverlapRelToGrndtr(vAlgo[i], vGrndtr[j]);
                }
            }

            // Count number of TP
            for(size_t k=0; k<vAlgo.size(); k++)
            {
                double dHighestOverlap = -1.0;
                int iHighest = 0;
                int jHighest = 0;

                // get highest overlap value
                for(size_t i=0; i<vAlgo.size(); i++)
                {
                    for(size_t j=0; j<vGrndtr.size(); j++)
                    {
                        if(overlap[i][j] > dHighestOverlap)
                        {
                            dHighestOverlap = overlap[i][j];
                            iHighest = i;
                            jHighest = j;
                        }
                    }
                }

                // Check whether it is a TP
                if(dHighestOverlap >= threshold)
                    tp++;
                else
                    break;

                // Set row & col to -1 => Don't consider them in future
                for(size_t i=0; i<vAlgo.size(); i++)
                {
                    overlap[i][jHighest] = -1.0;
                }
                for(size_t j=0; j<vGrndtr.size(); j++)
                {
                    overlap[iHighest][j] = -1.0;
                }

                // Write seqNo to FO Grndtr and FO Algo
                vAlgo[iHighest].iSequentialNumber = iSeqNo;
                vGrndtr[jHighest].iSequentialNumber = iSeqNo;
                iSeqNo++;
            }
            // Add FOs to return-vectors
            for(size_t i=0; i<vAlgo.size(); i++)
                vAlgoGes.push_back(vAlgo[i]);
            for(size_t i=0; i<vGrndtr.size(); i++)
                vGrndtrGes.push_back(vGrndtr[i]);
        }

        int fp = vAlgo.size() - tp;
        int fn = vGrndtr.size() - tp;

        bRes.truePositives += tp;
        bRes.falsePositives += fp;
        bRes.falseNegatives += fn;

        // Write logfile entry
        if(writeLogFile)
            writeLogfileEntry(ofLog, sFilename, tp, fp, fn);

        tp = 0;
    }

    bRes.precision = precision(bRes.truePositives, bRes.falsePositives);
    bRes.recall = recall(bRes.truePositives, bRes.falseNegatives);

    // Write logfile summary
    if(writeLogFile)
        writeSummaryToLogFile(ofLog, bRes, iNumFacesGrndtr, iNumFacesAlgo);

    return bRes;
}

void printAllocation(std::map<int, int> mObjectIDAlgo,
					std::map<int, int> mObjectIDGrndtr,
					std::map<int, bool> mAllocation)
{
	std::cout << "SeqNo\tID-GT\tID-Algo\tAlloc" << std::endl;
    std::map<int, bool>::iterator it;
    //for(it=mObjectIDGrndtr.begin(); it!=mObjectIDGrndtr.end(); it++)
    for(it=mAllocation.begin(); it!=mAllocation.end(); it++)
	{
		std::cout << it->first << "\t";
        std::cout << mObjectIDGrndtr[it->first] << "\t";
		std::cout << mObjectIDAlgo[it->first] << "\t";
        std::cout << it->second << std::endl;
	}
	std::cout << std::endl;
}

benchmarkResult benchmarkRecognition(const std::string &sAlgo, const std::string &sGrndtr, double threshold)
{
    benchmarkResult bRes;
    int iNumFacesGrndtr = 0;
    int iNumFacesAlgo = 0;
    std::map<int, bool> mAllocation;
	int iNumberOfAllocations = 0;
    bool bAllocationChanged = true;

    // Open logfile
    //std::ofstream ofLog;
    //openLogfile(ofLog, sAlgo, sGrndtr, threshold, "benchmarkRecognition");

    std::map<int, std::vector<int> > mSeqNoAlgo, mSeqNoGrndtr; // objectID -> seqNumbers
    std::map<int, int> mObjectIDAlgo, mObjectIDGrndtr; // seqNo -> objectID
    std::vector<FaceObject> vAlgo, vGrndtr;

    benchmarkDetectionBase(sAlgo, sGrndtr, threshold, false, vAlgo, vGrndtr);

    // Find out which FOs have the same ID in Algo
    for(size_t i=0; i<vAlgo.size(); i++)
    {
        //std::cout << "vAlgo[" << i << "].iSequentialNumber: " << vAlgo[i].iSequentialNumber << std::endl;
        if(vAlgo[i].iSequentialNumber == -1) continue;
        mSeqNoAlgo[vAlgo[i].objectID].push_back(vAlgo[i].iSequentialNumber);
        mObjectIDAlgo[vAlgo[i].iSequentialNumber] = vAlgo[i].objectID;
        iNumFacesAlgo++;
    }
    
    // Find out which FOs have the same ID in Grndtr
    for(size_t i=0; i<vGrndtr.size(); i++)
    {
        if(mObjectIDAlgo.count(vGrndtr[i].iSequentialNumber) == 0) continue;
        mSeqNoGrndtr[vGrndtr[i].objectID].push_back(vGrndtr[i].iSequentialNumber);
        mObjectIDGrndtr[vGrndtr[i].iSequentialNumber] = vGrndtr[i].objectID;
        iNumFacesGrndtr++;
        mAllocation[vGrndtr[i].iSequentialNumber] = false;
        //if(vGrndtr[i].iSequentialNumber==-1) std::cout << "-1: " << sFullpathGrndtr << std::endl;
    }

    //std::cout << "mObjectIDGrndtr.size()=" << mObjectIDGrndtr.size() << std::endl;
    //std::cout << "iNumFacesGrndtr=" << iNumFacesGrndtr << std::endl;
    //std::cout << "mAllocation.size()=" << mAllocation.size() << std::endl;

    // Compute allocation of Grndtr IDs and Algo IDs
    while(bAllocationChanged)
    {
        bAllocationChanged = false;
        std::map<int, bool>::iterator itAllocation;
        for(itAllocation=mAllocation.begin(); itAllocation!=mAllocation.end(); /*itAllocation++*/)
        {
            if(itAllocation->second)
            {
                itAllocation++;
                continue; // Allocation is already true
            }
            //std::cout << "itAllocation->first: " << itAllocation->first << std::endl;
            //if(mObjectIDGrndtr.find(itAllocation->first) == mObjectIDGrndtr.end() || mObjectIDAlgo.find(itAllocation->first) == mObjectIDAlgo.end())
            if(mObjectIDGrndtr.count(itAllocation->first) == 0 || mObjectIDAlgo.count(itAllocation->first) == 0)
            { // SeqNo does not exist -> False positive or false negative -> We do not consider them in recognition benchmark.
                //std::map<int, bool>::iterator itTmp = itAllocation;
                //std::cout << "out: " << itAllocation->first << std::endl;
                //itAllocation--;
                mAllocation.erase(itAllocation++);
                continue;
            }
            int iAllocationGain = 0;
            int idGrndtr = mObjectIDGrndtr[itAllocation->first];
            int idAlgo = mObjectIDAlgo[itAllocation->first];
            std::vector<int> vAllocationChanged;
            for(size_t j=0; j<mSeqNoGrndtr[idGrndtr].size(); j++)
            {
                int iSeqNo = mSeqNoGrndtr[idGrndtr][j];
                if(mObjectIDAlgo[iSeqNo] == idAlgo && !mAllocation[iSeqNo])
                {
                    iAllocationGain++;
                    vAllocationChanged.push_back(iSeqNo);
                }
                else if(mObjectIDAlgo[iSeqNo] != idAlgo && mAllocation[iSeqNo])
                {
                    iAllocationGain--;
                    vAllocationChanged.push_back(iSeqNo);
                }
                //if(iSeqNo == -1) std::cout << "-1 in for(size_t j=0; j<mSeqNoGrndtr[idGrndtr].size(); j++) " << idAlgo << " " << idGrndtr << std::endl;
            }
            for(size_t j=0; j<mSeqNoAlgo[idAlgo].size(); j++)
            {
                int iSeqNo = mSeqNoAlgo[idAlgo][j];
                if(mObjectIDGrndtr[iSeqNo] == idGrndtr && !mAllocation[iSeqNo])
                {
                    //iAllocationGain++;
                    //vAllocationChanged.push_back(iSeqNo);
                }
                else if(mObjectIDGrndtr[iSeqNo] != idGrndtr && mAllocation[iSeqNo])
                {
                    iAllocationGain--;
                    vAllocationChanged.push_back(iSeqNo);
                }
                //if(iSeqNo == -1) std::cout << "-1 in for(size_t j=0; j<mSeqNoAlgo[idAlgo].size(); j++) " << idAlgo << " " << idGrndtr << std::endl;
            }
            if(iAllocationGain > 0)
            {
				iNumberOfAllocations += iAllocationGain;
                bAllocationChanged = true;
                for(size_t j=0; j<vAllocationChanged.size(); j++)
                {
                    mAllocation[vAllocationChanged[j]] = mAllocation[vAllocationChanged[j]] ? false : true;
                    //if(vAllocationChanged[j] == -1) std::cout << "-1 in for(size_t j=0; j<vAllocationChanged.size(); j++) " << idAlgo << " " << idGrndtr << std::endl;
                }
            }
            itAllocation++;
        }
        //std::cout << "cnt: " << ++cnt << ", iNumberOfAllocations: " << iNumberOfAllocations << std::endl;
    }
    
    //std::cout << "Allocation:" << std::endl;
    //printAllocation(mObjectIDAlgo, mObjectIDGrndtr, mAllocation);
    
    bRes.truePositives = iNumberOfAllocations;
    bRes.falseNegatives = mAllocation.size() - iNumberOfAllocations;
    bRes.recall = recall(bRes.truePositives, bRes.falseNegatives);
    std::cout << "Number of different persons considered: " << mSeqNoGrndtr.size() << std::endl;
    std::cout << "Number of different persons recognized by the algorithm: " << mSeqNoAlgo.size() << std::endl;
    std::cout << "Number of considered faces: " << mAllocation.size() << std::endl;
    std::cout << "Number of faces recognized correctly: " << iNumberOfAllocations << std::endl;

    return bRes;
}

