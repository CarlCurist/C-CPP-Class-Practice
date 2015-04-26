#include<cstdio>
#include"iterator.h"


Iterator::Iterator(Queue a)
{
    head=current=a.head;
}
int Iterator::printQueue()
{
    Node *temp;
    for(temp=head;temp!=NULL;temp=temp->next)
    {
        printf("%d ",temp->value);
    }
    return 0;
}

bool Iterator::next()
{
    if(NULL==current->next)
        return false;
    current=current->next;
    return true;
}

int Iterator::getCurrentValue()
{
    return current->value;
}

bool Iterator::jmpTo(int offset)
{
    Node *temp=head;
    for(int i=0;i<offset;i++)
    {
        if(NULL==temp->next)
            return false;
        temp=temp->next;
    }
    current=temp;
    return true;
}
