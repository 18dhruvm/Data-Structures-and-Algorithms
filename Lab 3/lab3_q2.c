#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h> /* for uint64 definition */ 
#include<time.h> /* for clock_gettime */ 

#define BILLION 1000000000L

int*stack1; //memory allotted for stack1
int top1=-1; // index of the topmost variable in stack1
int*stack2; //memory allotted for stack1
int top2=-1;
int stack_size=3;

int isStack2Full()// returns 1 if stack2[] is full and 0 otherwise
{
    if(top2==stack_size-1) return 1;
    else return 0;
}

int isStack2Empty()//returns 1 if stack2[] is empty and 0 otherwise
{
    if(top2==-1) return 1;
    else return 0;
}

int isStack1Full()// returns 1 if stack1[] is full and 0 otherwise
{  
    if(top1==stack_size-1) return 1;
    else return 0;
}
int isStack1Empty()//returns 1 if stack1[] is empty and 0 otherwise
{
    if(top1==-1) return 1;
    else return 0;
}

int pop2() //pops and returns an element from stack2
{	int data;
    if(!isStack2Empty()) 
    {
        data = stack2[top2];
        top2 = top2 -1;
        return data;
    }
    else
        return -1;
}
int push2(int x)//pushes an element to stack2
{ 
    if(!isStack2Full()) 
    {
        top2 = top2 + 1;
        stack2[top2] = x;
        return 1;
    }   
    else
        return -1;
}

int pop1()//pops an element from stack1
{	int data;
    if(!isStack1Empty()) 
    {
        data = stack1[top1];
        top1 = top1 -1;
        return data;
    }
    else
        return -1;
}
int push1(int x)//pushes an element to stack1
{ 
    if(!isStack1Full()) 
    {
        top1 = top1 + 1;
        stack1[top1] = x;
        return 1;
    }   
    else
        return -1;
}

int isQueueFull()
{
    if (isStack2Full()==1)
        {return 1;}
    else
        {return 0;}
}

int isQueueEmpty()
{
    if (isStack2Empty() == 1)
        {return 1;}
    else
        {return 0;}
}

int enQueue (int x)
{
    if(isQueueFull())
        {return -1;}
    else
    {push2(x); 
    printf("%d enqueued successfully",x);
return 1;}
}

int deQueue()
{
    if(isQueueEmpty())
    {printf("Error, stack is empty");
        return -1;}
    
    else
    {
        while (isStack2Empty() == 0)  //stack2 is not empty
        {
            int x_1=pop2();
            push1(x_1);
        }
    int y=pop1();
    while (isStack1Empty() == 0) //stack2 is not empty
        {
            int x_2=pop1();
            push2(x_2);
        }
        printf("%d dequeued successfully",y);
    return y;
        
    }
}

void main()
{
    int ch;
    int xen;
    int size=20000;

    stack1=(int *)malloc(sizeof(int)*size);
    stack2=(int *)malloc(sizeof(int)*size);
 
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