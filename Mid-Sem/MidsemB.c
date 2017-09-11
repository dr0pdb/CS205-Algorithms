/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to implement a two dimensional min-heap and implement new element insertion in O(m+n).
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

//function to insert a new value into the table.
void insert(int value){
	int i,j;

	//if the first entry of the last row is filled 
	//It will take at max O(n) operations.
	if (matrix[m-1][0] != INF)
	{
		int j=1;
		for (j = 1; j < n-1; ++j)
		{
			matrix[m-1][j+1]=matrix[m-1][j];		
		}
	}

	matrix[m-1][0]=value;
	int index=m-1;

	//O(m) operations.
	while(index>0 && matrix[index][0]<matrix[index-1][0]){
		int temp = matrix[index][0];
		matrix[index][0]=matrix[index-1][0];
		matrix[index-1][0]=temp;
		index--;
	}

	//O(n) operations in the worst case.
	if (index>0 && matrix[index][0] > matrix[index-1][n-1])
	{
		return;
	}else{
		//swapping value once.
		int temp = matrix[index][0];
		matrix[index][0]=matrix[index-1][n-1];
		matrix[index-1][n-1]=temp;

		index--;
		int y=n-1;

		//constantly swapping inside a single row.
		while(matrix[index][y]<matrix[index][y-1]){
			int temp = matrix[index][y];
			matrix[index][y]=matrix[index][y-1];
			matrix[index][y-1]=temp;
			y--;
		}
	}	
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

	//printing before inserting element
	printMatrix();
	
	if (full())
	{
		printf("The table is already full hence no insertion.\n");
		return 0;
	}

	//getting the new element to insert.
	int newElement;
	printf("Enter the new element to insert: ");
	scanf("%d",&newElement);

	insert(newElement);

	//after inserting element
	printMatrix();
	return 0;
}
