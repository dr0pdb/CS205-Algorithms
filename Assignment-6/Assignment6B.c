/*
	Name - Saurav Roll-1601cs41
	The aim of this program is to calculate the min cost to reach from start to end point and also printing the path.
*/

#include<stdio.h>
#include<stdlib.h>

//global variables
int n,m;
int cost[500][500];
int dp[500][500]; //dp[i][j] contains the total cost to reach from (0,0) to (i,j).
int direction[500][500]; //direction to reach to this vertex. -1=parent 1-left 2-up and 3-diagonal

//helper function to return the minimum of two numbers.
int min(int a, int b){
	if (a<b)
	{
		return a;
	}
	return b;
}

//the main function
int main(int argc, char const *argv[])
{
	//getting the input.
	printf("Enter the value of m and n respectively: ");
	scanf("%d %d",&m,&n);

	//getting the cost values
	printf("Enter the cost value associated with each room:\n");
	int i;
	for (i = 0; i < m; ++i)
	{
		int j;
		for (j = 0; j < n; ++j)
		{
			scanf("%d",&cost[i][j]);
		}
	}	

	//base case for the dp table
	dp[0][0]=cost[0][0];
	direction[0][0]=-1;
	for (i = 1; i < n; ++i)
	{
		dp[0][i] = dp[0][i-1] + cost[0][i];
		direction[0][i] = 1;
	}
	for (i = 1; i < m; ++i)
	{
		dp[i][0] = dp[i-1][0] + cost[i][0];
		direction[i][0] = 2;
	}

	//bottom-up dp.
	for (i = 1; i < m; ++i)
	{
		int j;
		for (j = 1; j < n; ++j)
		{
			//assume from up
			int tempcost = cost[i][j] + min(dp[i-1][j],min(dp[i-1][j-1],dp[i][j-1]));
			dp[i][j] = tempcost;

			//storing the proper direction.
			if (tempcost == cost[i][j] + dp[i-1][j])
			{
				direction[i][j] = 2;
			}else if(tempcost == cost[i][j] + dp[i-1][j-1]){
				direction[i][j] = 3;
			}else{
				direction[i][j] = 1;
			}
		}
	}

	//printing the total cost
	printf("The total cost is %d\n",dp[m-1][n-1]);
	i = m-1;
	int j = n-1;
	int path[500],index=0;

	//constructing the path using the directions
	while(direction[i][j] != -1){
		path[index++]=direction[i][j];
		if (direction[i][j]==1)
		{
			j--;
		}else if (direction[i][j]==2)
		{
			i--;
		}else{
			i--;
			j--;
		}
	}

	//printing the path 
	printf("Here is the path: ");
	for (i = index-1; i >= 0; i--)
	{
		if (path[i]==1)
		{
			printf(" Rightward ");
		}else if (path[i]==2)
		{
			printf(" Downwards ");
		}else if(path[i]==3){
			printf(" Diagonal ");
		}
	}
	printf("\n");
	return 0;
}