/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to recursively sort the array by finding max and min.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int minm;
	int maxm;
};

//useful variables
int sortedArray[100];
int n,i,k,begin,end;

//Helper function to find min of two numbers
int min(int a , int b){
	if(a>b){
		return b;
	}
	return a;
}

//find max of two numbers
int max(int a , int b){
	if(a>b){
		return a;
	}
	return b;
}

//to calculate the min and max element of an array
struct node* calcMinMax(int arr[],int used[],int index){
	
	//base case
	if(index == n-1){
		struct node* ret;
		ret = (struct node*) malloc(sizeof(struct node));
		ret->minm = arr[n-1];
		ret->maxm = arr[n-1];
		return ret; 
	}
	
	struct node *ans;
	ans = (struct node*) malloc(sizeof(struct node));
	
	//recurse
	if(!used[index]){
		ans->minm = min(arr[index],calcMinMax(arr,used,index+1)->minm);
		ans->maxm = max(arr[index],calcMinMax(arr,used,index+1)->maxm);
		return ans;
	}else{
		return calcMinMax(arr,used,index+1);
	}
	
}

//To sort the array
void calcAns(int arr[],int used[]){
	
	int notUsed=0;
	for(k=0;k<n;k++){
		if(!used[k]){
			notUsed++;
		}
	}
	
	//sorted
	if(notUsed==0){
		return;
	}
	
	//find max and min
	struct node *temp = calcMinMax(arr,used,0);
	
	sortedArray[begin++]=temp->minm;
	sortedArray[end--]= temp->maxm;
	
	
	//searching and making the index marked as used
	for(k=0;k<n;k++){
		if(arr[k]==temp->minm){
			if(used[k] ==0){
					used[k]=1;
					break;
			}
		}
	}
	
	for(k=0;k<n;k++){
		if(arr[k]==temp->maxm){
			if(used[k] ==0){
					used[k]=1;
					break;
			}
		}
	}
	
	//recurse
	calcAns(arr,used);
}


int main(){
	
	//getting the input
	printf("Enter the size of the array: ");
	scanf("%d",&n);
	begin=0,end=n-1;
	
	//variables
	int arr[n];
	int used[n];
	printf("Enter the elements one by one: ");
	
	for(i=0;i<n;i++){
		scanf("%d",arr+i);
		used[i]=0;
	}
	
	//solve
	calcAns(arr,used);
		
	//printing the array
	printf("Here is the sorted Array:");
	for(i=0;i<n;i++){
		printf(" %d ",sortedArray[i]);
	}
	printf("\n");
	
	return 0;
}
