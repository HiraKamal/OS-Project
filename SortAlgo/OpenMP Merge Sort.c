#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int num=0;
int *A;
int *temp;

void MergeSort(int arr[],int length)
{
	A=(int*)malloc(length*sizeof(int));
	temp=(int*)malloc(length*sizeof(int));

	#pragma omp parallel num_threads(4)
	{
	#pragma omp for
	for(int i=0;i<length;i++)
	{
	A[i]=arr[i];
	temp[i]=arr[i];
	}
	}
}

void merge(int start,int mid,int end)
{
	int k;
	int i=start;
	int j=mid+1;
	#pragma omp parallel num_threads(4)
	{
	#pragma omp for
	for(int t=start;t<=end;t++)
	{
		temp[t]=A[t];
	}
	}
	#pragma omp parallel num_threads(4)
	{
	#pragma omp for
	for(k=start;k<=end;k++)
	{	
		if(i>mid){
			A[k]=temp[j++];
		}
		else if(j>end){
			A[k]=temp[i++];
		}
		else if(temp[i]<temp[j]){
			A[k]=temp[i++];
		}
		else{
			A[k]=temp[j++];	
		}
	}
	}
}

void display()
{
	#pragma omp parallel num_threads(2)
	{
	#pragma omp for
	for(int i=0;i<=num;i++){
		printf("%d ",A[i]);
	}
	}
}

void sort(int start, int end)
{
	int mid;
	#pragma omp parallel num_threads(2)
	{	
	if(start<end)
	{
		mid=(start+end)/2;
		sort(start,mid);
		sort(mid+1,end);
		merge(start,mid,end);
	}
	}
}

int main()
{
	clock_t begin, end;
        double total_t;
        begin = clock();
	int i;
	num=0;
	//int array[]={2,4,6,8,1,0,-5};
	FILE *filepointer;
	filepointer=fopen("1-25000.txt","r");
	fscanf(filepointer, "%d",&num);
	
	int *array=malloc(num*sizeof(int));
	//int n=num;
	
	for(i=0;i<=num;i++){
	fscanf(filepointer,"%d",&array[i]);
	}

	printf("list before sorting \n");
	#pragma omp parallel num_threads(4)
	{
	/*#pragma omp for
	for(i=0;i<=num;i++)
	{
		printf("%d\n",array[i]);
	}
	*/
	MergeSort(array,num);
	sort(0,num);
	}
	printf("\n list after sorting\n");
	display();

	free(array);
	end= clock();
        total_t = (double)(end - begin );
	//printf("Total numbers sorted: %d \n",num);
	printf("Initial time taken by CPU: %d \n", begin  );
	printf("End time taken by CPU: %d \n", end  );
	printf("Total time taken by CPU: %f seconds\n", total_t  );
    
	return 0;
}

