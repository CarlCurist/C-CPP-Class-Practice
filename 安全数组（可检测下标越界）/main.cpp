#include <iostream>
#include"SafeArrary.h"

using namespace std;

int main()
{
    SafeArray s(100);
    s.SetValue(0,2);
    s.SetValue(1,3);
    int a;
    a=s.GetValue(1);
    cout<<a;
    return 0;
}
