/*
	Name - Saurav Roll - 1601CS41.
	The aim of this program is to implement basic MAX-FLOW algorithm between source and sink.
*/

#include<stdio.h>
#include<stdlib.h>


//global variables.
#define INF 1000000000
#define QUEUE_SIZE 100
int queue_array[QUEUE_SIZE];
int rear = - 1;
int front = - 1;

int adjmat[400][400];
int v,s,t,queue_size=0;

//insert elements in the queue.
void insert(int a)
{
    int add_item;
    if (rear == QUEUE_SIZE - 1)
    printf("Queue Overflow \n");
    else
    {
        if (front == - 1){
        	/*If queue is initially empty */
        	front = 0;
        }
        rear = rear + 1;
        queue_array[rear] = a;
        queue_size++;
    }
} 

//implement deque in the queue.
int delete()
{
    if (front == - 1 || front > rear)
    {
        printf("Queue Underflow \n");
        return -1;
    }
    else
    {
    	int ans = queue_array[front];
        front = front + 1;
        queue_size--;
    	return ans;
    }
}

//returns if the queue is empty or not.
int isEmpty(){
	return queue_size ==0;
}

//usual breadth-first algorithm.
int bfs(int rgraph[400][400],int parent[400]){

	int visited[400]={0};

	insert(s);
	visited[s]=1;
	parent[s]=-1;

	while(!isEmpty()){
		int u = delete();

		int i;
		for (i = 0; i < v; ++i)
		{
			if (visited[i]==0 && rgraph[u][i]>0)
			{
				insert(i);
				parent[i] = u;
				visited[i]=1;
			}
		}
	}

	return (visited[t] == 1);
}

//helper function to return min of two numbers.
int min(int a,int b){
	return (a<b)?a:b;
}

//standard FordFulkerson algorithm.
int fordFulkerson(){
	int i,j;

	int rgraph[400][400];

	for (i = 0; i < v; ++i)
	{
		for (j = 0; j < v; ++j)
		{
			rgraph[i][j] = adjmat[i][j];
		}
	}

	//stores the parent.
	int parent[400];

	//final answer.
	int maxFlow = 0;

	while(bfs(rgraph,parent)){
		int pathFlow = INF;

		for (j = t; j != s; j = parent[j])
		{
			i = parent[j];
			pathFlow = min(pathFlow,rgraph[i][j]);
		}

		for (j = t; j != s; j = parent[j])
		{
			i = parent[j];
			rgraph[i][j] -= pathFlow;
			rgraph[j][i] += pathFlow;
		}
		maxFlow += pathFlow;
	}
	return maxFlow;
}

//construct edges in the graph.
void constructEdges(){
	int i,j;
	for (int i = 1; i < v-1; ++i)
	{
		for (j = 1; j < v-1; ++j)
		{
			if (j-i>=0 && j-i<=3)
			{
				adjmat[i][j] = i+j+2;
			}
		}		
	}

	for (i = 1; i <= (v-2)/4; ++i)
	{
		adjmat[s][i] = i;
	}

	for (i = 3*(v-2)/4; i < v-1; ++i)
	{
		adjmat[i][t] = i;
	}
}

int main(int argc, char const *argv[])
{
	//getting the input.
	printf("Enter the value of n: ");
	scanf("%d",&v);

	v+=2;
	s = 0;
	t = v-1;

	//constructing edges.
	constructEdges();

	//printing the final answer.
	printf("The maximum flow between vertex %d and %d is %d\n",s,t,fordFulkerson());

	return 0;
}