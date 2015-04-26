
struct Node
{
    int value;
    Node *next;
};

class Queue
{
    public:
        int push(int value);
        int pop();
        bool isEmpty();
        int print();
        friend class Iterator;
    private:
        Node *head=NULL;
        Node *last=NULL;
};
