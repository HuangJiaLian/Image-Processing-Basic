// compile: gcc nChooseK.c -o nChooseK
// run : ./nChooseK

#include <stdio.h>

// Get the combination number
unsigned int  nChoosek( unsigned int n, unsigned int  k );


int main(int argc, char const *argv[])
{
	int num = nChoosek(20,3);
	printf("Num of combination from 20 choose 3: %d\n", num);	
	return 0;
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

