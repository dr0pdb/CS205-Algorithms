/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to implement a two dimensional min-heap and implement extract-min with O(m+n) complexity.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
#define INF 1000000000
int *arr,m,n,k,**matrix,indexf,indexs;

//function to sort the array
void sort(int array[],int size){
	int i,j;
	for (i = 0; i < size; ++i)
	{
		for (j = i+1; j < size; ++j)
		{
			if (array[i]>array[j])
			{
				int temp = array[j];
				array[j]=array[i];
				array[i]=temp;
			}
		}
	}
}

//function which returns whether the matrix is full or not.
int full(){
	if (indexf==m-1 && indexs==n-1)
	{
		return 1;
	}
	return 0;
}

//function to print the table.
void printMatrix(){
	int i;
	printf(" ----Young tableau---- \n");
	for (i = 0; i < m; ++i)
	{
		int j;
		for (j = 0; j < n; ++j)
		{
			if (matrix[i][j]!=INF)
			{
				printf(" %d ",matrix[i][j]);
			}else{
				printf(" INF ");
			}
			
		}
		printf("\n");
	}
}

//function which extracts the minimum value and reshuffles in O(m+n) time.
int extractMin(){
	if (indexf==0 && indexs==0)
	{
		printf("The Young tableau is empty.\n");
		return 0;
	}

	int ans = matrix[0][0];
	int i;
	//O(n) operation.
	for (i = 0; i < n; ++i)
	{
		if (i<n-1)
		{
			matrix[0][i]=matrix[0][i+1];
		}else{
			matrix[0][i] = INF;
		}

	}

	int j;
	//O(m) operation.
	for (j = 0; j < m; ++j)
	{
		if (j<m-1)
		{
			matrix[j][n-1]=matrix[j+1][n-1];
		}else{
			matrix[j][n-1]=INF;
		}
	}

	//updating the index of last element
	if (indexs==0)
	{
		indexs=n-1;
		indexf--;
	}else{
		indexs--;
	}
	matrix[m-1][n-1]=INF;
	return ans;
}

int main()
{
	//getting the input
	int i;	
	printf("Enter the value of m and n respectively: ");
	scanf("%d %d",&m,&n);

	matrix = (int**)malloc(m*sizeof(int*));
	for (i = 0; i < m; ++i)
	{
		matrix[i]=(int*)malloc(n*sizeof(int));
	}

	//initialising the matrix with INFINITY
	for (i = 0; i < m; ++i)
	{
		int j;
		for (j = 0; j < n; ++j)
		{
			matrix[i][j]=INF;	
		}
	}

	//getting input array
	printf("Enter the size of the array(k): ");
	scanf("%d",&k);

	if (k>m*n || k<0)
	{
		printf("The value of k should be less than m*n\n");
		return 0;
	}

	//allocating the memory
	arr = (int*)malloc(k*sizeof(int));

	printf("Enter the elements one by one: ");

	//getting the input
	for (i = 0; i < k; ++i)
	{
		scanf("%d",arr+i);
	}

	//sorting for insertion
	sort(arr,k);

	//indexf-row number and indexs-col number
	indexf=0,indexs=0;
	for (i = 0; i < k; ++i)
	{
		matrix[indexf][indexs]=arr[i];
		indexs++;
		if (indexs==n)
		{
			indexf++;
			indexs=0;	
		}	
	}	

	//printing before extract min
	printMatrix();
	printf("\n------The extracted min value %d------ \n",extractMin());
	//after extract min
	printMatrix();
	return 0;
}