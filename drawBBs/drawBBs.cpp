#include <iostream>
#include <QImage>
#include <QDir>
#include <QDirIterator>
#include "../readWriteObjectFile.h"
#include <unistd.h>

using namespace std;

inline bool isIn(QImage &img, double x, double y)
{
    return x >= 0.0 && y >= 0.0 && x < img.width() && y < img.height();
}

void drawRect(QImage &img, double x, double y, double w, double h, QRgb color)
{
    for(int i=x; i<x+w; i++)
    {
        if(isIn(img,i,y))
            img.setPixel(i, y, color);
        if(isIn(img,i,y+h))
            img.setPixel(i, y+h, color);
    }
    for(int j=y; j<y+h; j++)
    {
        if(isIn(img,x,j))
            img.setPixel(x, j, color);
        if(isIn(img,x+w,j))
            img.setPixel(x+w, j, color);
    }
}

void drawBBs(const string &sImgFolder, const string &sFaceObjectFolder, QRgb color, bool add = true)
{
    QDir dirImgFolder(sImgFolder.c_str());
    QImage img;

    if(!QDir((sImgFolder+"/bb").c_str()).exists())
        QDir().mkdir((sImgFolder+"/bb").c_str());

    dirImgFolder.setFilter(QDir::Files);
    QDirIterator itDirImgFolder(dirImgFolder);
    while(itDirImgFolder.hasNext())
    {
        itDirImgFolder.next();
        string sFilename = itDirImgFolder.fileName().toUtf8().constData();
        if(add)
        {
            if(!img.load((sImgFolder+"/bb/"+sFilename).c_str()))
                continue;
        }
        else
            img.load(itDirImgFolder.filePath().toUtf8().constData());
        vector<FaceObject> vfo = readObjectFile(sFaceObjectFolder+"/"+sFilename+".txt");
        size_t i;
        for(i=0; i<vfo.size(); i++)
        {
            drawRect(img, vfo[i].x, vfo[i].y, vfo[i].width, vfo[i].height, color);
        }
        if(i>0)
            img.save((sImgFolder+"/bb/"+sFilename).c_str());
    }
}

void usage()
{
    printf("Description:\n\tDraws boxes to images. Images with boxes will be stored in <imagesFolder>/bb/.\n\n");
    printf("Usage:\n\tdrawBBs [OPTIONS] <imagesFolder> <FaceObjectFolder>\n\n");
    printf("OPTIONS:\n");
    printf("\t-r<int>\tRed value of color (0-255)\n");
    printf("\t-g<int>\tGreen value of color (0-255)\n");
    printf("\t-b<int>\tBlue value of color (0-255)\n");
    printf("\t-a\tAdd boxes to existing images\n");
    printf("\n");
    printf("<imagesFolder>: Path to folder where source images are stored.\n");
    printf("<FaceObjectFolder>: Path to folder where FaceObject files are stored.\n");
}

int main(int argc, char** argv)
{
    int c;
    char *images = NULL;
    char *bbs = NULL;
    int r = 0;
    int g = 0;
    int b = 0;
    bool add = false;

    while((c = getopt(argc, argv, "r:g:b:ah")) != -1)
    {
        switch(c)
        {
        case 'r':
            r = atoi(optarg);
            break;
        case 'g':
            g = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 'a':
            add = true;
            break;
        case 'h':
            usage();
            return 0;
        }
    }

    for(int i=optind; i<argc; i++)
    {
        if(i == optind)
            images = argv[i];
        else if(i == optind + 1)
            bbs = argv[i];
    }

    if(images == NULL)
    {
        printf("Error: Missing path of images\n");
        usage();
        return 1;
    }
    if(bbs == NULL)
    {
        printf("Error: Missing path of FaceObject files\n");
        usage();
        return 1;
    }

    QRgb color = qRgb(r, g, b);
    drawBBs(images, bbs, color, add);

	return 0;
}
