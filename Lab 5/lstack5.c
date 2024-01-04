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
	struct student* next;
};
//Result also found in testResult file

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

int push(struct student**top,struct student* temp) {
    if(*top==NULL) {
		*top = temp;
		return 1;
	}
	temp->next = *top;
	*top = temp;
}
struct student* pop(struct student**top) {
    if(*top == NULL) {
	return NULL;
	}
	struct student* temp = *top; //check wheter *root or root
	*top = temp->next;
	return temp;
};

int displayList(struct student*start)
{ struct student* it = start;
	while(it!=NULL) {
		printf("%s %s\n",it->rollNo,it->emailId);
		it=it->next;
	}
}


int main() {
	FILE*fp1;
	FILE*fp2;
	int i,j,op;
	struct student buffer;
	struct student* nodeCopy;
	struct student* head;
	fp1  = fopen("testCaseForStack.txt","r");
	fp2 = fopen("testResult.txt","w");
	if(fp1==NULL) {printf("\nFile read error\n");exit(0);}
	for(i = 0;i<138;i++)
	{
		fscanf(fp1,"%d",&op);
		if(op==1) {
			fscanf(fp1,"%s",buffer.rollNo);
			fscanf(fp1,"%s",buffer.emailId);
			fscanf(fp1,"%s",buffer.lecture);
			fscanf(fp1,"%s",buffer.tutorial);
			fscanf(fp1,"%s",buffer.practical);

			nodeCopy=createNode(buffer);
			push(&head,nodeCopy);
			printf("Details for %s successfully inserted\n",nodeCopy->rollNo);
			fprintf(fp2,"Details for %s successfully inserted\n",nodeCopy->rollNo);
		}
		else {
			struct student* temp = pop(&head);
			if(temp==NULL) {
				printf("Stack empty");
				fprintf(fp2,"Deletion Failed: %s not present in list\n",temp->rollNo);
			}
			else {
				printf("Deletion successfull %s successfully removed\n",temp->rollNo);
				fprintf(fp2,"Deletion successfull %s successfully removed\n",temp->rollNo);
			}
		}
	}
	fclose(fp1);
	fclose(fp2);
}
