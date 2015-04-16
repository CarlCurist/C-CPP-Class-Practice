#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
};

struct Node* createNewList()//不使用首个节点
{
    struct Node *head=(struct Node*)malloc(sizeof(struct Node));
    head->value=0;
    head->next=NULL;
    return head;
}

int addNewNode(struct Node* head,int offset,int value)//offset表示添加的节点在链表中的标号，head为0号，往后依次递加
{
    int i;
    struct Node *temphead=head;
    for(i=0;i<offset;i++)
    {
        if(temphead->next!=NULL)
        {
            temphead=temphead->next;
        }
        else
        {
            goto error;
        }
    }
    if(temphead->next!=NULL)//如果后面还有节点就插入，否则直接添加
    {
        struct Node *temp=(struct Node*)malloc(sizeof(struct Node));
        temp->value=value;
        temp->next=temphead->next;
        temphead->next=temp;
    }
    else
    {
         struct Node *temp=(struct Node*)malloc(sizeof(struct Node));
         temphead->next=temp;
         temp->value=value;
         temp->next=NULL;
    }

    return 0;

    error:
    printf("要添加的节点偏移太大了\n");
    return 1;
}
void printList(struct Node *head)
{
    head=head->next;
    while(head!=NULL)
    {
        printf("%d ",head->value);
        head=head->next;
    }
    printf("\n");
}
int deleteNode(struct Node *head,int offset)
{
    int i;
    struct Node *temphead=head->next;
    struct Node *templast=head->next;
    for(i=0;i<offset;i++)
    {
        if(temphead->next!=NULL)
        {
            temphead=temphead->next;
        }
        else
        {
            goto error;
        }
        if(i!=0)
        {
            templast=templast->next;
        }
    }

    templast->next=temphead->next;
    free(temphead);
    return 0;

    error:
        printf("下标超过了链表长度\n");
        return 1;
}
int main()
{
    struct Node *head=createNewList();
    char step;
    int temp1,temp2;
    while(1)
    {
        printf("请输入你的操作符，a表示添加一个节点，d表示删除一个节点，p表示打印整个链表\n");
        fflush(stdin);//刷新输入缓冲区，去掉\n字符
        scanf("%c",&step);
        switch(step)
        {
            case 'a':
                {
                    printf("请输入添加节点的位置和该节点的值\n");
                    scanf("%d %d",&temp1,&temp2);
                    addNewNode(head,temp1,temp2);
                    break;
                }
            case 'd':
                {
                    printf("请输入要删除的节点的位置\n");
                    scanf("%d",&temp1);
                    deleteNode(head,temp1);
                    break;
                }
            case 'p':
                {
                    printList(head);
                    break;
                }
            default:
                {
                    printf("没有该指令\n");
                }
        }
    }
    return 0;
}
