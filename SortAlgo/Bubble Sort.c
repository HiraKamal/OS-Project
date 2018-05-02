#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *first, int *sec)
{
    int temp = *first;
    *first = *sec;
    *sec = temp;
} 
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int n=0;
    /*printf("Enter no of elements you want in your array: ");
    scanf("%d\n",&n);
    int arr[n];
    for (int i=0;i<n;i++)
    {
	scanf("%d",&arr[i]);
    }
*/
    clock_t begin, end;
    double total_t;
    begin = clock();
    FILE * fp;
    fp = fopen("1-10000.txt","r");
    fscanf(fp, "%d", &n);

    int *arr = malloc(n * sizeof(int));
	
    for (int i=0; i < n; i++)
    {
	fscanf(fp, "%d", &arr[i]);
    }
    bubbleSort(arr, n);
    printf("Sorted array: \n");
	//printf("%d\n",n);
    printArray(arr, n);
    end= clock();
    total_t = (double)(end - begin );
    //printf("Total Numbers :  %d\n",n);	
    printf("Initial time taken by CPU: %d \n", begin  );
    printf("End time taken by CPU: %d \n", end  );
    printf("Total time taken by CPU: %f seconds\n", total_t  );
    free(arr);

    return 0;
}
