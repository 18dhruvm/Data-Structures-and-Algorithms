//#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student
{
	char rollNo[20];
	char emailId[35];
	char lecture[3];
	char tutorial[3];
	char practical[3];
	struct student*next;
};
//This function allocates memory for a new node using malloc, receives the starting address in variable ptr and fills in the data from buffer, to the memory pointed by ptr
struct student*createNode(struct student buffer)
{
	struct student*ptr=(struct student*)malloc(sizeof(struct student));

	strcpy(ptr->rollNo,buffer.rollNo);
	strcpy(ptr->emailId,buffer.emailId);
	strcpy(ptr->lecture,buffer.lecture);
	strcpy(ptr->tutorial,buffer.tutorial);
	strcpy(ptr->practical,buffer.practical);	

	ptr->next=NULL;
	return ptr;
}

//This function inserts a node with pointer temp to the list. The function checks whether a node with the same the roll number is already present in the list (whose starting address is in *startPtr) or not. If not, the function inserts the node at the end of the list and returns 1 on successful insertion.  If there is already a record with the same roll number, the function returns 0. Note that if in case the node that you are inserting is the first, then you have to update the listHead variable (a local variable in main) and that justifies the function being invoked with a reference to it (&listHead)  
int insertNode(struct student**startPtr,struct student*temp)
{
	if(*startPtr==NULL)
	{		
		*startPtr=temp;
		return 1;
	}	
	struct student*iterator=*startPtr;
	while(iterator->next!=NULL)
	{
		if(strcmp(iterator->rollNo,temp->rollNo)==0)
			return 0;
		iterator=iterator->next;
	}
	if(strcmp(iterator->rollNo,temp->rollNo)==0)
		return 0;
	iterator->next=temp;
	return 1;	
}
//This function looks for a node with a specific roll number in the list and deletes it if its present and returns 1 on successful deletion and 0 otherwise. Note that if in case the node that you are deleting is the first, then you have to update the listHead variable (a local variable in main) and that justifies the function being invoked with a reference to it (&listHead)  
int deleteNode(struct student**ptr,char rollNumber[20])
{
   struct student *old,*temp;
   temp= *ptr;
   while(temp!=NULL)
   {
       if(strcmp(temp->rollNo,rollNumber)==0)
       {
	  /*If node to be deleted is the first node*/
	  if(temp== *ptr)
	  {
	     *ptr=temp->next;
	     free(temp);
	     return 1;
	  }
	  /* deletes the intermediate in the linked list*/
	  else
	  {
	     old->next=temp->next;
	     free(temp);
	     return 1;
	  }
       }
       else
       {
	  old=temp;
	  temp=temp->next;
       }
   }

   return 0;

}
//This function takes the address of the first node and a roll number as input and checks whether there is a corresponding record  in the list or not. If yes, the function returns the position of the node in the list and returns 0 otherwise.
int searchNode(struct student*ptr,char rollNumber[20])
{
struct student *temp = ptr;
int index=1;

    while(temp != NULL)
    {
        if(strcmp(temp->rollNo,rollNumber)==0)
        {
            return index;
        }
        else
        {
         temp = temp->next;
        index++;   
        }
    }
    return 0;
}

//This function takes the address of the first node in the list as input and prints the roll number and email Id of each student in the list.To end with, the function returns the length of the list
int displayList(struct student*start)
{	
int count=0;
struct student *temp=start;

while(temp!=NULL)
{
	printf("\nRoll Number: %s \tEmail ID: %s", temp->rollNo, temp->emailId);
	temp=temp->next;
	count++;
}
return count;
}


int main()
{
	FILE*fp1;
	FILE*fp2;
	int i,j;
	int val;
	int op;
	int hit;
	int status;
	struct student buffer;
	struct student*nodeCopy;
	struct student*listHead=NULL;
	fp1=fopen("testCaseForList.txt","r");
	fp2=fopen("testResult.txt","w");	
	if(fp1==NULL){printf("\nFile read error\n");exit(0);}
	for(i=0;i<138;i++)
	{
		fscanf(fp1,"%d",&op);
	
		if(op==1)
		{
			fscanf(fp1,"%s",buffer.rollNo);
			fscanf(fp1,"%s",buffer.emailId);
			fscanf(fp1,"%s",buffer.lecture);
			fscanf(fp1,"%s",buffer.tutorial);
			fscanf(fp1,"%s",buffer.practical);
/*
			printf("%s ",buffer.rollNo);
			printf("%s ",buffer.emailId);
			printf("%s ",buffer.lecture);
			printf("%s ",buffer.tutorial);
			printf("%s\n",buffer.practical);
*/
			nodeCopy=createNode(buffer);
			status=insertNode(&listHead,nodeCopy);
			if(status==0)
			{	
				fprintf(fp2,"Insertion failed: Duplicate entry for %s\n",nodeCopy->rollNo);
				free(nodeCopy);
			}
			else
				fprintf(fp2,"Details for %s successfully inserted\n",nodeCopy->rollNo);

		}
		else
		{	//hit=1 --> value is present in the list and 0 otherwise
			fscanf(fp1,"%d %s",&hit,buffer.rollNo);	
			if((op==2)&&(deleteNode(&listHead,buffer.rollNo)!=hit))
			{
				printf("\nThere is an error in delete function\n");
				exit(0);
			}
			else if(op==2) //corresponds to deletion
			{
				if(hit==0)
					fprintf(fp2,"Deletion Failed: %s not present in list\n",buffer.rollNo);
				else
					fprintf(fp2,"Deletion successfull %s successfully removed\n",buffer.rollNo);

			}
			if(op==3)//corresponds to search, comment this if block if you want to test your deletion alone
			{
				int index=searchNode(listHead,buffer.rollNo);
				if(((hit==0) && (index!=0))||((hit!=0)&&(index==0)))
				{	
					printf("\nThere is an error in search function\n");
					exit(0);
				}
				else if(hit==0)
					fprintf(fp2,"%s not present in list\n",buffer.rollNo);
				else
					fprintf(fp2,"%s present at location %d\n",buffer.rollNo,index);

			}
			
		}
	}
	int count=displayList(listHead);
	printf("\nTotal count=%d\n",count);

	fclose(fp1);	
	fclose(fp2);
}



