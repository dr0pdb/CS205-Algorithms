/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to contruct a graph using required conditions and find the all-pair shortest path between them.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

//global variables.
int v,threshold;
char names[400][10];
int adjmat[400][400];
int dist[400][400];

//helper function to return the absolute value of a number.
int abs(int a){
	if (a<0)
	{
		a*=-1;
	}
	return a;
}

//function to return the edgeweight.
int edgeweight(int a, int b){

	int i=0,ans=0;

	for (i = 0; i < 5; ++i)
	{
		ans += abs(names[a][i]-names[b][i]);
	}
	return ans;
}

//function to return the value of |Y|
int vertexWeight(int a){
	char curr[10];
	strcpy(curr,names[a]);

	int i,ans=0;
	for (i = 0; i < 5; ++i)
	{
		ans+=curr[i];
	}
	return ans;
}

//checks whether an edge exists between two words.
int checkEdge(int a, int b){
	int counter = 0;
	int i;
	for(i=0;i<5;i++){
		if(names[a][i] != names[b][i]){
			counter++;
		}
	}
	
	return counter==1;
}

//check if b can open a's account
int check(int a, int b){
	if (dist[a][b]>=threshold)
	{
		return 0;
	}

	if (vertexWeight(b)<= vertexWeight(a))
	{
		return 0;
	}
	return 1;
}

//main function.
int main(int argc, char const *argv[])
{
	//getting input.
	printf("Enter the number of words: ");
	scanf("%d",&v);

	int i;
	printf("Enter the words one by one(5 lowercase alphabetical characters only): ");
	for (i = 0; i < v; ++i)
	{
		scanf("%s",&names[i]);
	}

	printf("Enter the threshold value of d: ");
	scanf("%d",&threshold);

	//constructing edges according to condition.
	for (i = 0; i < v; ++i)
	{
		int j;
		for (j = i+1; j < v; ++j)
		{
			if (checkEdge(i,j))
			{
				adjmat[i][j] = edgeweight(i,j);
				adjmat[j][i] = adjmat[i][j];
				dist[i][j] = adjmat[i][j];
				dist[j][i] = adjmat[i][j];		
			}else{
				adjmat[i][j] = INF;
				adjmat[j][i] = adjmat[i][j];
				dist[i][j] = adjmat[i][j];
				dist[j][i] = adjmat[i][j];
			}
		}
	}

	//floyyd warshall algorithm
	int k;
	for (k = 0; k < v; k++)
    {
        for (i = 0; i < v; i++)
        {
            int j;
            for (j = 0; j < v; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }


    //if j can open i's account.
    int rechable[400][400]={0};

    for (i = 0; i < v; ++i)
    {
    	int j;
    	for (j = 0; j < v; ++j)
    	{
    		if (check(i,j))
    		{
    			rechable[i][j] = 1;
    		}
    	}
    }

    printf("--------------FINAL RESULT--------------\n");
    //printing the final result
    for (i = 0; i < v; ++i)
    {
    	printf("%s can access : %s ",names[i],names[i]);
    	
    	int j;
    	for (j = 0; j < v; ++j)
    	{
    		if (rechable[j][i])
    		{
    			printf(" %s ",names[j]);
    		}
    	}
    	printf("\n");
    }

	return 0;
}
