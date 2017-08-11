/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to search for an element in a sorted array using trisection search.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//useful variables
int n,i;

//function to search the element.
int tSearch(int arr[], int search, int start, int end){
	
	//size should atleast be one
	if(end-start>=0){
	
		//the two mid boundaries
		int mid1 = start + (end-start)/3;
		int mid2 = start + 2*(end - start)/3;
		
		//if we found the elment.	
		if(search == arr[mid1]){
			return mid1;
		}else if(search == arr[mid2]){
			return mid2;
		}
		
		//depending on the value of element to search,search in the subarray.
		if(search < arr[mid1]){
			return tSearch(arr,search,start,mid1-1);
		}else if(search > arr[mid1] && search < arr[mid2]){
			return tSearch(arr,search,mid1+1 , mid2-1);
		}else{
			return tSearch(arr,search,mid2+1,end);
		}
	}	
	//element not found
	return -1;
}

int main(){
	
	//getting input
	printf("Enter the size of the sorted list: ");
	scanf("%d",&n);
	
	int arr[n],temp[n];
	
	printf("Enter the elements one by one: ");
	for(i=0;i<n;i++){
		scanf("%d",arr+i);
		temp[i]=arr[i];
	}
	
	//verifying the input
	for(i=0;i<n;i++){
		int j;
		for(j=i+1;j<n;j++){
			if(temp[j]<temp[i]){
				int x = temp[i];
				temp[i] = temp[j];
				temp[j] = x;
			}
		}
	}
	
	//checking if the input is sorted or not
	int inputOk = 1;
	for(i=0;i<n;i++){
		if(temp[i] != arr[i]){
			inputOk = 0;
			break;
		}
	}
	
	//printing the answer after calculating.s
	if(inputOk){
		printf("Enter the number you want to search: ");
		int search;
		scanf("%d",&search);
		int index = tSearch(arr,search,0,n-1);
		if(index ==-1){
			printf("\nElement not found\n");
		}else{
			printf("\n%d found at index %d(Zero based)\n",search, index);
		}
	}else{
		printf("Input a valid sequence i.e. sorted.\n");
	}
	
	return 0;
}
