

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void reverse(struct node** head_ref)
{
    struct node* prev = NULL;
    struct node* current = *head_ref;
    struct node* next = NULL;
    while (current != NULL) {
        // Store next
        next = current->next;
 
        // Reverse current node's pointer
        current->next = prev;
 
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
struct node *merge(struct node*root1,struct node*root2)
{
    if(root1==NULL)
        return root2;
    if(root2==NULL)
        return root1;

    struct node *root3=NULL;
    struct node *temp;
    while(root1!=NULL && root2!=NULL)
    {
        if(root1->data<root2->data)
        {
            temp=root1;
            root1=root1->next;
        }
        else
        {
            temp=root2;
            root2=root2->next;
        }
        if(root3==NULL)
            root3=temp;
        else
        {
            root3->next=temp;
            root3=root3->next;
        }
    }

    if(root1==NULL)
    {
        while(root2!=NULL)
        {
            root3->next=root2;
            root3=root3->next;
            root2=root2->next;
        }
    }
    else
    {
        while(root1!=NULL)
        {
            root3->next=root1;
            root3=root3->next;
            root1=root1->next;
        }
    }
    
    reverse(&root3);
    return root3;
}

void split(struct node *source, struct node **front, struct node **back) 
{ 
	struct node* ptr1; 
	struct node* ptr2; 
	ptr2 = source; 
	ptr1 = source->next; 

	while (ptr1 != NULL) 
	{ 
		ptr1 = ptr1->next; 
		if (ptr1 != NULL) 
		{ 
			ptr2 = ptr2->next; 
			ptr1 = ptr1->next; 
		} 
	} 

	*front = source; 
	*back = ptr2->next; 
	ptr2->next = NULL; 
} 

void MergeSort(struct node** thead) 
{ 
	struct node* head = *thead; 
	struct node* ptr1; 
	struct node* ptr2; 

	if ((head == NULL) || (head->next == NULL)) 
	{ 
		return; 
	} 

	split(head, &ptr1, &ptr2); 
	
	MergeSort(&ptr1); 
	MergeSort(&ptr2); 

	*thead = merge(ptr1, ptr2); 
} 

void push(struct node** head_ref, int x)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = x;
	new_node->next = *head_ref;
	*head_ref = new_node;
}

void print(struct node* list) 
{ 
	while (list != NULL) 
	{ 
		printf("%d ",list->data); 
		list = list->next; 
	} 
	printf("\n\n");
} 

void main()
{
    FILE*fp1;
    int i,j;
    fp1=fopen("SearchTestcase.txt","r");
    for(i=0;i<2;i++)
    {
        int size;
        fscanf(fp1,"%d",&size);
        struct node*array=NULL;
        for(j=0;j<size;j++)
        {
            int element;
            fscanf(fp1,"%d",&element);
            push(&array,element);
        }
        MergeSort(&array);
        print(array);
        free(array);
    }
    
    fclose(fp1);
}
