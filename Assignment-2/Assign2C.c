/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to simulate a recursive mathematical function.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//helper function to solve the problem.
void solve(int n, int steps){
	
	//base case
	if(n==1){
		printf("Final value is 1 and number of steps are %d\n",steps);
		return;
	}
	
	//even
	if(n%2==0){
		if(n/2 !=1){
			printf("Next value is %d\n",n/2);
		}	
		//recurse	
		solve(n/2,steps+1);
	}else{
		printf("Next value is %d\n",3*n+1);
		//recurse
		solve(3*n+1,steps+1);
	}
}

int main(){
	
	//getting the input
	int n;
	printf("Enter the number: ");
	scanf("%d",&n);
	
	//solving the problem
	printf("Initial value is %d\n",n);
	solve(n,0);
	
	return 0;
}
