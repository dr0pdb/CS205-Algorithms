/*
	Name - Saurav Roll-1601CS41.
	The aim of this program is to find and print the most reliable path between two given vertices.
*/

#include<stdio.h>
#include<stdlib.h>

//global variables.
int size[400]={0};
int adjlist[400][400];
double dist[400][400];
double path[400]={-1e9};
int p[400];

//function to print the path.
void printPath(int i){
	if (p[i] == i)
	{
		printf(" %d ",i);
		return;
	}
	printPath(p[i]);
	printf(" %d ",i);
}

int main()
{

	//getting input.
	int v,e,i;
	printf("Enter the number of vertices: ");
	scanf("%d",&v);

	printf("Enter the number of edges: ");
	scanf("%d",&e);

	printf("------NOTE: THE VERTICES ARE NUMBERED FROM 0 TO V-1------\n");
	printf("Enter the edges one by one with the r-value: ");

	//building the adjacency list.
	int from,to;
	double wt;
	for (i = 0; i < e; ++i)
	{
		scanf("%d %d %lf",&from,&to,&wt);
		adjlist[from][size[from]]=to;
		dist[from][size[from]++]=wt;
	}

	//getting input
	printf("Enter the two vertices among which to find the most reliable path:");
	scanf("%d %d",&from,&to);
	
	path[from] = 1;

	//initialising.
	for (i = 0; i < v; ++i)
	{
		p[i]=i;
	}
	
	//modified bellman ford algorithm.
	for (i = 0; i < v-1; ++i)
	{
		int u;
		for (u = 0; u < v; ++u)
		{
			int j;
			for (j = 0; j < v; ++j)
			{
				int to = adjlist[u][j];
				double wt = dist[u][j];

				if (path[to] < path[u]*wt)
				{
					path[to] = path[u]*wt;
					p[to]=u;
				}
			}
		}
	}

	//printing the final answer.
	printPath(to);
	printf(" and the maximum r-valued path is %lf\n", path[to]);

	return 0;
}