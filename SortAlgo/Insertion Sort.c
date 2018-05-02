#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
 
void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}
 

void printArray(int arr[], int n)
{
   int i;
   for (i=0; i < n; i++)
       printf("%d ", arr[i]);
   printf("\n");
}

int main()
{
    int n;
    /*printf("Enter no of elements you want in your array: ");
    scanf("%d\n",&n);
    int arr[n];*/
    clock_t begin, end;
    double total_t;
    begin = clock();
    FILE * fp;
    fp = fopen("1-25000.txt","r");
    fscanf(fp, "%d", &n);
    int *arr = malloc(n * sizeof(int));
    for (int i=0;i<n;i++)
    {
	fscanf(fp, "%d", &arr[i]);
	//scanf("%d",&arr[i]);
    }
    insertionSort(arr, n);
    printf("Sorted array: \n");
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
