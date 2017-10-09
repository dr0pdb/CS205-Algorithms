/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to divide a group of players into two sub groups with no intra-rivarlies between the players of a single team.
*/

#include<stdio.h>
#include<stdlib.h>

//global variables.
int n,r;

int color[400];
int adjlist[400][400];
int sizelist[400]={0};
int possible=1;

//recursive depth-first-search.
void dfs(int u,int col){

	if (!possible)
	{
		return;
	}

	//coloring the current player as visited.
	color[u]=col;
	int i;

	//recursively visiting adjacent/rival players.
	for (i = 0; i < sizelist[u]; ++i)
	{
		int next = adjlist[u][i];
		if (color[next] == -1)
		{
			dfs(next,1-col);
		}else if (color[next]==col)
		{
			possible = 0;
			return;	
		}
	}
}

int main(){

	int i;

	//getting input
	printf("Enter the number of players(n): ");
	scanf("%d",&n);

	for (i = 1; i <= n; ++i)
	{
		color[i]=-1;
	}

	printf("Enter the number of rivarlies(r): ");
	scanf("%d",&r);

	printf("-------- Note that the players have been numbered from 1 to n --------\n");
	printf("Enter the rival pairs one by one: ");
	int u,v;


	//building adjacency list.
	for (i = 0; i < r; ++i)
	{
		scanf("%d %d",&u,&v);
		adjlist[u][sizelist[u]++]=v;
		adjlist[v][sizelist[v]++]=u;
	}

	//dfs call.
	for (i = 1; i <= n; ++i)
	{
		if (color[i] == -1)
		{
			dfs(i,0);
		}
	}

	//check to see if it's possible.
	if (!possible)
	{
		printf("It is impossible to partition them into two teams with the required conditions.\n");
	}else{

		//printing the results.
		printf("Team 1 - ");
		for (i = 1; i <= n; ++i)
		{
			if (color[i]==0)
			{
				printf(" %d ",i);
			}
		}
		printf("\n");
		printf("Team 2 - ");
		for (i = 1; i <= n; ++i)
		{
			if (color[i]==1)
			{
				printf(" %d ",i);
			}
		}
		printf("\n");
	}

	return 0;
}