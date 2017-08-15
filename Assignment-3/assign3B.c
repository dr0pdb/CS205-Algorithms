/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to check whether a string is evenWord string or not
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
int n,i;
int counter[26]={0};

//counting the number of each character in the string
void prepareCounter(char string[]){

	char a = string[0];
	counter[a-'a']++;
	
	//base case.
	if(strlen(string)==1){
		return;
	}
	
	char temp[1000];
	
	strcpy(temp,string+1);
	//recursively counting
	prepareCounter(temp);
}

//checking whether the string is even
int check(int count){
	
	//base case
	if(count==26){
		return 1;
	}
	
	//if its odd then it can't be evenString
	if(counter[count] %2 !=0){
		return 0;
	}else{
		return check(count+1);
	}
}

int main(){
	
	char str[1000];
	
	//getting the input
	printf("Enter the string to be checked: ");
	scanf("%s",str);
	
	//finding and printing the answer.
	prepareCounter(str);
	int answer = check(0);
	if(answer){
		printf("The string is an even string\n");
	}else{
		printf("The string is not an even string\n");
	}
	return 0;
}
