#include"queue.h"
class Iterator
{
public:
    Iterator(Queue a);
    int printQueue();//输出队列全部的值
    bool next();//将current指针向后移一位
    int getCurrentValue();//得到current目前指向的节点的值
    bool jmpTo(int offset);//将current指针指向距离队首偏移为offset的节点，offset=0时current指向队首
private:
    Node *head,*current;
};
