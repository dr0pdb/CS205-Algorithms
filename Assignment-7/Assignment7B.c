/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to divide an array into pairs whose sum is maximum.
*/

#include<stdio.h>
#include<stdlib.h>

//global variables.
int n,m,pairIndex=0,answerIndex=0;
long long answer=0;

//struct for a pair of integers.
typedef struct node{
	int first,second,firstIndex,secondIndex;
}pair;
pair *pairs,*answerPairs;
int *used;

//helper function to find the absolute value of a number.
int abs(int a){
	if (a<0)
	{
		a*=-1;
	}
	return a;
}

//helper function to check if the pair is valid or not.
int valid(int a, int b){
	if (abs(a-b)<=m)
	{
		return 1;
	}
	return 0;
}

//helper function to print all the possible pairs.
void printPairs(){
	int i;
	for (i = 0; i < pairIndex; ++i)
	{
		printf(" (%d,%d) ",pairs[i].first,pairs[i].second);
	}
	printf("\n");
}

//sorting in descending order.
void sortPairs(){
	int i,j;
	for (i = 0; i < pairIndex; ++i)
	{
		for (j = i+1; j < pairIndex; ++j)
		{
			pair left = pairs[i];
			pair right = pairs[j];
			if ((left.first+left.second)<(right.first+right.second))
			{
				pairs[i]=right;
				pairs[j]=left;
			}
		}
	}
}

//helper function to check whether any element of the pair has already been used or not.
int checkUsed(pair a){
	if (used[a.firstIndex] || used[a.secondIndex])
	{
		return 1;
	}
	return 0;
}

//helper function to print the final answer pairs.
void printAnswers(){
	int i;
	for (i = 0; i < answerIndex; ++i)
	{
		printf(" (%d,%d) ",answerPairs[i].first,answerPairs[i].second);
	}
	printf("\n");
}

int main()
{
	//getting the input.
	printf("Enter the number of values in the list: ");
	scanf("%d",&n);

	//at max we can have nc2 pairs.
	pairs = (pair*)malloc(n*n*sizeof(pair));
	answerPairs = (pair*)malloc(n*n*sizeof(pair));

	//storing the values
	int arr[n],i;
	used = (int*)malloc(n*sizeof(int));

	//getting input.
	printf("Enter the values one by one: ");
	for (i = 0; i < n; ++i)
	{
		scanf("%d",&arr[i]);
		used[i]=0;
	}

	printf("Enter the value of m: ");
	scanf("%d",&m);

	//building the valid pairs.	
	for (i = 0; i < n; ++i)
	{
		int j;
		for (j = i+1; j < n; ++j)
		{
			if (valid(arr[i],arr[j]))
			{
				pair temp;
				int a,b,ai,bi;
				if (arr[i]<arr[j])
				{
					a = arr[i];
					b = arr[j];
					ai = i;
					bi = j;
				}else{
					a = arr[j];
					b = arr[i];
					ai = j;
					bi = i;
				}
				temp.first = a;
				temp.second = b;
				temp.firstIndex = ai;
				temp.secondIndex = bi;
				pairs[pairIndex++]=temp;
			}
		}
	}

	//printing the valid pairs before finding the maximum sum
	printf("The valid pairs are: ");
	printPairs();

	//sorting in descending order.
	sortPairs();

	//finding the pairs for max sum.
	for (i = 0; i < pairIndex; ++i)
	{
		if (!checkUsed(pairs[i]))
		{
			answerPairs[answerIndex++]=pairs[i];
			used[pairs[i].firstIndex]=1;
			used[pairs[i].secondIndex]=1;
			answer+=(pairs[i].first+pairs[i].second);
		}
	}

	//finally printing the answer.
	printf("The final pair list which maximizes the sum is: ");
	printAnswers();
	printf("The maximum sum possible is %lld\n",answer);
	return 0;
}