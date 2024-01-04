#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>

#define SIZE 50000

int *A; //array, size assigned dynamically

int c_queue[SIZE]; //array for circular queue
int front = -1, rear = -1;

// Check if the queue is full
int isFull() 
{
  if ((front == rear + 1) || (front == 0 && rear == SIZE - 1)) return 1;
  return 0;
}

// Check if the queue is empty
int isEmpty() 
{
  if (front == -1) return 1;
  return 0;
}

// Adding an element
void enQueue(int element) {
  if (isFull())
    printf("\n Queue is full! \n");
  else 
  {
    if (front == -1) front = 0;
    rear = (rear + 1) % SIZE;
    c_queue[rear] = element;
  }
}

// Display the queue
void showtime() 
{
  int i;
  if (isEmpty())
    printf("\nEmpty Queue");
  else 
  {
    printf("\nElements > 0: ");
    for (i = front; i != rear; i = (i + 1) % SIZE) 
    {
      printf("%d ", c_queue[i]);
    }
    printf("%d ", c_queue[i]);
  }
}

void load(int array[],int size) // load the data from array to queue as per ques
{
    int index=1;
    int length=size;
    enQueue(array[1]);
    while(size>1)
    {
        if(2*index > length || 2*index+1> length)
        {
            break;
        }
        if(array[2*index]!=-1)
        {
            enQueue(array[2*index]);
        }
        if(array[(2*index) + 1]!=-1)
        {
            enQueue(array[(2*index)+1]);
        }
        index++;
        size--;
    }
}

int main() 
{
    FILE*fp1;
    int size;
    int val,x,lines=10;
    fp1=fopen("binaryTreeArray.txt","r");
    for(int i=0;i<lines;i++)
	{	fscanf(fp1,"%d",&size);
	    //printf("\n%d",size);
	    A = (int *)malloc(sizeof(int)*size);
		for(int j=0;j<size;j++)
		{
			fscanf(fp1,"%d",&val);
			A[j]=val;
		}
		/*for(x=0;x<size;x++)
		{
		    printf("%d\t",A[x]);
		}
		printf("\n");*/ //to show elements in the array A[size]
		load(A,size);
		
	}
	
	fclose(fp1);
	showtime();
 

  return 0;
}
