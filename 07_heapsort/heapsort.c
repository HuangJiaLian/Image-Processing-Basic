// compile: gcc heapsort.c -o heapsort
// run: ./heapsort

#include <stdio.h>

void heapAdjust(int *list, int i, int lenth);
void heapSort(int *list, int length);
void outputList(int *list, unsigned int index, unsigned int indexMax);


int main(int argc, char const *argv[])
{
	int list[] = {8,14,23,-1,35,235,128,23,45,67,123};
	unsigned int length = sizeof(list) / sizeof(int);

	printf("The original list:\n");
	outputList(list,0,length);
	printf("\n");
	// Sort the list
	heapSort(list,length);

	// Print the list to screen without loop
	printf("The ordered list:\n");
	outputList(list,0,length);
	printf("\n");
	return 0;
}



void heapAdjust(int *list, int i, int length)
{
    int nChild;
    int temp;
    for(;2*i+1 < length; i = nChild)
    {
        // Index of left child
        nChild = 2*i + 1;
        // If right child greater than left
        if(nChild < length - 1 && list[nChild+1] > list[nChild])
        {
            // nChild store the bigger child's index
            ++nChild;
        }
        // If the bigger child bigger than his father, then he becomes father
        if(list[i] < list[nChild])
        {
            temp = list[i];
            list[i] = list[nChild];
            list[nChild] = temp;
        }else
        {
            break;
        }
    }
}



void heapSort(int *list, int length)
{
    int i;
    int temp;
    for(i=length/2 -1; i>=0; --i)
    {
        heapAdjust(list,i,length);
    }
    for(i=length-1;i>0;--i)
    {
        temp =  list[i];   
        list[i] =  list[0];  
        list[0] = temp;     
        heapAdjust(list,0,i);
    }
}


void outputList(int *list, unsigned int index, unsigned int indexMax)
{
	if(index < indexMax)
	{
		printf("%d ", list[index]);
		outputList(list, index + 1, indexMax);
	}
	return;
}