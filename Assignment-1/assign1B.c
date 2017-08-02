/*
    Name-Saurav Roll-1601CS41
    The aim of this program is to find out the maximum sum of the subarray whose elements are not adjacent in the original array.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int n,i;

//Helper function to return the maximum of the two values
int max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

//Helper function to return the largest digit in a number
int LargeDigit(int x){
    
    //if it has a single digit only
    if(x/10==0){
        return x;
    }
    
    return max(x%10,LargeDigit(x/10));
}

//Function to calculate the answer to the problem.
void findMax(int boxes[],int *inclusive, int *exclusive){
    for (i = 1; i < n; ++i)
    {
    	int old = *inclusive;
    	*inclusive = max(*inclusive,*exclusive+boxes[i]);
    	*exclusive = old;
    }
}

int main(){
    
	//Input.
    printf("Enter the number of boxes: ");
    scanf("%d",&n);
    
    int boxes[n];
    printf("Enter the boxes: ");
    for(i=0;i<n;i++){
        int temp;
        scanf("%d",&boxes[i]);
    }
    
    //inclusive will contain the value of sum including the current number and excluding would contain the value of the sum excluding the current number.
    int ans,inclusive,exclusive=0;
    inclusive=boxes[0];   
    findMax(boxes,&inclusive,&exclusive);
    
    ans = max(inclusive,exclusive);

    //printing the results.
    printf("The maximum number of chocolates that can be taken: %d\n",ans);
    printf("The largest digit in the answer : %d\n",LargeDigit(ans));
    
    return 0;
}
