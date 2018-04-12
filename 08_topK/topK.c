// compile: gcc topK.c -o topK
// run: ./topK

#include <stdio.h>

void heapAdjust(int list[], int i, int length);
void get_topk(int list[], int length, int top[], int K);
void outputList(int *list, unsigned int index, unsigned int indexMax);

int main(int argc, char const *argv[])
{
	int list[] = {8,14,23,-1,35,235,128,23,45,67,123};
	int length = sizeof(list) / sizeof(int);
	int K = 5;
	int top[K];
	get_topk(list,length, top, K);
	outputList(top, 0, K);
	printf("\n");
	return 0;
}



void get_topk(int list[], int length, int top[], int K)
{
    int counter = 0;
    float temp;
    int i =0;
    for(i = length/2-1; i>=0; --i)
    {
        heapAdjust(list,i,length);
    }
    for(i = length -1; i>0; i--)
    {
        top[counter] = list[0];
        counter ++ ;
        if(counter >= K)
        {
            break;
        }
        if(list[0] != list[i])
        {
            temp = list[0];
            list[0] = list[i];
            list[i] = temp;
        }
        heapAdjust(list,0,i);
    }
}


void heapAdjust(int list[], int i, int length)
{
    int nChild;
    int nTemp;
    for(;2*i+1<length;i=nChild)
    {
        nChild = 2*i +1;
        if(nChild < length-1 && list[nChild+1] > list[nChild])
        {
            nChild ++;
        }

        if(list[i] < list[nChild])
        {
            nTemp = list[i];
            list[i]=list[nChild];
            list[nChild]=nTemp;
        }else
        {
            break;
        }
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