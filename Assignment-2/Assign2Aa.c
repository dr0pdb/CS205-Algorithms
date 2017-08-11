/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to recursively find the min and max digits of a number.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long long calcAns(long long a){
	if(a/10==0){
		if(a%2==0){
			return 0;
		}else{
			return 1;
		}
	}
	
	if((a%10)%2==0){
		return calcAns(a/10);
	}else{
		return 1 + calcAns(a/10);
	}
}

int main(){
	
	//taking the input
	long long a;
	printf("Enter the number : ");
	scanf("%lld",&a);
	
	//calculating and printing the answer
	long long ans = calcAns(a);
	printf("The number of odd digits is %lld",ans);	
	return 0;
}
