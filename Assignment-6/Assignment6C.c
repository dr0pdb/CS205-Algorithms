/*
	Name - Saurav Roll-1601cs41
	The aim of this program is to partition the array into two sets having minimum difference.
*/

#include<stdio.h>
#include<stdlib.h>

#define INF 1000000000
#define MIN2(a,b) (a)<(b)?(a):(b)
int n,*arr;

//function to calculate the minimum difference.
void minDiff(){
	int sum=0,i;
	for (i = 0; i < n; ++i)
	{
		sum+=arr[i];
	}

	//the dp table and the parent info
	short int dp[sum+1];
	int parent[sum+1];
	int counter[sum+1];
	
	//initialising the dp table
	for (i = 0; i <= sum; ++i)
	{
		dp[i]=-1;
		parent[i]=-1;
		counter[i]=0;
	}

	//counting the number of each value
	for (i = 0; i < n; ++i)
	{
		counter[arr[i]]++;
	}

	//base case
	dp[0]=1;
	int indices[sum+1];

	int index=0;

	//gettting the all possible subset sum
	for (i = 0; i < n; ++i)
	{
		int j;
		for (j = 0; j <=sum; ++j)
		{
			if(dp[j]!=1 && j-arr[i]>=0 && dp[j-arr[i]]==1){
				indices[index++]=j;
				parent[j]=arr[i];
			}
		}
		for (j = 0; j < index; ++j)
		{
			dp[indices[j]]=1;
		}
	}
	
	//getting the min difference
	int ans=INF,minIndex;
	for (i = 1; i <= sum; ++i)
	{
		if (dp[i]==1 && ans>abs(sum-(2*i)))
		{
			ans = abs(sum-(2*i));
			minIndex=i;
		}
	}
	//printing the result
	printf("The minimum difference possible is %d\n",ans);

	//printing the first set
	printf("First set: { ");
	index = minIndex;
	int used[n];
	for (i = 0; i < n; ++i)
	{
		used[i]=0;
	}
	while(parent[index]>0){
		printf("%d ",parent[index]);
		counter[parent[index]]--;
		index-=parent[index];
	}
	//printing the second set.
	printf("} Second set: { ");
	for (i = 0; i < sum+1; ++i)
	{
		while(counter[i]){
			printf("%d ",i);
			counter[i]--;
		}
	}
	printf("}\n");
}

//the main function
int main(int argc, char const *argv[])
{
	//getting the input.
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);

	arr = (int*)malloc(n*sizeof(int));
	printf("Enter the elements one by one: ");
	
	//getting the coin values
	int i;
	for (i = 0; i < n; ++i)
	{
		scanf("%d",arr+i);
	}
	//calculating the result
	minDiff();
	
	return 0;
}