/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to calculate the product of two numbers using divide and conquer.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//function to reverse a string.
void strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
}

//function to convert a number to it's binary representation.
void convertToBinary(long long value , char c[]){
	
	int j=0;
	while(value){
		c[j++]='0'+value%2;
		value/=2;
	}	
	c[j]='\0';
	strrev(c);
	
}

//function to append zeroes in front of a string to make them of equal length.
int makeSameLength(char a[],char b[]){
	
	int len1 = strlen(a);
	int len2 = strlen(b);
	
	//if same length,then return.
	if(len1 == len2){
		return len1;
	}
	//if string b is smaller
	else if(len1>len2){
		strrev(b);
		
		int j,index=len2;
		for(j=0;j<len1-len2;j++){
			b[index++]='0';
		}
		b[index]='\0';
		strrev(b);
		return len1;	
	}else{
		strrev(a);
		
		int j,index=len1;
		for(j=0;j<len2-len1;j++){
			a[index++]='0';
		}
		a[index]='\0';
		strrev(a);	
		return len2;
	}
}

//function to return the addition of two binary numbers as a string.
char sum[100];
char* addBits(char a[], char b[]){

	//useful variables.
	char tempa[100];
	char tempb[100];

	strcpy(tempa,a);
	strcpy(tempb, b);

	int length = makeSameLength(tempa,tempb);
	int carry=0,index=0; //initialising.

	int j;
	for (j = length-1; j >=0 ; --j)
	{
		int first = tempa[j]-'0';
		int second = tempb[j]-'0';

		int temp = (first ^ second ^ carry);

		sum[index++] = '0'+temp;
		carry = (first&second) | (second&carry) | (first&carry);
	}

	if (carry)
	{
		sum[index++]='1';
	}

	sum[index++]='\0';
	strrev(sum); //return the reversed string.
	return sum;
}

//The actual function that does the multiplication recursively.
long long multiply(char a[], char b[]){

	//make same length first.
	int n = makeSameLength(a, b);


	//base case
	if (n==0)
	{
		return 0;
	}
	if (n==1)
	{
		return (a[0]-'0')*(b[0]-'0');
	}

	int firstHalf = n/2;
	int secondHalf = n-firstHalf;

	char firstleft[100],firstright[100];
	char secondleft[100],secondright[100];

	//dividing into parts
	strncpy(firstleft, a, firstHalf);
	strncpy(secondleft, b, firstHalf);
	strcpy(firstright,a+firstHalf);
	strcpy(secondright, b+firstHalf);

	firstleft[firstHalf]='\0';
	firstright[n]='\0';
	secondleft[firstHalf]='\0';
	secondright[n]='\0';

	//recursive calls.
	long long p1 = multiply(firstleft, secondleft);
	long long p2 = multiply(firstright, secondright);
	char *temp1=addBits(firstleft,firstright);
	char str1[100],str2[100];

	strcpy(str1, temp1);
	char *temp2=addBits(secondleft,secondright);
	strcpy(str2, temp2);
	long long p3 = multiply(str1,str2);

	//returning the answer
	return p1*(1<<(2*secondHalf)) + (p3 - p1 - p2)*(1<<secondHalf) + p2;
}

int main(){
	
	//getting input
	long long a,b;
	printf("Enter two numbers to multiply: ");
	scanf("%lld %lld",&a,&b);
	
	char n1[64],n2[64];
	
	convertToBinary(a,n1);
	convertToBinary(b,n2);
	makeSameLength(n1,n2);

	//calculating and printing the answer.
	long long result = multiply(n1,n2);
	printf("The product of the two numbers is: %lld\n",result);
}
