#include"Point.h"
int Point::getX()
{
    return x;
}
int Point::getY()
{
    return y;
}
Point::Point(int x1,int y1)
{
        this->x=x1;
        this->y=y1;
}
void Point::move(int x,int y)
{
    this->x=x;
    this->y=y;
}
