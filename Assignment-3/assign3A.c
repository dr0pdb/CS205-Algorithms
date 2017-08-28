/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to calculate the median of an array of numbers using recursion.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
int n,i;

//function to recursively find the median of the array
int findMedian(int arr[],int start,int end,int index){
	
	int randomIndex;

	if (end-start)
	{
		randomIndex = (rand()%(end-start))+start;
	}else{
		randomIndex = (start + end)/2;
	}
	
	int *part1,*part2;
	part1 = (int*)malloc((end-start+1)*sizeof(int));
	part2 = (int*)malloc((end-start+1)*sizeof(int));
	
	int lesser=0,greater=0;
	//counting and dividing the array into two parts, one with bigger elements and one with smaller elements
	for(i=start;i<=end;i++){
		if(arr[i]>arr[randomIndex] && i != randomIndex){
			part2[greater++]=arr[i];

		}else if( arr[i]<arr[randomIndex] && i != randomIndex){
			part1[lesser++]=arr[i];
		}
	}
	
	//recursing based on condition
	if(index<lesser){
		return findMedian(part1,0,lesser-1,index);
	}else if(index==lesser){
		return arr[randomIndex];
	}else{
		return findMedian(part2,0,greater-1,index-lesser-1);
	}
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
	int median = findMedian(numbers,0,n-1,(n-1)/2);
	printf("The median of the array is : %d\n",median);
	return 0;
}
