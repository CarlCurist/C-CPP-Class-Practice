#include <iostream>
#include "Circle.h"

using namespace std;

int main()
{

    Circle circle(10,20,5);
    circle.move(30,20);

    cout<<circle.getCenter().getX()<<":"<<circle.getCenter().getY()<<endl;

    return 0;
}

