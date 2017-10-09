/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to find out the max number of edges in a single connected component of an undirected graph.
*/

#include<stdio.h>
#include<stdlib.h>

//global variables.
int n,m;

int color[400];
int adjlist[400][400];
int sizelist[400]={0};
int numEdges[400]={0};

//helper function to find the max of two elements.
int max(int a, int b){
	return (a>b)? a:b;
}

//recursive depth-first-search.
void dfs(int u,int col){

	//coloring as visited.
	color[u]=col;
	int i;

	//recursively visiting adjacent elements.
	for (i = 0; i < sizelist[u]; ++i)
	{
		//incrementing the number of edges in this scc.
		numEdges[col]++;
		int next = adjlist[u][i];
		if (color[next] == -1)
		{
			dfs(next,col);
		}
	}
}

int main(){

	int i;

	//getting input
	printf("Enter the number of vertices(n): ");
	scanf("%d",&n);

	for (i = 1; i <= n; ++i)
	{
		color[i]=-1;
	}

	printf("Enter the number of edges(m): ");
	scanf("%d",&m);

	printf("-------- Note that the vertices have been numbered from 1 to n --------\n");
	printf("Enter the edge pairs one by one: ");
	int u,v;


	//building adjacency list.
	for (i = 0; i < m; ++i)
	{
		scanf("%d %d",&u,&v);
		adjlist[u][sizelist[u]++]=v;
		adjlist[v][sizelist[v]++]=u;
	}

	//dfs call.
	int scc_num = 0;
	for (i = 1; i <= n; ++i)
	{
		if (color[i] == -1)
		{
			dfs(i,++scc_num);
		}
	}

	//finding the answer by taking the maximum among all the connected components.
	int answer = -1000000000;
	for (i = 1; i <= scc_num; ++i)
	{
		answer = max(answer,numEdges[i]);
	}

	printf("The maximum number of edges in a single connected component are %d\n",answer/2);
	return 0;
}