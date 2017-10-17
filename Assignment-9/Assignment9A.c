/*
	Name - Saurav Roll-1601CS41.
	The aim of this program is to find the optimal location of borewells and pipeline connections.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables.
int v=0,e=0;
char names[400][100];
int size[400]={0};
int adjlist[400][400];
double selfcost[400];
double totalcost=0;

typedef struct node{
	int from,to,wt;
}node;

node edgelist[400];
node mst[400];
int mst_index=0;

//VARIABLES FOR UNION-FIND.
int p[400],ranks[400];


//if it is the representative then return itself otherwise return parent of it's immediate parent.
int findSet(int i){
	if(p[i]==i){
		return i;
	}
	
	return p[i]=findSet(p[i]);
 }

//returns whether i and j belong to the same set.
int isSameSet(int i, int j){ 
	return findSet(i) == findSet(j);
}

//helper function to join i and j.
void join(int i, int j){
 	if (!isSameSet(i,j))
 	{
 		int x = findSet(i),y = findSet(j);
 		if(ranks[x] > ranks[y]){
 			p[y] = x;
 		}else{
 			p[x] = y;
 			if (ranks[x] == ranks[y])
 			{
 				ranks[y]++;
 			}
 		}
	}
}

//returns the absolute value of a.
int abs(int a){
	if(a<0){
		a*=-1;
	}
	return a;
}

//returns the cost of borewell.
int cost(char s[],int size){
	int cos = 0;
	int i;
	for (i = 0; i < size; ++i)
	{
		cos+=s[i];
	}

	return cos;
}

//checks if their is an edge from a to b.
int checkNeighbour(char a[] , int size1, char b[], int size2){
	int i,counta[26]={0},countb[26]={0};
	
	for(i=1;i<size1;i++){
		if(a[i]>='a' && a[i]<='z'){
			counta[a[i]-'a']++;
		}else{
			counta[a[i]-'A']++;
		}
	}
	
	for(i=0;i<size2;i++){
		if(b[i]>='a' && b[i]<='z'){
			countb[b[i]-'a']++;
		}else{
			countb[b[i]-'A']++;
		}
	}
	
	int flag = 0;
	
	for(i=0;i<26;i++){
		if(counta[i] != countb[i]){
			flag = 1;
			break;
		}
	}
	
	//if flag is zero then they have the edge.
	if(!flag){
		return 1;
	}
	
	if(a[0]>='a' && a[0]<='z'){
			counta[a[0]-'a']++;
	}else{
		counta[a[0]-'A']++;
	}
	
	int diff = 0;
	flag = 0;
	
	for(i=0;i<26;i++){
		if(counta[i] != countb[i]){
			if(counta[i]>countb[i]){
				return 0;
			}else{
				diff += countb[i]-counta[i];

				//if diff >1 then they cannot have an edge.
				if(diff>1){
					return 0;
				}
			}
		}
	}
	
	return 1;
}

int main()
{
	int used[400]={0}; 

	//taking input.
	printf("Enter the number of vertices: ");
	scanf("%d",&v);
	
	printf("Enter their names one by one (alphabetical characters only) : ");
	int i;
	
	for(i=0; i<v;i++){
		scanf("%s",&names[i]);
		selfcost[i] = cost(names[i],strlen(names[i]));
		selfcost[i]/=1.0*strlen(names[i]);
		totalcost+=selfcost[i];
		used[i]=1;
	}
	
	//checking for edges.
	for(i=0;i<v;i++){
		int j;
		for(j=i+1;j<v;j++){
			if(checkNeighbour(names[i],strlen(names[i]),names[j],strlen(names[j]))){
				int wt = abs(cost(names[i],strlen(names[i]))-cost(names[j],strlen(names[j])));
				node n;
				n.from = i;
				n.to = j;
				n.wt = wt;
				edgelist[e++] = n;
			}
			
			if(checkNeighbour(names[j],strlen(names[j]),names[i],strlen(names[i]))){
				int wt = abs(cost(names[j],strlen(names[j]))-cost(names[i],strlen(names[i])));
				node n;
				n.from = j;
				n.to = i;
				n.wt = wt;
				edgelist[e++] = n;
			}
		}
	}
	 
	//sorting the edgelist.
	for(i=0;i<e;i++){
		int j;
		for(j=i+1;j<e;j++){
			if(edgelist[i].wt>edgelist[j].wt){
				int t1,t2,t3;
				t1 = edgelist[i].from;
				t2 = edgelist[i].to;
				t3 = edgelist[i].wt;
				
				edgelist[i].from = edgelist[j].from;
				edgelist[i].to = edgelist[j].to;
				edgelist[i].wt = edgelist[j].wt;
				
				edgelist[j].from = t1;
				edgelist[j].to = t2;
				edgelist[j].wt = t3;
			}
		}
	}
	
	//building the mst.
	for(i=0;i<400;i++){
		p[i]=i;
		ranks[i]=0;
	}
	
	//kruskal algorithm.
	int edgessofar = 0,index = 0;
	while(edgessofar<v-1){
		node n = edgelist[index++];
		int from = n.from;
		int to = n.to;
		
		if(!isSameSet(from,to)){
			mst[mst_index++]=n;
			edgessofar++;
			join(from,to);	
		}
	} 
	
	//final list of edges.
	node finalList[400];
	int finalindex=0;

	for(i=0;i<mst_index;i++){
		node curr = mst[i];

		int from= curr.from,to = curr.to,edgewt = curr.wt;
		
		if (edgewt<selfcost[from]+selfcost[to])
		{
			if (selfcost[from]>selfcost[to])
			{
				used[to]=0;
				totalcost-=selfcost[to];
			}else{
				used[from]=0;
				totalcost-=selfcost[from];
			}			
			totalcost+=edgewt;
			finalList[finalindex++]=curr;
		}
	} 

	//printing the final result
	printf("Houses with borewells: ");
	for (i = 0; i < v; ++i)
	{
		if (used[i])
		{
			printf(" %s ",names[i]);
		}
	}
	printf("\n");
	printf("Final pipeline connections: ");
	for (i = 0; i < finalindex; ++i)
	{
		printf(" %s -> %s ", names[finalList[i].from],names[finalList[i].to]);
	}
	printf("\n");
	printf("Minimum possible cost is %.2lf\n",totalcost);
	return 0;
}
