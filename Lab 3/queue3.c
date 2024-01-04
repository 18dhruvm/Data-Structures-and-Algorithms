#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h> /* for uint64 definition */ 
#include<time.h> /* for clock_gettime */ 

#define BILLION 1000000000L

int*queue;//the array that holds the queue
int queue_size;//size of the queue[] array
int opCode;
int front=0, rear=0;//queue index variables

int queueSize() //returns the total number of elements in the queue
{
int size;
size=rear-front;
return size;
}

int isQueueEmpty()//returns 1 if Queue is empty and 0 otherwise
{
if (front==rear)
{return 1;}
else return 0;
}

int isQueueFull()//returns 1 if Queue is full and 0 otherwise
{
 if(rear==queue_size)
   {
      return 1;
   }
  else return 0;
}

int enQueue(int x)//returns -1 if Queue is full and 1 otherwise
{
if(rear==queue_size)
   {
      return -1;
   }
  else {
    queue[rear]=x;
    rear=rear+1;
    return 1;}
}

int deQueue()//returns -1 if Queue is empty and the value otherwise
{	
int x;
   if(front==rear)
  {
    return -1;
  }
else {
    x=queue[front];
    front=front++;
    return x;}
}

int main()
{
	FILE*fp1;
	FILE*fp2;
	int i,j;
	int x,val;
	fp1=fopen("testCaseSize.txt","w");//lists the sizes of 10 different test cases
	fp2=fopen("SearchTestcase.txt","w");//lists all those test case where each entry (other than size) is either 0 (Dequeue) or 1(Enqueue)
	int size=30;
	for(i=0;i<10;i++)
	{
		fprintf(fp1,"%d\n",size);
		size=size*2;
	}
	fclose(fp1);	
	fp1=fopen("testCaseSize.txt","r");
	for(i=0;i<10;i++)
	{	
		fscanf(fp1,"%d",&size);
		fprintf(fp2,"%d ",size);

		for(j=0;j<size-1;j++)
		{
			fprintf(fp2,"%d ",((rand()%10000)>=6000)?0:1);
		}
		fprintf(fp2,"%d\n",((rand()%10000)>=6000)?0:1);
	}
	fclose(fp1);
 	fclose(fp2);

	int status;

	fp1=fopen("SearchTestcase.txt","r");	
	fp2=fopen("queueTime.txt","w");

	uint64_t diff=0;
	struct timespec start, end;

	for(i=0;i<10;i++)
	{	fscanf(fp1,"%d",&size);
		queue_size=(int)(0.7*size);
		queue=(int*)calloc(sizeof(int), queue_size); //have a queue of reasonable size for each test case

		for(j=0;j<size;j++)
		{
			fscanf(fp1,"%d",&opCode);
			if (opCode==1)//wants to enqueue
			{	x=rand()%10000;	//generate the random value to be enqueued		
				clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */ 
				status=enQueue(x);			
				clock_gettime(CLOCK_MONOTONIC, &end); /* mark the end time */ 
			
				diff += BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 

				if(status==-1)//queue full
				{
					printf("\n Enqueuing %d failed, queue full",x);
				}
				else 
				{
					printf("\n %d Successfully enqueued", x);
				}
			}
			else
			{				
				clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */ 
				status=deQueue(x);			
				clock_gettime(CLOCK_MONOTONIC, &end); /* mark the end time */ 
			
				diff += BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 

				if(status==-1)//queue empty
				{
					printf("\n DeQueuing failed, queue empty");
				}
				else
				{
					printf("\n successfully dequeued %d",status);
				}
			}
		}
		fprintf(fp2,"%.3f\n", ((long long unsigned int) diff/(float)size)); //write average computation time for a test case
	}
	fclose(fp1);
	fclose(fp2); 
}



