/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to calculate the maximum sub-array sum using recursion.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
int n,i;

//function to calculate the max of two elements
int max(int a, int b){
	return ((a>b)?a:b);
}

//function to return the left sum and the right sum both including the mid elements
int maxCrossingSum(int array[],int start,int mid , int end){
	
	//calculating the max sum in the right of the mid element
	int curr=0,maxright=-1000000;
	for(i=mid+1;i<=end;i++){
		curr+=array[i];
		maxright = max(maxright,curr);
	}
	
	//calculating the max sum inthe left of the mid element
	curr=0;
	int maxleft=-1000000;
	for(i=mid;i>=start;i--){
		curr+=array[i];
		maxleft = max(maxleft,curr);
	}
	
	return maxleft+maxright;
}

//function to calculate the max subarray sum.
int subArraySum(int array[] , int start,int end){
	
	//base case: single elment then return it
	if(start==end){
		return array[start];
	}	
	
	int mid = (start+end)/2;
	
	//three possibilites: either the max subarray is in left half,right half or includes the mid elements
	return max(maxCrossingSum(array,start,mid,end),max(subArraySum(array,start,mid),subArraySum(array,mid+1,end)));
}

int main(){
	
	//getting the input
	printf("Enter the size of the array: ");
	scanf("%d",&n);
	
	int numbers[n];
	
	printf("Enter the elements of the array: ");
	for(i=0;i<n;i++){
		scanf("%d",&numbers[i]);
	}
	
	//calculating and printing the answer.
	int maxSubArraySum = subArraySum(numbers,0,n-1);
	printf("The maximum sub-array sum is: %d\n",maxSubArraySum);
	return 0;
}
