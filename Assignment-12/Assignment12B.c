/*
  Name - Saurav Roll-1601CS41
  The aim of this program is to find the max flow from a source to a sink using the push-relabel algorithm.
*/
#include<stdio.h>
#include<string.h>

#define INF 1e9+10

//struct to represent an edge.
typedef struct Edge{
	int flow,capacity;
	int from,to;
}Edge;

//struct to represetn a vertex.
typedef struct vertex{
	int h,e_flow;
}Vertex;

//names of cities.
char cities[71][25] = {"Mumbai\0","Delhi\0","Bangalore\0","Hyderabad\0","Ahmedabad\0","Chennai\0","Kolkata\0","Surat\0","Pune\0","Jaipur\0","Lucknow\0","Kanpur\0","Nagpur\0","Visakhapatnam\0","Indore\0","Thane\0","Bhopal\0","Patna\0","Vadodara\0","Ghaziabad\0","Ludhiana\0","Coimbatore\0","Agra\0","Madurai\0","Nashik\0","Faridabad\0","Meerut\0","Rajkot\0","Varanasi\0","Srinagar\0","Aurangabad\0","Dhanbad\0","Amritsar\0","NaviMumbai\0","Allahabad\0","Ranchi\0","Howrah\0","Jabalpur\0","Gwalior\0","Vijayawada\0","Jodhpur\0","Raipur\0","Kota\0","Guwahati\0","Chandigarh\0","Thiruvananthapuram\0","Solapur\0","Tiruchirappalli\0","Bareilly\0","Moradabad\0","Mysore\0","Tiruppur\0","Gurgaon\0","Aligarh\0","Jalandhar\0","Bhubaneswar\0","Salem\0","Warangal\0","Guntur\0","Bhiwandi\0","Saharanpur\0","Gorakhpur\0","Bikaner\0","Amravati\0","Noida\0","Jamshedpur\0","Bhilai\0","Cuttack\0","Firozabad\0","Kochi\0","Goa\0"};

//global variables.
int v = 71;
Edge edges[20000];
Vertex vertices[100];
int edgeIndex = 0,vertexIndex=0;
int source,sink;
int indeg[100]={0},outdeg[100]={0};

//helper function to add an edge.
void addEdge(int flow,int from,int to,int capacity){
	Edge e;
	e.flow = flow;
	e.from = from;
	e.to = to;
	e.capacity = capacity;
	edges[edgeIndex++] = e;
}

//helper function to return the min of two numbers.
int min(int a,int b){
  return (a>b)?b:a;
}

//returns the capacity of edge between i and j.
int getCapacity(int a, int b){
	int countera[26]={0},counterb[26]={0};
  
  int i;
  for(i=0;i<strlen(cities[a]);i++){
    if(cities[a][i]>='a' && cities[a][i]<='z'){
      countera[cities[a][i]-'a']++;
    }else if(cities[a][i]>='A' && cities[a][i]<='Z'){
      countera[cities[a][i]-'A']++;
    }
  }
  
  for(i=0;i<strlen(cities[b]);i++){
    if(cities[b][i]>='a' && cities[b][i]<='z'){
      counterb[cities[b][i]-'a']++;
    }else if(cities[b][i]>='A' && cities[b][i]<='Z'){
      counterb[cities[b][i]-'A']++;
    }
  }
  
  int common = 0;
  //counting the number of common characters.
  for(i=0;i<26;i++){
    common += min(countera[i],counterb[i]);
  }

  return 2*common;
}

//helper function to check for edges.
int existsEdge(int a,int b){

	int countera[26]={0},counterb[26]={0};
  
  int i;
  for(i=0;i<strlen(cities[a]);i++){
    if(cities[a][i]>='a' && cities[a][i]<='z'){
      countera[cities[a][i]-'a']++;
    }else if(cities[a][i]>='A' && cities[a][i]<='Z'){
      countera[cities[a][i]-'A']++;
    }
  }
  
  for(i=0;i<strlen(cities[b]);i++){
    if(cities[b][i]>='a' && cities[b][i]<='z'){
      counterb[cities[b][i]-'a']++;
    }else if(cities[b][i]>='A' && cities[b][i]<='Z'){
      counterb[cities[b][i]-'A']++;
    }
  }
  
  int common = 0;
  //counting the number of common characters.
  for(i=0;i<26;i++){
    common += min(countera[i],counterb[i]);
  }

  //if it has nothing in common.
  if (!common)
  {
  	return 0;
  }

  //if it has atleast one common then check the length constraint.
	return strlen(cities[b])-strlen(cities[a]) == 1;
}

