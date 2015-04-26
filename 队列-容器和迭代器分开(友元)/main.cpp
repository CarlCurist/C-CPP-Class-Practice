#include <iostream>
#include"iterator.h"

using namespace std;

int main()
{
    Queue q;
    q.push(2);
    q.push(4);
    q.push(5);
    q.pop();
    q.push(6);

    Iterator iter(q);
    iter.jmpTo(1);
    cout<<iter.getCurrentValue();
    return 0;
}
