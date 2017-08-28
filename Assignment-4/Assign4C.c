/*
	Name - Saurav Roll-1601CS41
	The aim of this program is to calculate the product of two matrices using divide and conquer.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n,i;
int result[100][100];
int **mat1;
int **mat2;

//function to add two matrices.
void add(int ans[][100],int size, int a[][100],int b[][100]){

	int j;
	
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			ans[i][j] = a[i][j] + b[i][j];
		}
	}
}

To recursively calculate the product of two matrices.
void multiply(int ans[][100],int size, int **a , int **b){
	
	int j;
	
	//Base case of the recursion.
	if (size==2)
	{
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				ans[i][j] = 0;
				int k;
				for (k = 0; k < size; ++k)
				{
					ans[i][j] += a[i][k]*b[k][j];
				}
			}
		}
		return;
	}else{
		
		int part1[size/2][size/2];
		int part2[size/2][size/2];
		int part3[size/2][size/2];
		int part4[size/2][size/2];

		//variables to divide the matrix into 4 parts.
		int **a1=(int **)malloc(size/2*sizeof(int*));
		int **a2=(int **)malloc(size/2*sizeof(int*));
		int **a3=(int **)malloc(size/2*sizeof(int*));
		int **a4=(int **)malloc(size/2*sizeof(int*));
		int **b1=(int **)malloc(size/2*sizeof(int*));
		int **b2=(int **)malloc(size/2*sizeof(int*));
		int **b3=(int **)malloc(size/2*sizeof(int*));
		int **b4=(int **)malloc(size/2*sizeof(int*));

		//allocating memory.
		for (j = 0; j < size/2; ++j)
		{
			a1[j] = (int*) malloc(size/2*sizeof(int));
			a2[j] = (int*) malloc(size/2*sizeof(int));
			a3[j] = (int*) malloc(size/2*sizeof(int));
			a4[j] = (int*) malloc(size/2*sizeof(int));
			b1[j] = (int*) malloc(size/2*sizeof(int));
			b2[j] = (int*) malloc(size/2*sizeof(int));
			b3[j] = (int*) malloc(size/2*sizeof(int));
			b4[j] = (int*) malloc(size/2*sizeof(int));
		}

		//dividing the matrices into 4 parts
		for (i = 0; i < size/2; ++i)
		{
			for (j = 0; j < size/2; ++j)
			{
				a1[i][j] = a[i][j];
				b1[i][j] = b[i][j];

				a2[i][j] = a[i][j+size/2];
				b2[i][j] = b[i][j+size/2];

				a3[i][j] = a[i+size/2][j];
				b3[i][j] = b[i+size/2][j];

				a4[i][j] = a[i+size/2][j+size/2];
				b4[i][j] = b[i+size/2][j+size/2];
			}
		}

		//variables for product of two matrices.
		int product1[size/2][size/2],product2[size/2][size/2];
		
		//recursive calls
		multiply(product1,size/2,a1,b1);
		multiply(product2,size/2,a2,b3);
		add(part1,size/2,product1,product2);
		
		multiply(product1,size/2,a1,b2);
		multiply(product2,size/2,a2,b4);
		
		add(part2,size/2,product1,product2);
		
		multiply(product1,size/2,a3,b1);
		multiply(product2,size/2,a4,b3);

		add(part3,size/2,product1,product2);

		multiply(product1,size/2,a3,b2);
		multiply(product2,size/2,a4,b4);

		add(part4,size/2,product1,product2);

		//finally updating the answer
		for (i = 0; i < size/2; ++i)
		{
			for (j = 0; j < size/2; ++j)
			{
				ans[i][j] = part1[i][j];
				ans[i][j+size/2] = part2[i][j];
				ans[i+size/2][j] = part3[i][j];
				ans[i+size/2][j+size/2] = part4[i][j];
			}
		}

		// for (i = 0; i < size; ++i)
		// {
		// 	for (j = 0; j < size; ++j)
		// 	{
		// 		ans[i][j] = 0;
		// 		int k;
		// 		for (k = 0; k < size; ++k)
		// 		{
		// 			ans[i][j] += a[i][k]*b[k][j];
		// 		}
		// 	}
		// }

	}

}

int main(){
	
	//allocating space.
	mat1 = (int **)malloc(100*sizeof(int*));
	mat2 = (int **)malloc(100*sizeof(int*));

	int j;
	for (j = 0; j < 100; ++j)
	{
		mat1[j] = (int*) malloc(100*sizeof(int));
		mat2[j] = (int*) malloc(100*sizeof(int));
	}

	//getting the input.	
	printf("Enter the size of the square matrix: ");
	scanf("%d",&n);

	printf("Enter the first matrix(%d x %d) \n",n,n);
	for (i = 0; i < n; ++i)
	{
		int j;
		for (j = 0; j < n; ++j)
		{
			scanf("%d",&mat1[i][j]);
		}
	}

	printf("Enter the second matrix(%d x %d): \n",n,n);
	for (i = 0; i < n; ++i)
	{
		int j;
		for (j = 0; j < n; ++j)
		{
			scanf("%d",&mat2[i][j]);
		}
	}

	//trivial case
	if (n==1)
	{
		printf("Here is the result matrix(%d x %d) \n",n,n);
		printf("%d ",mat1[0][0]*mat2[0][0]);
	}else{
		multiply(result,n,mat1,mat2);

		//printing the answer.
		printf("\nHere is the result matrix(%d x %d) \n",n,n);
		for (i = 0; i < n; ++i)
		{
			int j;
			for (j = 0; j < n; ++j)
			{
				printf("%d ",result[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
}
