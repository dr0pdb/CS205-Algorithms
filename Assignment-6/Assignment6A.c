/*
	Name- Saurav Roll-1601CS41
	The aim of this program is to calculate the minimum number of coins required to get a particular sum.
*/

#include<stdio.h>
#include<stdlib.h>

//global variables and the memo table
#define INF 1000000000
int n,s,*values;
int dp[50][10000][500];
int coinsCount[50],minCoinsCount[50],bestCount=INF;

//helper function to find the minimum of two numbers
int min(int a, int b){
	if (a<b)
	{
		return a;
	}
	return b;
}

//The actual function to calculate the number of coins.
int coins(int index,int sum,int counter){
	
	//if not possible
	if (sum<0 || index == n)
	{
		return INF;
	}
	//if result reached.
	if (sum==0)
	{
		if (bestCount>counter)
		{
			bestCount = counter;
			int i;
			for (i = 0; i < 50; ++i)
			{
				minCoinsCount[i]=coinsCount[i];	
			}
		}
		return counter;
	}
	//if state already known.
	if (dp[index][sum][counter] !=-1)
	{
		return dp[index][sum][counter];
	}

	//actual recursive calls
	coinsCount[index]++;
	dp[index][sum][counter] = coins(index,sum-values[index],counter+1);
	int temp = coins(index+1,sum-values[index],counter+1);
	coinsCount[index]--;
	int temp2 = coins(index+1,sum,counter);

	dp[index][sum][counter] = min(dp[index][sum][counter],min(temp,temp2));

	return dp[index][sum][counter];
}

int main()
{
	//getting the input
	printf("Enter the value of n: ");
	scanf("%d",&n);

	values = (int*)malloc(n*sizeof(int));
	
	printf("Enter the value of the coins: ");
	int i;
	for (i = 0; i < n; ++i)
	{
		scanf("%d",values+i);	
	}

	printf("Enter the value of S: ");
	scanf("%d",&s);

	//initialising the dp table
	for (i = 0; i < n; ++i)
	{
		coinsCount[i]=0;
		int j,k;
		for (j = 0; j < 10000; ++j)
		{
			for (k = 0; k < 500; ++k)
			{
				dp[i][j][k]=-1;
			}
		}
	}

	//calculating the answer.
	int ans = coins(0,s,0);

	//if sum cannot be reached
	if (ans==INF)
	{
		printf("The sum %d cannot be reached using these coins\n",s);
	}else{
		//printing the answer
		printf("The min number of coins needed are %d \n",ans);

		printf("Here are the number of coins of each value(Non-zero ones only): \n");
		for (i = 0; i < n; ++i)
		{
			if (minCoinsCount[i]==0)
			{
				continue;
			}else{
				printf("value-%d count-%d\n",values[i],minCoinsCount[i]);
			}
		}
	}

	return 0;
}