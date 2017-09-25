/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to implement ith order statistic in worst case O(n)
*/
#include<stdio.h>
#include<stdlib.h>

//global variables
#define INF 1000000000
int *arr,n;

//helper function to swap two elements of the array.
void swap(int *a,int *b){
	int temp = *a;
    *a = *b;
    *b = temp;
}

//helper function to sort an array.
void sort(int a[],int size){
	int i,j;
	for (i = 0; i < size; ++i)
	{
		for (j = i+1; j < size; ++j)
		{
			if (a[i]>a[j])
			{
				swap(&a[i],&a[j]);
			}			
		}
	}
}

//standard partition function to partition around x.
int partition(int arr[], int l, int r, int x)
{    
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);
 
    i = l;
    int j;
    for (j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
} 

//function to sort an array and return its median.
int findMedian(int a[],int size){
	sort(a,size);
	return a[(size-1)/2];
}

//the actual function to find the kth smallest in O(n)
int findKthSmallest(int a[],int left,int right,int k){

	//check to see the validity of k.
	if (k>0 && k<=right-left+1)
	{	
		//size of the sub-array.
		int size = right-left+1;

		//allocating space to store medians.
		int i,medians[(size+4)/5];
		for (i = 0; i < size/5; ++i)
		{
			medians[i] = findMedian(a+left+i*5,5);
		}

		//if still elements are left.
		if (i*5<size)
		{
			medians[i] = findMedian(a+left+i*5,size%5);
			i++;
		}

		//recursively finding the median of medians.
		int partitionMedian = medians[i-1];
		if (i!=1)
		{
			partitionMedian = findKthSmallest(medians,0,i-1,i/2);
		}

		//using partition to find the correct position.
		int position = partition(a,left,right,partitionMedian);

		//if the pivot is the k-1th element we have the answer.
		if (position-left == k-1)
		{
			return a[position];
		}
		//if pivot is smaller then recurse in left half
		if (position-left > k-1)
		{
			return findKthSmallest(a,left,position-1,k);
		}else{
			return findKthSmallest(a,position+1,right,k-position+left-1);
		}
		
	}
	return INF;
}
//the main function.
int main(int argc, char const *argv[])
{
	//getting the input.
	printf("Enter the size of the array: ");
	scanf("%d",&n);

	//allocating memory.
	arr = (int*)malloc(n*sizeof(int));
	printf("Enter the values one by one: ");
	int i;
	for (i = 0; i < n; ++i)
	{
		scanf("%d",arr+i);
	}

	//getting input.
	printf("Enter the value of k: ");
	int k;
	scanf("%d",&k);

	//finding and printing the answer.
	int ans = findKthSmallest(arr,0,n-1,k);
	printf("The %dth smallest element of the array is: %d\n",k,ans);
	return 0;
}