/*
	Name - Saurav Roll-1601CS41.
	The aim of this program is to find the strictly increasing shortest path between two randomly selected vertices.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INF 1000000000

//global variables.
int v;
char places[400][50];
int adjmat[400][400]={0};

//returns minimum
int min(int a, int b){
	return (a<b)?a:b;
}

//return maximum.
int max(int a, int b){
	return (a>b)?a:b;
}

//return absolute value
int abs(int a){
	return (a<0)?-a:a;
}

//returns the number of common characters between two strings.
int findCommon(int a, int b){
	int cnt1[26]={0},cnt2[26]={0};

	int i;
	for (i = 0; i < strlen(places[a]); ++i)
	{
		if (places[a][i]>='a' && places[a][i]<='z')
		{
			cnt1[places[a][i]-'a']++;
		}else if (places[a][i]>='A' && places[a][i]<='Z')
		{
			cnt1[places[a][i]-'A']++;
		}
		
	}

	for (i = 0; i < strlen(places[b]); ++i)
	{
		if (places[b][i]>='a' && places[b][i]<='z')
		{
			cnt2[places[b][i]-'a']++;
		}else if (places[b][i]>='A' && places[b][i]<='Z')
		{
			cnt2[places[b][i]-'A']++;
		}
	}

	int ans = 0;
	for (i = 0; i < 26; ++i)
	{
		ans += min(cnt1[i],cnt2[i]);	
	}
	return ans;	
}

//returns the weight of the edge between two vertices.
int findWeight(int a, int b){
	int minm = min(strlen(places[a]),strlen(places[b]));
	int i,ans = 0;

	for (i = 0; i < minm; ++i)
	{
		ans += abs(places[a][i]-places[b][i]);
	}

	if (strlen(places[a])>strlen(places[b]))
	{
		for (int i = minm+1; i < strlen(places[a]); ++i)
		{
			ans += abs(places[a][i]);
		}
	}else{
		for (int i = minm+1; i < strlen(places[b]); ++i)
		{
			ans += abs(places[b][i]);
		}
	}
	return ans;
}

//dijkstra shortest path algorithm.
void dijkstra(int start,int end){
	int cost[400][400],dist[400],prev[400];
	int visited[400],count,minddistance,nextnode,i,j;

	//resetting values.
	for (i = 0; i < v; ++i)
	{
		dist[i] = INF;
		for (j = 0; j < v; ++j)
		{
			if (adjmat[i][j]==0)
			{
				cost[i][j] = INF;
			}else{
				cost[i][j] = adjmat[i][j];
			}
		}
	}

    for(i=0;i<v;i++)
    {
        dist[i]=cost[start][i];
        prev[i]=start;
        visited[i]=0;
    }

    dist[start]=0;
    visited[start]=1;
    count=1;

    //running loop v-1 times.
    while(count<v-1){
    	minddistance = INF;

    	for(i=0;i<v;i++)
            if(dist[i]<minddistance&&!visited[i])
            {
                minddistance=dist[i];
                nextnode=i;
            }
            
            //check if a better path exists through nextnode            
            visited[nextnode]=1;
            for(i=0;i<v;i++)
                if(!visited[i])
                    if(minddistance+cost[nextnode][i]<dist[i])
                    {
                        dist[i]=minddistance+cost[nextnode][i];
                        prev[i]=nextnode;
                    }
        count++;
    }

    //checking if path exists or not.
    if (dist[end]==INF)
    {
    	printf("There is no such path between %s and %s\n",places[start],places[end]);
    }else{
    	//printing the answer and the final path.
    	printf("The distance of the required path between %s and %s is: %d\n",places[start],places[end],dist[end]);
    	printf("Path = %s",places[end]);
    	j = i;
    	do{
    		j = prev[j];
    		printf(" <<-- %s ",places[j]);
    	}while(j != start);
    }
}

int main()
{
	//getting input.
	printf("Enter the number of vertices: ");
	scanf("%d",&v);

	printf("Enter their names one by one: ");
	int i;
	for (i = 0; i < v; ++i)
	{
		scanf(" %s",&places[i]);
	}

	//forming edges.
	for (i = 0; i < v; ++i)
	{
		int j;
		for (j = i+1; j < v; ++j)
		{
			int slope = strlen(places[j])-strlen(places[i]);
			int common = findCommon(i,j);
			int weight = findWeight(i,j);	

			if (!slope)
			{
				adjmat[i][j] = weight;
				adjmat[j][i] = weight;
			}else if (common==1)
			{	
				if (slope==1)
				{
					adjmat[i][j] = weight;
				}
				if (slope==-1)
				{
					adjmat[j][i] = weight;
				}
			}else if (common ==2)
			{
				if (slope==2)
				{
					adjmat[i][j] = weight;
				}

				if (slope == -2)
				{
					adjmat[j][i] = weight;
				}
			}

		}
	}
	//generating random start and end.
	int start = rand()%v,end = rand()%v;

	//calling dijkstra.
	dijkstra(start,end);

	return 0;
}