/*
	Name - Saurav Roll-1601cs41
	The aim of this program is to partition the array into two sets having minimum difference.
*/

#include<stdio.h>
#include<stdlib.h>

#define INF 1000000000
int n,*arr,pathValue;

//function to calculate the minimum difference.
int minDiff(){
	int sum=0,i;
	for (i = 0; i < n; ++i)
	{
		sum+=arr[i];
	}

	short int dp[n+1][sum+1];

	for (i = 0; i <=n; ++i)
	{
		dp[i][0]=1;
	}

	for (i = 1; i <=sum; ++i)
	{
		dp[0][i]=0;
	}

    for (i=1; i<=n; i++)
    {	int j;
        for (j=1; j<=sum; j++)
        {
            dp[i][j] = dp[i-1][j];

            if (arr[i-1] <= j){
                dp[i][j] |= dp[i-1][j-arr[i-1]];
            }
        }
    }
    int j,ans=INF;
    for (j = sum/2; j >=0; j--)
    {
    	if (dp[n][j]==1)
    	{
    		ans = sum-(2*j);
    		break;
    	}
    }
    return ans;
}

//the main function
int main(int argc, char const *argv[])
{
	printf("Enter the number of elements in the array: \n");
	scanf("%d",&n);

	arr = (int*)malloc(n*sizeof(int));
	printf("Enter the elements one by one: \n");
	
	int i;
	for (i = 0; i < n; ++i)
	{
		scanf("%d",arr+i);
	}

	int diff = minDiff();
	printf("The minimum difference possible is %d\n",diff);
	printf("First set: ");
	
	return 0;
}