#ifndef TAGELEMENT_H
#define TAGELEMENT_H

#include <QString>

class TagElement
{
public:
    TagElement();
    TagElement(int x, int y, int width, int height);
    TagElement(int objectType, QString objectID, int x, int y, int width, int height, double truncated, int occluded);
    int x;
    int y;
    int width;
    int height;
    QString objectID;
    double truncated;
    int occluded;
    int objectType;




};

#endif // TAGELEMENT_H
