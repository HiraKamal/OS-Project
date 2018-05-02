#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> 

int main()
{
    int n;
    /*printf("Enter no of elements you want in your array: ");
    scanf("%d\n",&n);
    int arr[n];
    */
    clock_t begin, end;
    double total_t;
    begin = clock();
    FILE * fp;
    fp = fopen("1-25000.txt","r");
    fscanf(fp, "%d", &n);
    int *arr = malloc(n * sizeof(int));
	
    #pragma omp parallel num_threads(2)
{
    #pragma omp for
	for (int i=0; i < n; i++)
	{
		fscanf(fp, "%d", &arr[i]);
	}
}
   #pragma omp parallel num_threads(2)
{
    #pragma omp for
    for (int i = 0; i < n-1; i++)      
    {  
	#pragma omp parallel for
        for (int j = 0; j < n-i-1; j++) 
	{
           if (arr[j] > arr[j+1])
	   { 
                int temp;
		temp = arr[j];
    		arr[j] = arr[j+1];
    		arr[j+1] = temp;
	   }
	}
    }
}
    printf("Sorted array: \n");
    #pragma omp parrallel num_threads(2)
{
    #pragma omp for
    for (int i=0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}
    printf("\n");
    end= clock();
    total_t = (double)(end - begin );
    //printf("Total Numbers :  %d\n",n);	
    printf("Initial time taken by CPU: %d \n", begin  );
    printf("End time taken by CPU: %d \n", end  );
    printf("Total time taken by CPU: %f seconds\n", total_t  );
    free(arr);

    return 0;
}
