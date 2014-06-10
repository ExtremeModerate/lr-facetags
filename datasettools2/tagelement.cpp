#include "tagelement.h"


TagElement::TagElement()
{
}

TagElement::TagElement(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
}

TagElement::TagElement(int objectType, QString objectID, int x, int y, int width, int height, double truncated, int occluded)
{
    this->objectType = objectType;
    this->objectID = objectID;
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    this->truncated = truncated;
    this->occluded = occluded;
}
