/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to recursively find the min and max digits of a number.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int minm;
	int maxm;
};


//Helper function to calculate the min of two numbers
long long min(long long a, long long b){
	if(a>b){
		return b;
	}
	return a;
}

//Helper function to calculate the max of two numbers
long long max(long long a, long long b){
	if(a>b){
		return a;
	}
	return b;
}


//Recursively calculate the min and max
struct node* calcAns(long long a){
	
	//Base case- single digit number
	if(a/10 ==0){
		struct node *ans;
		ans = (struct node*) malloc(sizeof(struct node));
		ans->minm = a;
		ans->maxm = a;
		return ans;
	}
	
	//recursive approach
	struct node *ret;
	ret = (struct node*) malloc(sizeof(struct node));
	struct node *rec = calcAns(a/10);
	ret->minm = min(a%10, rec->minm);
	ret->maxm = max(a%10,rec->maxm);
	return ret;
}

int main(){
	
	//taking the input
	long long a;
	printf("Enter the number : ");
	scanf("%lld",&a);
	
	//calculating and printing the answer
	struct node *ans = calcAns(a);
	printf("Minimum digit - %d and Maximum digit - %d ",ans->minm,ans->maxm);	
	return 0;
}
