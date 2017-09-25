/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to find the min number of steps to reduce n to 1.
*/

#include<stdio.h>
#include<stdlib.h>

typedef long long ll;
#define INF 1000000000

//helper function to return the min of two elements.
ll min(ll a, ll b){
	if (a<b)
	{
		return a;
	}
	return b;
}

//helper function to print the answer
void print(int n,ll ans){
	printf("The min number of steps to reduce %d to 1 is %lld\n", n,ans);
}

int main()
{
	//getting the input.
	ll n;
	printf("Enter the number to be reduced to 1: ");
	scanf("%lld",&n);

	//in case of incorrect input.
	if (n<=0)
	{
		printf("The number should be greater than or equal to 1\n");
		return 0;
	}

	//initialising the dp table
	ll dp[n+10];
	dp[0]=INF;
	//base cases
	dp[1]=0; dp[2]=1; dp[3]=1; dp[4]=2;dp[5]=1;dp[6]=2;dp[7]=1;

	//building the bottom up dp table
	int i;
	for (i = 8; i <= n; ++i)
	{
		dp[i] = dp[i-1];
		if (i%2==0)
		{
			dp[i] = min(dp[i],dp[i/2]);
		}

		if (i%3==0)
		{
			dp[i]=min(dp[i],dp[i/3]);
		}

		if (i%5==0)
		{
			dp[i]=min(dp[i],dp[i/5]);
		}

		if (i%7==0)
		{
			dp[i]=min(dp[i],dp[i/7]);
		}

		dp[i]+=1;
	}
	//printing the answer.
	print(n,dp[n]);

	return 0;
}