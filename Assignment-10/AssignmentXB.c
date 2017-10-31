/*
	Name - Saurav Roll - 1601CS41.
	The aim of this program is to find the optimal cricket schedule to minimize the travelling expenses.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//global variables
char names[8][50];
int dist[8][8];
int ans[10][512],parent[10][512];
double memo[10][512];

//return distance between two cities.
int dis(int a,int b){
	return dist[a][b];
}

//solving the TSP problem
double solve(int prev , int bmask){
	
	int n = 8;

	if(bmask == ((1 << n) - 1)){
        return 0;
	}

	if (memo[prev][bmask] != -1)
	{
		return memo[prev][bmask];
	}

	double answer = 1000000000.0;

	int i;
	for(i=1;i<n;i++){
		//if it hasn't been visited yet.
		if (i != prev && !(bmask & (1<<i)))
		{
            int changed = ((1<<i) | bmask);
			double temp = dis(prev, i) + solve(i, changed);
            if(temp < answer){
                answer = temp;
                ans[prev][bmask] = i;
            }
		}	
	}
	return memo[prev][bmask] = answer;
}

//prints the final path.
void printdist(int id,int bmask)
{
    if(ans[id][bmask] == -1)
    {
        printf(" %s\n", names[id]);
        return;
    }
    printf("  %s -->> ", names[id]);
    printdist(ans[id][bmask],bmask | 1 << ans[id][bmask]);
}

//initialise the arrays with values.
void initialise(){

	strcpy(names[0],"Chennai\0");
	strcpy(names[1],"Kolkata\0");
	strcpy(names[2],"Indore\0");
	strcpy(names[3],"Bengaluru\0");
	strcpy(names[4],"Nagpur\0");
	strcpy(names[5],"Ranchi\0");
	strcpy(names[6],"Guwahati\0");
	strcpy(names[7],"Hyderabad\0");

	dist[0][1] = 1400; dist[1][0] = dist[0][1];
	dist[0][2] = 1200; dist[2][0] = dist[0][2];
	dist[0][3] = 300;  dist[3][0] = dist[0][3];
	dist[0][4] = 900;  dist[4][0] = dist[0][4];
	dist[0][5] = 1300; dist[5][0] = dist[0][5];
	dist[0][6] = 1900; dist[6][0] = dist[0][6];
	dist[0][7] = 500;  dist[7][0] = dist[0][7];

	dist[1][2] = 1300; dist[2][1] = dist[1][2];
	dist[1][3] = 1600; dist[3][1] = dist[1][3];
	dist[1][4] = 1000; dist[4][1] = dist[1][4];
	dist[1][5] = 300;  dist[5][1] = dist[1][5];
	dist[1][6] = 500;  dist[6][1] = dist[1][6];
	dist[1][7] = 1200; dist[7][1] = dist[1][7];

	dist[2][3] = 1100; dist[3][2] = dist[2][3];
	dist[2][4] = 400;  dist[4][2] = dist[2][4];
	dist[2][5] = 1000; dist[5][2] = dist[2][5];
	dist[2][6] = 1600; dist[6][2] = dist[2][6];
    dist[2][7] = 700;  dist[7][2] = dist[2][7];

	dist[3][4] = 900;  dist[4][3] = dist[3][4];
	dist[3][5] = 1400; dist[5][3] = dist[3][5];
	dist[3][6] = 2000; dist[6][3] = dist[3][6];
    dist[3][7] = 500;  dist[7][3] = dist[3][7];

	dist[4][5] = 700;  dist[5][4] = dist[4][5];
	dist[4][6] = 1400; dist[6][4] = dist[4][6];
    dist[4][7] = 400;  dist[7][4] = dist[4][7];

	dist[5][6] = 700;  dist[6][5] = dist[5][6];
    dist[5][7] = 1000; dist[7][5] = dist[5][7];

	dist[6][7] = 1700; dist[7][6] = dist[6][7];
}

int main(int argc, char const *argv[])
{
	//initialise
	initialise();

	//resetting everything.
	int i;
	for (i = 0; i < 10; ++i)
	{
		int j;
		for (j = 0; j < 512; ++j)
		{
			memo[i][j] = -1;
			ans[i][j] = -1;
		}
	}

	//solving
	double ans = solve(0,1);
	
	//printing the final answer.
	printf("The total cost of travelling will be: %lf\n", ans);
	printf("The final dist will be: ");
	printdist(0,1);
	return 0;
}
