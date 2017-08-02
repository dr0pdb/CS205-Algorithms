/*
    Name-Saurav Roll-1601CS41
    The aim of this program was to take n strings and construct a linked list using the abbreviations of those strings and present in a sorted order.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//Utility variables
int n,i,j,k;

typedef struct node{
    char sname[50];
    int len;
    struct node *next;    
} Student;

//variables for the linked list
Student *head=NULL,*prev=NULL,**studentsList;

//Helper function to print the linked list of students.
void printList(){
    Student *ptr=head;
    printf("Printing the students list:\n");
    while(ptr != NULL){
       for(i=0;i<ptr->len ;i++){
           printf("%c",ptr->sname[i]);
       }
       printf("  "); 
       ptr = ptr->next;       
    }
    printf("\n");
}

//Helper function to return the maximum of the two values
int max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

//Helper function to return the minimum of the two values
int min(int a, int b){
    if(a>b){
        return b;
    }
    return a;
}

int main(){

    printf("Enter the number of students: ");    
    scanf("%d",&n);
    
    char students[n][50];
     
    printf("Enter the name of students, one per line: ");
    for(i=0; i<n;i++){
        scanf("%s",&students[i]);
    }

    //sorting the array
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            //In this case we have to swap.
            if(strcmp(students[i],students[j])>0){
                char temp[50];
                strcpy(temp,students[j]);
                strcpy(students[j],students[i]);
                strcpy(students[i],temp);
            }
        }
    }
    
    //To store the max Size required for the abbreviations
    int maxSizeRequired[n];
    for(i=0;i<n;i++){
        maxSizeRequired[i]=-1;
    }
   

    //This will calculate for each name, the smallest length required to define it unambiguously.
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            int numberMatch=0;
            for(k=0; k<min(strlen(students[i]),strlen(students[j])) ; k++){
                if(students[i][k] == students[j][k]){
                    numberMatch++;
                }else{
                    numberMatch++;
                    maxSizeRequired[i]=max(numberMatch,maxSizeRequired[i]);
                    maxSizeRequired[j]=max(numberMatch,maxSizeRequired[j]);
                    break;
                }
            }
        }
    }
    
    
    
    //creating the linked list
    studentsList = (Student**) malloc(n*sizeof(Student*));
    for(i=0;i<n;i++){
        studentsList[i] = (Student*)malloc(sizeof(Student));
        Student *currStudent = studentsList[i];
        //saving the substring in the variable currName.
        char currName[50];
        strncpy(currName,students[i],maxSizeRequired[i]);
        currName[maxSizeRequired[i]]="\0";
        
        //linked list operations
        if(i==0){
            head = currStudent;
            prev = currStudent;
            strcpy(currStudent->sname,currName);
            currStudent->next = NULL;
            currStudent->len = maxSizeRequired[i];
        }else{
            prev->next = currStudent;
            prev = currStudent;
            strcpy(currStudent->sname,currName);
            currStudent->next = NULL;
            currStudent->len = maxSizeRequired[i];
        }
    }
    
    //printing the results.
    printList();
    printf("Here are the full names of the students:\n");
    for(i=0;i<n;i++){
        printf("%s  ",students[i]);
    }
}
