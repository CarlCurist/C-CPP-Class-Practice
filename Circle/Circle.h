#include"Point.h"
class Circle:public Point
{
public:
    Circle(int x,int y,int r);
    Point getCenter();

private:
    int r;
};
