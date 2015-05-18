#include"Circle.h"
Point Circle::getCenter()
{
    return (Point)*this;
}

Circle::Circle(int x,int y,int r):Point(x,y)
{
    this->r=r;
}

