/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to recursively find the binary equivalent representation of a number.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ans[64];
int counter=0;

//Function to recursively calculate the binary representation
void calcAns(long long a){

	//base case
	if(a<2){
		ans[counter]=a;
		return ;
	}
	
	ans[counter++]=a%2;
	//recursively calculate for a/2
	calcAns(a/2);
}

int main(){
	
	//taking the input
	long long a;
	printf("Enter the number : ");
	scanf("%lld",&a);
	
	//calculating and printing the answer
	calcAns(a);
	printf("The binary representation of the number is: ");
	int i;
	for(i=counter;i>=0;i--){
		printf("%d",ans[i]);
	}
	printf("\n");	
	return 0;
}
