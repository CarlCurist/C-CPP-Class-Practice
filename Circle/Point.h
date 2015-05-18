class Point
{
public:
    int getX();
    int getY();
    Point(int x1,int y1);
    void move(int x,int y);

private:
    int x=0;
    int y=0;
};
