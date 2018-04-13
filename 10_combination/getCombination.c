// compile: gcc getCombination.c -o getCombination
// run : ./getCombination

#include <stdio.h>

// Define a struct for better management
struct triplet
{
    int tri[3];
};

// Get the combination number
unsigned int  nChoosek( unsigned int n, unsigned int  k );
// Get all combinations 
void get_combine(int list[], int listLength, int k, 
                int tempList[], int tempListLength, struct triplet combination[]);
// Just print to screen
void printAllCombinations(struct triplet combination[], int combinationNum);

// A global variable used in nesting function get_combine
int COUNTER = 0;



int main(int argc, char const *argv[])
{
	// int list[] = {1,3,9,23,-9};
    int list[] = {1,2,3,4};
    int listLength = sizeof(list) / sizeof(int);

    unsigned int combinationNum = nChoosek(listLength,3);
    struct triplet combination[combinationNum]; 
    COUNTER = 0;
    int temp[3];
    get_combine(list, listLength, 3, temp, 3, combination);
    
    printAllCombinations(combination, combinationNum);
	return 0;
}



void get_combine(int list[], int listLength, int k, 
                int tempList[], int tempListLength, struct triplet combination[])
{
 int i, j;
 for (i = listLength; i >= k; i--)
  {
   tempList[k - 1] = i - 1;
   if (k > 1)
   {
      get_combine(list, i - 1, k - 1, tempList, tempListLength, combination);
   }
   else
    {
      for (j = tempListLength - 1; j >= 0; j--)
      {
        combination[COUNTER].tri[j] = list[tempList[j]];
      }
        COUNTER++;
    }
  }
}



unsigned int  nChoosek( unsigned int n, unsigned int  k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}



void printAllCombinations(struct triplet combination[], int combinationNum)
{
    int i, j;
    for(i = 0; i < combinationNum; i++)
    {
        for(j = 0; j < 3; j++)
        {
            printf("%d ", combination[i].tri[j]);
        }
        printf("\n");
    }
}