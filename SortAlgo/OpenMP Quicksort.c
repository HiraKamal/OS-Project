#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    
    int i = (low - 1);

	#pragma omp schedule(static) parallel num_threads(4)
{
	#pragma omp for
  
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;    
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
}
    return (i + 1);
}
 
void quickSort(int arr[], int low, int high)
{
  if (low < high)
    {
        int pi = partition(arr, low, high);
 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size)
{
    int i;
	#pragma omp schedule(static) parallel num_threads(2)
{
	#pragma omp for
    for (i=0; i < size; i++)
        printf("%d \n", arr[i]);
 }
   printf("\n");
}
 

int main()
{
	clock_t begin, end;
        double total_t;
        begin = clock();	
	

	int num=0;	
	FILE * fp;
	fp = fopen("1M.txt","r");
	fscanf(fp, "%d", &num);

	int *arr = malloc(num * sizeof(int));
	int n=num; 
	int i=0;



	#pragma omp schedule(static) parallel num_threads(2)
{

	#pragma omp for
	for ( i=0; i < num; i++){
		fscanf(fp, "%d", &arr[i]);
	}


}

	quickSort(arr, 0, n-1);


	end= clock();
        total_t = (double)(end - begin );

	printArray(arr,num);


	printf("Total numbers sorted: %d \n",num);
	printf("Initial time taken by CPU: %d \n", begin  );
	printf("End time taken by CPU: %d \n", end  );
	printf("Total time taken by CPU: %f seconds\n", total_t  );	

	free(arr);
	return 0;
}

