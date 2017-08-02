/*
	Name-Saurav	Roll-1601CS41
	The aim of this program is to create two linkedlist of vowels and consonants arranged.
	It should also report palindromes if any.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct node 
{
	char c;
	struct node *next;
} List;

//useful variables
struct node *head1, *head2, **list1 , **list2;
int n,i,j;

//array of vowels
char vowels[10]={'a','A','e','E','i','I','o','O','u','U'};

//function to check whether a character is vowel or not
int check(char a){
	for (j = 0; j < 10; ++j)
	{
		if (a == vowels[j])
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	//getting the input
	printf("Enter the number of students: ");    
    scanf("%d",&n);
    
    char students[n][50];
     
    printf("Enter the name of students, one per line: ");
    for(i=0; i<n;i++){
        scanf("%s",students[i]);
    }

    //finding the first letter of each name
    char firstLetter[n];
    int insertIndex=0;
    for (i = 0; i < n/2; ++i)
    {
    	if (check(students[i][0]))
    	{
    		firstLetter[insertIndex++]=students[i][0];
    	}
    }

    for (i = 0; i < n/2; ++i)
    {
    	if (!check(students[i][0]))
    	{
    		firstLetter[insertIndex++]=students[i][0];
    	}
    }

    insertIndex = n/2;

    for (i = n/2; i < n; ++i)
    {
    	if (check(students[i][0]))
    	{
    		firstLetter[insertIndex++]=students[i][0];
    	}
    }

    for (i = n/2; i < n; ++i)
    {
    	if (!check(students[i][0]))
    	{
    		firstLetter[insertIndex++]=students[i][0];
    	}
    }

    //creating the list.
    list1 = (List**) malloc((n/2)*sizeof(List*));
	list2 = (List**) malloc((n-n/2)*sizeof(List*));

    //adding elements to first linked list
    for(i=0;i<(n/2);++i){
        
    	list1[i] = (List*) malloc(sizeof(List));
    	list1[i]->c = firstLetter[i];
    	list1[i]->next = NULL;

    	if (!i)
        {	
        	head1 = list1[0];
        }
    }

    //adding elements to the second linked list
    for (i = n/2; i < n; ++i)
    {
    	list2[i-n/2] = (List*) malloc(sizeof(List));
    	list2[i-n/2]->c = firstLetter[i];
		list2[i-n/2]->next = NULL;

		if (i == n/2)
    	{
     		head2= list2[0];
     	}
    }

     //printing the two lists
    printf("Here is the first list: ");
    for (i = 0; i < n/2; ++i)
    {
    	if (i==0)
    	{
    		printf("%c",students[i][0]);	
    	}else{
    		printf("->%c",students[i][0]);
    	}
    	
    }
    printf("\n");

    printf("Here is the second list: ");
    for (i = 0; i < n-n/2; ++i)
    {
    	if (i==0)
    	{
    		printf("%c",students[i][0]);	
    	}else{
    		printf("->%c",students[i][0]);
    	}
    }
    printf("\n");


    //printing the first arranged list
    printf("Here is the first arranged list: ");
    for (i = 0; i < n/2; ++i)
    {
    	if (i==0)
    	{
    		printf("%c",list1[i]->c);	
    	}else{
    		printf("->%c",list1[i]->c);
    	}
    	
    }
    printf("\n");

    //printing the second arranged list
    printf("Here is the second arranged list: ");
    for (i = 0; i < n-n/2; ++i)
    {
    	if (i==0)
    	{
    		printf("%c",list2[i]->c);	
    	}else{
    		printf("->%c",list2[i]->c);
    	}
    }
    printf("\n");

    //finding palindrome in the first list
    for (i = 0; i < n/2; ++i)
    {
    	for (j = i+1; j < n/2; ++j)
    	{
    		int isPalindrome = 1;
    		int x=i,y=j;
    		while(x<=j && y>=i){
    			if (firstLetter[x] != firstLetter[y])
    			{
    				isPalindrome=0;
    			}
    			x++;
    			y--;
    		}
    		if (isPalindrome)
    		{
    			x=i;
    			printf("This is a palindrome:");
    			while(x<=j){
    				printf(" %c",firstLetter[x]);
    				x++;
    			}
    			printf("\n");
    		}
    	}
    }
	
	//finding palindrome in the second list
	for (i = n/2; i < n; ++i)
    {
    	for (j = i+1; j < n; ++j)
    	{
    		int isPalindrome = 1;
    		int x=i,y=j;
    		while(x<=j && y>=i){
    			if (firstLetter[x] != firstLetter[y])
    			{
    				isPalindrome=0;
    			}
    			x++;
    			y--;
    		}
    		if (isPalindrome)
    		{
    			x=i;
    			printf("This is a palindrome:");
    			while(x<=j){
    				printf(" %c",firstLetter[x]);
    				x++;
    			}
    			printf("\n");
    		}
    	}
    }
   
	return 0;
}