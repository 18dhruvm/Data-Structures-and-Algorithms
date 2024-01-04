#include<stdio.h>
#include<stdlib.h>

int c=0;

void swap(int* a, int i, int j) 
{
	c++;
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}

void min_heapify(int* a,int n,int i) 
{
	int s=i;
	int l = 2*i+1;
	int r = 2*i+2;
	if(l<n && a[l]<a[s])
	{
		s = l;
	}
	if((r)<n && a[r]<a[s])
		s = r;
	if(s!=i) 
	{
		swap(a,i,s);
		min_heapify(a,n,s);
	}
}	

void build_heap(int* a,int n) 
{
	for(int i=n/2-1;i>=0;i--)
	{
		min_heapify(a,n,i);
	}
}

void sort(int* a,int n) 
{
	for(int i=1;i<n;i++) 
	{
		swap(a,0,n-i);
		min_heapify(a,n-i,0);
	}
}

void printFirst(int* a,int n,int k) 
{
	for(int i=1;i<=k;i++) 
	{
		printf("%d ",a[0]);
		swap(a,0,n-i);
		min_heapify(a,n-i,0);
	}
}

int main() {
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	int size;
	fp1 = fopen("searchTestCase.txt","r");
	fp2 = fopen("heapLists.txt","w");
	fp3 = fopen("sortedLists.txt","w");
	for(int i=0;i<18;i++) {
		c=0;
		fscanf(fp1,"%d",&size);
		int* a = (int*)calloc(sizeof(int),size);
		for(int j=0;j<size;j++)
			fscanf(fp1,"%d",&a[j]);
		build_heap(a,size);
		fprintf(fp2,"\n%d ",size); 
		for(int j=0;j<size;j++) {
			fprintf(fp2,"%d ",a[j]);
		}
		printf("Total number of swaps: %d\n",c);
		sort(a,size);
		fprintf(fp3,"\n%d ",size);
		for(int j=0;j<size;j++)
			fprintf(fp3,"%d ",a[j]);
	}
	fclose(fp2);
	FILE *fp4;
	fp4 = fopen("heapLists.txt","r");
	for(int i=0;i<18;i++) {
		fscanf(fp4,"%d ",&size);
		int* a = (int*)calloc(sizeof(int),size);
		for(int j=0;j<size;j++) {
			fscanf(fp2,"%d ",&a[j]);
		}
		
		int r=20;
		int k = size%100+r>size?size%100:size%100+r;
		printf("\nSize %d printing first %d elements:\n",size,k);
		printFirst(a,size,k);
		printf("\n");
	}
}