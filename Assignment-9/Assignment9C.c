/*
	Name - Saurav Roll-1601CS41.
	The aim of this program is to find the optimal location of restraunts to be set up in a city.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global varialbes.
int v,e;
char names[400][400];
int size[400]={0};
double dist[400][400];
double traffic[400][400];
int used[400]={0};
int inrange[400][400];
int inrangeCount[400]={0};
int p[400];

//returns the minimum of two numbers.
double min(double a, double b){
	if (a>b)
	{
		return b;
	}
	return a;
}

//returns the max of two numbers.
int max(int a, int b){
	if (b<a)
	{
		return a;
	}
	return b;
}

//it returns the edit distance between two strings.
double editdistance(char a[], char b[]){
	int m,n;
	m = strlen(a);
	n = strlen(b);
	double dp[m+1][n+1];

	int i,j;
	for (i = 0; i <= m; ++i)
	{
		for (j = 0; j <=n; ++j)
		{
			if (!i)
			{
				dp[i][j] = j;
			}

			else if (!j)
			{
				dp[i][j]= i;
			}
			else if (a[i-1] == b[j-1])
			{
				dp[i][j] = dp[i-1][j-1];
			}
			else{
				dp[i][j] = 1 + min(dp[i][j-1],min(dp[i-1][j],dp[i-1][j-1]));
			}
		}
	}
	return dp[m][n];
}

//function to print the path.
void printPath(int i){
	if (p[i] == i)
	{
		printf(" %s ",names[i]);
		return;
	}
	printPath(p[i]);
	printf(" %s ",names[i]);
}


int main()
{
	//getting input.
	int i;
	printf("Enter the number of vertices: ");
	scanf("%d",&v);

	printf("Enter their names one by one(alphabetical characters only): ");
	for (i = 0; i < v; ++i)
	{
		p[i]=i;
		scanf("%s",&names[i]);
	}
	
	//getting traffic values.
	printf("Enter the value of traffic one by one( 0.5 - 2 )\n");
	for (i = 0; i < v; ++i)
	{
		int j;
		for (j = i+1; j < v; ++j)
		{
			printf("%s <-> %s : ", names[i],names[j]);
			scanf("%lf",&traffic[i][j]);
			traffic[j][i]=traffic[i][j];
		}
	}

	//calculating edit distance.
	for (i = 0; i < v; ++i)
	{
		int j;
		for (j = i+1; j < v; ++j)
		{
			dist[i][j] = editdistance(names[i],names[j]);
			dist[j][i] = dist[i][j];
		}
	}	


	//counting all the nearby elements for each.
	for (i = 0; i < v; ++i)
	{
		int j;
		for (j = i+1; j < v; ++j)
		{
			if (traffic[i][j]*dist[i][j]<=30)
			{
				size[i]++;
				size[j]++;
				inrange[i][inrangeCount[i]++]=j;
				inrange[j][inrangeCount[j]++]=i;
			}
		}
	}

	//useful variables for final answer.
	int usedCount=0;
	int finalAnswer[400],answerIndex=0;

	//untill we have visited all the localities.
	while(usedCount<v){
		int maxm = -1,maxIndex=0;

		//finding the one with max reachable localities.
		for (i = 0; i < v; ++i)
		{
			if (!used[i])
			{
				if (maxm<inrangeCount[i])
				{
					maxm = inrangeCount[i];
					maxIndex = i;
				}
			}	
		}

		used[maxIndex]=1;
		usedCount++;
		finalAnswer[answerIndex++]=maxIndex;

		int usedThisTime[400]={0};

		//marking sites reachable from the maxIndex as visited.
		for (i = 0; i < size[maxIndex]; ++i)
		{
			int curr = inrange[maxIndex][i];
			if (!used[curr])
			{
				used[curr]=1;
				usedThisTime[curr]=1;
				p[curr]=maxIndex;
				usedCount++;
				inrangeCount[maxIndex]--;
			}
		}

		for (i = 0; i < v; ++i)
		{
			if (i==maxIndex)
			{
				continue;
			}
			int j;
			for (j = 0; j < size[i]; ++j)
			{
				if (usedThisTime[j])
				{
					inrangeCount[i]--;
				}
			}
		}
	}
	
	//printing the location of dominos.
	printf("The location of dominos restraunts are: ");
	for (i = 0; i < answerIndex; ++i)
	{
		printf(" %s ",names[finalAnswer[i]]);
	}	

	//printing the paths.
	printf("\nThe paths taken for each of the localities\n");

	for (i = 0; i < v; ++i)
	{
		printf(" %s :", names[i]);
		printPath(i);
		printf("\n");
	}

	return 0;
}