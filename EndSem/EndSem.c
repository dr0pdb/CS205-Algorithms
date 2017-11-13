/*
	Name - Saurav Roll-1601CS41.
	The aim of this program is to build the graph of cities using the required conditions and also check the graph for connectivity and whether a triangle exists.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//declaring a pair of integers.
typedef struct pair
{
	//first and second.
	int f,s;
}pair;

//global variables.
int v;
char cities[400][50];
pair adjlist[400][400];
int size[400]={0},visited[400]={0};
int triangleexists = 0;
int triangle[3];

//checks if their is an edge between city a and b
int check(int a,int b){
	int counta[26]={0},countb[26]={0};

	int i;
	for (i = 0; i < strlen(cities[a]); ++i)
	{
		char c = cities[a][i];
		if (c>='a' && c<='z')
		{
			counta[c-'a']++;
		}else if (c>='A' && c<='Z')
		{
			counta[c-'A']++;
		}
	}

	for (i = 0; i < strlen(cities[b]); ++i)
	{
		char c = cities[b][i];
		if (c>='a' && c<='z')
		{
			countb[c-'a']++;
		}else if (c>='A' && c<='Z')
		{
			countb[c-'A']++;
		}
	}	

	//checking for common characters.
	for (i = 0; i < 26; ++i)
	{	
		//if any common characters exists, then return true.
		if (counta[i] && countb[i])
		{
			return 1;
		}
	}
	return 0;
}

//helper function to return the minimum of two numbers.
int min(int a,int b){
	return (a<b)? a : b;
}

//returns the edit distance between city a and b.
int getWeight(int a,int b){

	//storing the length of both the strings.
	int m,n;
	m = strlen(cities[a]);
	n = strlen(cities[b]);

	//dp table
	int dp[m+1][n+1];

	int i,j;
	for (i = 0; i <= m; ++i)
	{
		for (j = 0; j <=n; ++j)
		{	
			//base case
			if (!i)
			{
				dp[i][j] = j;
			}

			//base case
			else if (!j)
			{
				dp[i][j]= i;
			}

			//recursive step.
			else if (cities[a][i-1] == cities[b][j-1])
			{
				dp[i][j] = dp[i-1][j-1];
			}
			else{
				dp[i][j] = 1 + min(dp[i][j-1],min(dp[i-1][j],dp[i-1][j-1]));
			}
		}
	}

	//returning the final answer.
	return dp[m][n];
}

//helper function to build the graph with correct edge weights.
void buildEdges(){
	int i,j;
	for (i = 0; i < v; ++i)
	{
		for (j = i+1; j < v; ++j)
		{
			//if they have any common characters.
			if (check(i,j))
			{
				//getting the edit distance.
				int weight = getWeight(i,j);
				pair p;
				p.f = j;
				p.s = weight;

				//building the adjacency list.
				adjlist[i][size[i]++]=p;
				p.f = i;
				adjlist[j][size[j]++]=p;
			}
		}
	}
}

//dfs function.
void dfs(int u,int parent,int parent_of_parent){
	
	visited[u] = 1;
	int i;

	//iterate over all the neighbours of u.
	for (i = 0; i < size[u]; ++i)
	{
		pair curr = adjlist[u][i];
		//if it is not visited , then recursively visit it.
		if (!visited[curr.f])
		{
			dfs(curr.f,u,parent);
		}else if (curr.f == parent_of_parent)
		{
			//if this happens then their is a triangle between u,parent and parent_of_parent.
			triangleexists = 1;
			triangle[0] = parent_of_parent;
			triangle[1] = parent;
			triangle[2] = u;
		}
	}
}

int main()
{
	//getting the input.
	printf("Enter the number of cities: ");
	scanf("%d",&v);

	//getting input.
	printf("Enter their names one by one(all lowercase): ");
	int i;
	for (i = 0; i < v; ++i)
	{
		scanf("%s",&cities[i]);
	}

	//building the graph.
	buildEdges();

	//printing the final built graph.
	printf("--------------------final Graph--------------------\n");
	for (i = 0; i < v; ++i)
	{
		printf("--- The adjacency list of %s ---\n",cities[i]);
		int j;
		for (j = 0; j < size[i]; ++j)
		{
			pair curr = adjlist[i][j];
			printf("%s(edge weight - %d)  \n",cities[curr.f],curr.s);
		}
		printf("\n");
	}

	int cc=0;

	//dfs call.
	for (i = 0; i < v; ++i)
	{	
		if (!visited[i])
		{
			cc++;
			dfs(i,-1,-1);
		}
	}

	//printing the final answers.
	printf("First question: ");
	//if number of connnected components is one , then the graph is connected.
	if (cc==1)
	{
		printf("The graph is connected!\n");
	}else{
		printf("The graph is disconnected!\n");
	}

	printf("Second question: ");
	//if triangleexists.
	if (triangleexists)
	{
		printf("Yes. One of the triangles is between: %s %s %s\n",cities[triangle[0]],cities[triangle[1]],cities[triangle[2]]);
	}else{
		printf("No triangle exists.\n");
	}
	return 0;
}