#include<stdio.h>
#include<stdlib.h>
#include<stdint.h> /* for uint64 definition */ 

int count1=0;
struct node *start1 = NULL;
int count2=0;
struct node *start2 = NULL;

/*int isQueueFull()
{
    if (isStack2Full()==1)
        {return 1;}
    else
        {return 0;}
}*/

int isQueueEmpty()
{
    if (isEmpty2() == 1)
        {return 1;}
    else
        {return 0;}
}

int enQueue (int x)
{
   // if(isQueueFull())
     //   {return -1;}
    //else
    insert2(x); 
    printf("%d enqueued successfully",x);
return 1;}


int deQueue()
{
    if(isQueueEmpty())
    {printf("Error, stack is empty");
        return -1;}
    
    else
    {
        while (isEmpty2() == 0)  //stack2 is not empty
        {
            int x_1=delete2();
            insert1(x_1);
        }
    int y=delete1();
    while (isEmpty2() == 0) //stack2 is not empty
        {
            int x_2=delete1();
            insert2(x_2);
        }
        printf("%d dequeued successfully",y);
    return y;
        
    }
}

struct node
{
    int data;
    struct node *next;
};

void insert1(int x)
{
    struct node *temp;
    temp =(struct node*)malloc(sizeof(struct node*));
    temp->data = x;
    temp->next = NULL;
	
	struct node *p = start1;
    for (int i = 0; i < count1-1; i++)
        p = p->next;

    temp->next = p->next; 
     p->next = temp;
    count1++;
    
}
void insert2(int x)
{
    struct node *temp;
    temp =(struct node*)malloc(sizeof(struct node*));
    temp->data = x;
    temp->next = NULL;
	
	struct node *p = start2;
    for (int i = 0; i < count2-1; i++)
        p = p->next;

    temp->next = p->next; 
     p->next = temp;
    count2++;
    //return 1;
}

int delete1()
{

if (isEmpty1()==1) 
	return 0;

struct node *temp;

  struct node *p = start1;
  for (int i = 0; i < count1-1; i++)
    p = p->next;

temp = p->next;
int temp_data = temp-> data;
p->next = temp->next; 
  count1--;
free (temp);
return temp_data;
}
int delete2()
{

if (isEmpty2()==1) 
	return 0;

struct node *temp;

  struct node *p = start2;
  for (int i = 0; i < count2-1; i++)
    p = p->next;

temp = p->next;
int temp_data = temp-> data;
p->next = temp->next; 
  count2--;
free (temp);
return temp_data;
}

int isEmpty1()
{
    if(start1==NULL)
    {
        return 1;
    }
    else
    return 0;
}

int isEmpty2()
{
    if(start2==NULL)
    {
        return 1;
    }
    else
    return 0;
}
void main()
{
    int ch;
    int xen;
  
    printf("\n1: Enqueue element into queue");
    printf("\n2: Dequeue element from queue");
    printf("\n3: Exit");
    while (1)
    {
        printf("\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter integer to enqueue: ");
            scanf("%d", &xen);
            enQueue(xen);
            break;
        case 2:
            deQueue();
            break;
        case 3:
            printf("Exiting...");
            exit(0);
            break;
        default:
            printf("Wrong choice");
            break;
        }
    }
    
}