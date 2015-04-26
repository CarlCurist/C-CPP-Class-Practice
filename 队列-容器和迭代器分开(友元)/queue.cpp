#define NULL 0
#include"queue.h"
#include<stdio.h>
int Queue::push(int value)
{
    if(NULL==head&&NULL==last)
    {
        head=last=new Node;
        head->value=value;
        head->next=NULL;
    }
    else
    {
        last->next=new Node;
        last=last->next;
        last->value=value;
        last->next=NULL;
    }
    return 0;
}
int Queue::pop()
{
    if(NULL==head)
    {
        return -1;
    }
    Node *temp=head;
    head=head->next;
    if(NULL==head)//如果指向队首的指针为空，则表示队列为空
        last=NULL;
    delete temp;
    return 0;
}
bool Queue::isEmpty()
{
    return NULL==head&&NULL==last;
}
int Queue::print()
{
    Node *temp=head;
    for(;NULL!=temp;temp=temp->next)
        printf("%d ",temp->value);
    return 0;
}
