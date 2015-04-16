#include"SafeArrary.h"

SafeArray::SafeArray(int size)
{
    ArraySize=size;
    Array=new int[size];
}
SafeArray::~SafeArray()
{
    delete Array[];
}
int SafeArray::SetValue(int offset,int value)
{
    if(offset<0||offset>=ArraySize)
        return -1;
    else{
        //*(Array+offset)=value;
        Array[offset]=value;
        return 0;
    }

}
int SafeArray::GetValue(int offset)
{
    if(offset<0||offset>=ArraySize)
        return -1;
    else{
        //return *(Array+offset);
        return Array[offset];
    }
}

