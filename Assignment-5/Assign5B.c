/*

	Name- Saurav Roll-1601CS41
	The aim of this program is to use a linear-time algorithm for sorting a struct.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)


//struct to denote the career of a player.
typedef struct career{
	char name[50];
	long long score;
} career;

//global variables.
int n;
career *careers;

//helper function to sort the scores.
void countSort(int exp){
	career output[n]; 
	int i,counter[10]={0};

	//counting the occurence of each digit.
	for (i = 0; i < n; ++i)
	{
		counter[(careers[i].score/exp)%10]++;
	}	

	//getting the correct position.
	for (i = 1; i < 10; ++i)
	{
		counter[i]+=counter[i-1];
	}

	//getting the right values into the output.
	for (i = n-1; i >=0 ; i--)
	{
		output[counter[(careers[i].score/exp)%10]-1].score = careers[i].score;
		strcpy(output[counter[(careers[i].score/exp)%10]-1].name,careers[i].name);
		counter[(careers[i].score/exp)%10]--;
	}

	//copying contents.
	for (i = 0; i < n; ++i)	
	{
		careers[i].score = output[i].score;
		strcpy(careers[i].name, output[i].name);
	}
}

//helper function to sort the strings.
void countSortString(int index){
	career output[n];
	int i,counter[26]={0};

	//counting the occurence of each character.
	for (i = 0; i < n; ++i)
	{
		int temp;
		if(careers[i].name[index] >='a' &&  careers[i].name[index] <='z'){
			temp= careers[i].name[index]-'a';
		}else if(careers[i].name[index] >='A' &&  careers[i].name[index] <='Z'){
			temp= careers[i].name[index]-'A';
		}
		counter[temp]++;
	}
	//getting the correct position.
	for (i = 1; i < 26; ++i)
	{
		counter[i]+=counter[i-1];
	}
	//getting the right values into the output.
	for (i = n-1; i >=0 ; i--)
	{
		int temp;
		if(careers[i].name[index] >='a' &&  careers[i].name[index] <='z'){
			temp= careers[i].name[index]-'a';
		}else if(careers[i].name[index] >='A' &&  careers[i].name[index] <='Z'){
			temp= careers[i].name[index]-'A';
		}
		output[counter[temp]-1].score = careers[i].score;
		strcpy(output[counter[temp]-1].name, careers[i].name);
		counter[temp]--;
	}
	//copying contents.
	for (i = 0; i < n; ++i)
	{
		careers[i].score = output[i].score;
		strcpy(careers[i].name, output[i].name);
	}
}

//helper function to get the min length among the array.
int getMinLength(){
	int i,min=1000000;
	for (i = 0; i < n; ++i)
	{
		min = MIN(min, strlen(careers[i].name)); 
	}

	return min;
}

//helper function to get the maximum score
int getMax(){
	int i,maxm=-1;
	for (i = 0; i < n; ++i)
	{
		maxm = MAX(maxm, careers[i].score); 
	}

	return maxm;
}

//The main RadixSort function.
void radixSort(){
	int i;
	//sorting according to alphabets
	int m = getMinLength();
	for (i = m-1; i >= 0; i--)
	{
		countSortString(i);
	}

	//sorting according to scores.
	m = getMax();


	for (i = 1;m/i > 0; i*=10)
	{
		countSort(i);
	}

	
}

//helper function to print the array.
void printArray(){
	int i;
	printf("\n---------Final sorted order---------\n");
	for (i = 0; i < n; ++i)
	{
		printf("%s\t%lld\n",careers[i].name,careers[i].score);
	}
	printf("\n");
}

//main function
int main(){

	//getting the input
	printf("Enter the number of players: ");	
	scanf("%d",&n);
		
	careers = (career*)malloc(n*sizeof(career));

	int i;
	printf("---------Enter details---------\n");
	for (i = 0; i < n; ++i)
	{
		printf("Details for player %d\n",i+1);
		printf("Name: ");
		scanf (" %[^\n]%*c", careers[i].name);
		printf("Score: ");
		scanf("%lld",&careers[i].score);
	}

	//sorting and printing.
	radixSort();
	printArray();
	return 0;
}
