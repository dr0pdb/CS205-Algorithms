/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to construct a graph considering the required conditions and check it's cyclic nature and pairwise connectivity.
*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//constant to be used floyyd-warshall algorithm
#define INF 1000000000

//global variables.
int n,m;

int color[400];
char words[400][8];
int adjlist[400][400];
int pathexists[400][400]={0};
int sizelist[400]={0};
int cyclic=0;

//helper function to find the max of two elements.
int max(int a, int b){
	return (a>b)? a:b;
}

//recursive depth-first-search.
void dfs(int u,int parent){

	//coloring as visited.
	color[u]=1;
	int i;

	//recursively visiting adjacent elements.
	for (i = 0; i < sizelist[u]; ++i)
	{
		int next = adjlist[u][i];
		if (color[next] == -1)
		{
			dfs(next,u);
		}else if (next!=parent)
		{
			//the graph is cyclic hence return
			cyclic=1;
			return;
		}
	}
}

//helper function to check whether two words have an edge between them.
int check(int a,int b){

	//copying into temporary strings.
	char first[8],second[8];
	strcpy(first,words[a]);
	strcpy(second,words[b]);

	//checking the conditions.
	int used[5]={0},counter=0;
	int i;
	for (i = 1; i < 5; ++i)
	{
		int j;
		for (j = 0; j < 5; ++j)
		{
			if (first[i]==second[j] && !used[j])
			{
				used[j]=1;
				counter++;
				break;
			}
		}
	}

	//if counter is 4 then they have an edge.
	if (counter==4)
	{
		return 1;
	}
	return 0;
}

int main(){

	//getting the input
	int i;

	printf("Enter the number of words: ");
	scanf("%d",&n);

	printf("Enter the words one by one: ");
	for (i = 1; i <=n; ++i)
	{
		scanf("%s",&words[i]);
	}
	
	//initialising array.
	for (i = 0; i <=n; ++i)
	{
		int j;
		for (j = 0; j <=n; ++j)
		{
			pathexists[i][j]=INF;			
		}
	}

	//adding edges if possible.
	for (i = 1; i <=n; ++i)
	{
		int j;
		for (j = i+1; j <=n; ++j)
		{
			if(check(i,j)){
				adjlist[i][sizelist[i]++]=j;
				adjlist[j][sizelist[j]++]=i;
				pathexists[i][j]=1;
				pathexists[j][i]=1;
			}
		}
	}

	//initialising as unvisited.
	for (i = 1; i <= n; ++i)
	{
		color[i]=-1;
	}

	//dfs calls
	for (i = 1; i <=n; ++i)
	{
		if (color[i]==-1)
		{
			dfs(i,-1);
		}
	}

	if (cyclic)
	{
		printf("------The given graph is cyclic------\n");
	}else{
		printf("------The given graph is not cyclic------\n");
	}
	
	//floyyd warshall algorithm to find the shortest path between all pairs.
	int k;
	for (k = 1; k <=n ; k++)
    {
        for (i = 1; i <= n; i++)
        {
    		int j;        
            for (j = 1; j <=n; j++)
            {
                if (pathexists[i][k] + pathexists[k][j] < pathexists[i][j]){
                    pathexists[i][j] = pathexists[i][k] + pathexists[k][j];
                }
            }
        }
    }

    //printing the result.
    printf("\nMatrix of path between all i and j\n");
    for ( i = 1; i <=n; ++i)
    {
    	int j;
    	for (j = 1; j <=n; ++j)
    	{
    		if (pathexists[i][j]!=INF)
    		{
    			printf(" 1 ");
    		}else{
    			printf(" 0 ");
    		}
    		
    	}
    	printf("\n");
    }

	return 0;
}