//helper function to build Edges in the graph.
void buildEdges(){
	int i,j;
	for (i = 0; i < v; ++i)
	{
		//these will be handled later.
		if (!strcmp(cities[i], "Goa\0"))
		{
			source = i;
			continue;
		}

		//try all other vertices.
		for (j = 0; j < v; ++j)
		{
			if (j==i)
			{
				continue;
			}

			if (!strcmp(cities[j],"Thiruvananthapuram\0"))
			{
				sink = j;
				continue;
			}

			//check if an edge exists between i and j.
			if (existsEdge(i,j))
			{
				indeg[j]++;
				outdeg[i]++;
				addEdge(0,i,j,getCapacity(i,j));
			}
		}

	}
}

//adds special edges for the source and sink.
void handleSpecialEdges(){
	
	//for goa
	int i;
	for (i = 0; i < v; ++i)
	{
		if(i==source) continue;

		if (!indeg[i])
		{
			addEdge(0, source, i, 20);
			indeg[i]++;
			outdeg[source]++;
		}		
	}

	//for Thiruvananthapuram
	for (i = 0; i < v; ++i)
	{
		if (i==sink)
		{
			continue;
		}

		if (!outdeg[i])
		{
			addEdge(0, i, sink, 20);
			outdeg[i]++;
			indeg[sink]++;
		}
	}
}

//helper function to initialise the preflow.
void initialise(){
	
	//setting height of source to v.
	vertices[source].h = v;

	int i;
	for (i = 0; i < edgeIndex; ++i)
	{
		//if edges is from source
		if (edges[i].from == source)
		{
			edges[i].flow = edges[i].capacity;

			//add excess flow.
			vertices[edges[i].to].e_flow += edges[i].flow;
			
			//adding reversed edge in residual graph.
			addEdge(-edges[i].flow, edges[i].to,edges[i].from,0);
		}
	}
}

//returns the index of vertex with overflow.
int findOverflow(){
	int i;
	for (i = 0; i < v; ++i)
	{
		if (i==source || i==sink)
		{
			continue;
		}

		//we have found our overflowing vertex.
		if (vertices[i].e_flow>0)
		{
			return i;
		}
	}
	//if no such edge is found.
	return -1;
}

//updates the reverse flow for the flow added.
void updateReverseEdgeFlow(int i,int flow){

	int from = edges[i].to , to = edges[i].from;

	int j;
	for (j = 0; j < v; ++j)
	{
		if (edges[j].to == to && edges[j].from == from)
		{
			edges[j].flow -= flow;
			return;
		}
	}

	//adding reverse edges
	Edge e;
	e.flow = 0;
	e.capacity = flow;
	e.from = from;
	e.to = to;
	edges[edgeIndex++]=e;
}

//push from the vertex u.
int push(int u){
	int i;

	//iterate over all the edges.
	for (i = 0; i < edgeIndex; ++i)
	{
		if (edges[i].from == u)
		{
			
			if (edges[i].capacity == edges[i].flow)
			{
				continue;
			}

			//flow only possible downwards.
			if (vertices[u].h> vertices[edges[i].to].h)
			{
				//find the flow available to push through that edge.
				int flow = min(edges[i].capacity - edges[i].flow,vertices[u].e_flow);

				vertices[u].e_flow -= flow;
				vertices[edges[i].to].e_flow += flow;

				edges[i].flow += flow;
				updateReverseEdgeFlow(i,flow);
				return 1;
			}
		}	
	}
	return 0;
}

//relabel the vertex.
void relabel(int from){
	int mh = INF;

	int i;
	for (i = 0; i < edgeIndex; ++i)
	{
		if (edges[i].from == from)
		{
			//if flow is equal to capacity.
			if (edges[i].flow == edges[i].capacity)
        continue;

      if (vertices[edges[i].to].h < mh)
      {
      	mh = vertices[edges[i].to].h;

      	vertices[from].h = mh + 1; 
      }
		}
	}

}

//the main function that returns the max flow from source to sink.
int getMaxFlow(){
	initialise();

	//while we have a vertex with excess flow.
	while(findOverflow() != -1){
		int u = findOverflow();

		//if possible then push otherwise relabel.
		if (!push(u))
		{
			relabel(u);
		}
	}
	//return the max flow.
	return vertices[sink].e_flow;
}

//initialise the vertices with height and e_flow as 0.
void initialiseVertices(){
	int i;
	for (i = 0; i < v; ++i)
	{int i;
		for (i = 0; i < edgeIndex; ++i)
		{
			//if edges is from source
			if (edges[i].from == source)
			{
				edges[i].flow = edges[i].capacity;

				vertices[edges[i].to].e_flow += edges[i].flow;
			}
		}
		Vertex v;
		v.e_flow = 0;
		v.h = 0;
	}
}

//the main function.
int main(){
  
	//build the graph.
  initialiseVertices();
  buildEdges();
  handleSpecialEdges();

  //getting the maxflow and printing the result.
  int maxflow = getMaxFlow();
  printf("The maximum flow from Goa to Thiruvananthapuram is %d\n", maxflow);
  return 0;
}
