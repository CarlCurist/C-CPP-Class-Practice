class SafeArray
{
public:
    SafeArray(int size);
    ~SafeArray();
    int SetValue(int offset,int value);
    int GetValue(int offset);
private:
    int *Array=0;
    int ArraySize=0;
};
