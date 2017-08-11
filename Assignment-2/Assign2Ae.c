/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to recursively calculate the sum of digits of a number.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//function to calculate the sum of digits.
long long calcSum(long long a){
	//if it is a one digit number return it.
	if(a/10 ==0){
		return a;
	}
	
	//return the last digit+ sum of remaining digits
	printf("-> %lld ",a%10 +calcSum(a/10));
	return calcSum(a%10 + calcSum(a/10));
}

int main(){
	
	//taking the input
	long long a;
	printf("Enter the number whose sum is to be calculated: ");
	scanf("%lld",&a);
	
	//calculating and printing the answer
	printf("The recursive sum of the digits is %lld ",a);
	calcSum(a);
	
	return 0;
}
