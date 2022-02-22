#include "StdAfx.h"

#include "Rectangle.h"


int CRectangle::SIDE_LENGTH = 32;


CRectangle::CRectangle() {
}
CRectangle::CRectangle(int x, int y, int typePar, bool walkablePar)
{
    top = y;
    left = x;
    type = typePar;
    walkable = walkablePar;
}
bool CRectangle::Intersect(int x1, int y1, int x2, int y2)
{

    if (x1 == x2 || y1 == y2 || left == right
        || top == bottom) {
        // the line cannot have positive overlap
        return false;
    }

    // If one rectangle is on left side of other
    if (x1 >= right || left >= x2)
        return false;

    // If one rectangle is above other
    if (y2 <= top || bottom <= y1)
        return false;

    return true;
}




