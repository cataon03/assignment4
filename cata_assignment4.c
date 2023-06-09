/*
Catalina Ocampo
COP3502C
Professor Torosdagli

*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;


void mergeSort(int pData[], int l, int r)
{
	int m = (l+r)/2;

    if (l < r) {
        int m = (l + r) / 2;

        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
  
       	int i, j, k;
		int n1 = m - l + 1;
		int n2 = r - m;
		
		int *L = (int*) malloc(n1*sizeof(int));
		int *R = (int*) malloc(n2*sizeof(int));

		extraMemoryAllocated += (n1 * sizeof(L)) + (n2 *sizeof(R));

		for (i = 0; i < n1; i++)
			L[i] = pData[l + i];
		for (j = 0; j < n2; j++)
			R[j] = pData[m + 1+ j];
		
		i = 0; 
		j = 0;
		k = l; 
		
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				pData[k] = L[i];
				i++;
			}
			else
			{
				pData[k] = R[j];
				j++;
			}
			k++;
		}
	
		while (i < n1)
		{
			pData[k] = L[i];
			i++;
			k++;
		}
		
		while (j < n2)
		{
			pData[k] = R[j];
			j++;
			k++;
		}
		free(L);
		free(R);
	}
}


void insertionSort(int* pData, int n)
{
    int temp = 0;

	int k;
    for(int i=0; i<n-1; i++)
    {
        temp = pData[i];

        for(k=i-1; k>=0; k--)
        {
            if(pData[k]<pData[k-1])
                pData[k+1] = pData[i];
            else 
                break;
        }
		pData[k+1] = temp;
    }	
}

void bubbleSort(int* pData, int n)
{
    int temp = 0;
    for(int i=0; i<n-1; i++)
    {
        for(int k=0; k<n-i-1; k++)
        {
            if(pData[k]>pData[k+1])
            {
                temp = pData[k];
                pData[k] = pData[k+1];
                pData[k+1] = temp;
            }
        }
    }	
}


void selectionSort(int* pData, int n)
{
	int temp = 0;
	int min = 0;
	int k;

	for(int i=0; i<n-1; i++)
	{
		min = i;
		for(k=i+1; k<n; k++)
		{
			if(pData[k] < pData[min])
			{
				min = k;
			}
		}
		if(min!=i)
		{
			temp = pData[i];
			pData[i] = pData[min];
			pData[min] = temp;
		}
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);

		if(ppData==NULL)
		{
			printf("DMA FAILED.");
		}
		// Implement parse data block
        for(int i=0; i<dataSz; i++)
		{
            fscanf(inFile, "%d", &((*ppData)[i])); 
        }
	}	

    fclose(inFile);
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n"); 
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		 
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}