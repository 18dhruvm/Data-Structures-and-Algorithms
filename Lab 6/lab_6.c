#include<stdlib.h>
#include<stdio.h>

int *queue;
int size;
int *stack1,*stack2;
int front=0;int rear=0;
struct node* head1;
struct node* head2;

struct node 
{
    int data;
    struct node *next;
};

struct node* insert(int x) 
{
    struct node*temp = (struct node*)malloc(sizeof(struct node));
    temp->data = x;
    temp->next = NULL;
    return temp;
}

int push(int x,struct node* *root) 
{
    if(*root==NULL) 
    {
        struct node* temp = insert(x);
        *root = temp;
    }
    
    struct node* temp = insert(x);
    temp->next = *root;
    *root = temp;
    return 1;
}

int pop(struct node* *root) 
{
    if(*root == NULL) 
    {
        return 0;
    }
    struct node* temp = *root; //check wheter *root or root
    int temp_data = temp->data;
    *root = temp->next;
    return temp_data;
}

int enqueue(int x) 
{
    push(x,&head2);
    printf("Enqueued %d\n",x);
    rear++;
}

int dequeue() 
{
    if(front==rear) 
        return 0;
    int x=0;
    struct node* temp2 = head2;
    while(temp2!=NULL) 
    {
        x = pop(&head2);
        push(x,&head1);
        temp2 = temp2->next;
    }
    
    int y = pop(&head1);
    struct node* temp1 = head1;
    while(temp1!=NULL) 
    {
        x = pop(&head1);
        push(x,&head2);
        temp1 = temp1->next;
    }
    
    front++;
    return y;
}

void main() 
{
    printf("1: enqueue\n2: dequeue\n3: exit\n");
    while(1) 
    {
        printf("\nEnter option: ");
        int c;
        scanf("%d",&c);
        switch(c) 
        {
            case 1:
                printf("Enter a value to enqueue: ");
                int x;
                scanf("%d",&x);
                enqueue(x);
                break;
            case 2:
                x = dequeue();
                if(x==0) printf("Queue Empty\n");
                else printf("Dequeued %d",x);
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Please enter a valid number\n");
        }
    }
}