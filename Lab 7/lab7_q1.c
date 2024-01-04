#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h> /* for uint64 definition */
#include<time.h> /* for clock_gettime */

#define BILLION 1000000000L

int localpid(void) {static int a[9] = { 0 }; return a[0];}

int *array;

void swap (int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int partition(int array[], int low, int high)
{
    int pivot= array[high];
    int i=(low-1);
   
    for(int j=low; j<=high-1; j++)
    {
        if(array[j]<pivot)
        {
            i++;
            swap(&array[i],&array[j]);
        }
    }
   
    swap(&array[i+1], &array[high]);
    return (i+1);
}

void quicksort(int array[], int low, int high)
{
    if (low<high)
    {
        int x= partition(array, low, high);
        quicksort(array, low, x-1);
        quicksort(array, x+1, high);
    }
}

void merge(int array[], int l, int m, int r)
{
    int i, j, k;
    int n1=m-l+1;
    int n2=r-m;
   
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];
 
   
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int array[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
 
        merge(array, l, m, r);
    }
}

int main()
{
    FILE*fp2;
    FILE*fp3;
    FILE*fp4;
    int i,j;
    int val;
   
    fp2=fopen("SearchTestcase.txt","r");
    fp3=fopen("QuickSortTime.txt","w");
    
    uint64_t diff;
    struct timespec startL, endL,startB,endB;
    
    for(i=0;i<18;i++)
    {
        int size;
        fscanf(fp2,"%d",&size);
        array=(int*)malloc(sizeof(int)*size);
        
        for(j=0;j<size;j++)
        {
            int element;
            fscanf(fp2,"%d",&element);
            array[j]=element;
        }
        
        clock_gettime(CLOCK_MONOTONIC, &startL); 
        quicksort(array, 0, size-1);
        clock_gettime(CLOCK_MONOTONIC, &endL); 
        diff = BILLION * (endL.tv_sec - startL.tv_sec) + endL.tv_nsec - startL.tv_nsec;
        fprintf(fp3,"%llu\n", (long long unsigned int) diff);
        free(array);
    }
    fclose(fp3);
    
    fp4=fopen("MergeSortTime.txt","w");
    
    for(i=0;i<18;i++)
    {
        int size;
        fscanf(fp2,"%d",&size);
        array=(int*)malloc(sizeof(int)*size);
        
        for(j=0;j<size;j++)
        {
            int element;
            fscanf(fp2,"%d",&element);
            array[j]=element;
        }
        clock_gettime(CLOCK_MONOTONIC, &startB); 
        mergeSort(array, 0, size-1);
        clock_gettime(CLOCK_MONOTONIC, &endB); 
        diff = BILLION * (endB.tv_sec - startB.tv_sec) + endB.tv_nsec - startB.tv_nsec;
        fprintf(fp4,"%llu\n", (long long unsigned int) diff);
        free(array);
    }
    fclose(fp2);
    fclose(fp4);

    return 0;
}
