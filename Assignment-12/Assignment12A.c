/*
  Name - Saurav Roll-1601CS41
  The aim of this program is to implement bi-partite matching to match jobs with applicants.
*/
#include<stdio.h>
#include<string.h>

//hardcoded names of companies.
char companies[19][50] = {
  "Microsoft\0","Google\0","Adobe\0","Mentor Graphics\0","Synopsis\0","IBM\0","Wipro\0","TCS\0","CTS\0","Goldman\0","Infosys\0","Cadence\0","Texas Instrument\0","DRDO\0","HAL\0","ISRO\0","Capgemini\0","Ushacomm\0","Ericson\0"
};

//global variables.
char candidates[40][40];
int numberCandidates = 0,numberCompanies = 19;

//implementation of bipartite matching.
int bpm(int graph[40][20],int u,int seen[], int match[]){
  int i;
  
  //try each and every company for availability.
  for(i=0;i<numberCompanies;i++){
    if(graph[u][i] && !seen[i]){
      seen[i] = 1;
      
      if(match[i]<0 || bpm(graph,match[i],seen,match)){
        match[i] = u;
        return 1;
      }
    }    
  }
  return 0;
}

//helper function to call bpm.
void findMaxBPM(int graph[40][20]){

  //stores the final result.
  int match[numberCompanies];
  int i;
  
  //initialising everything as -1;
  for(i=0;i<numberCompanies;i++){
    match[i] = -1;
  }
  
  //calling bpm on each candidate.
  for(i = 0;i<numberCandidates;i++){
    int used[19] = {0};
    bpm(graph,i,used,match);
  }
  
  //printing the final results.
  int flag = 0;
  for(i=0;i<numberCompanies;i++){
    if(match[i] != -1){
      
      if(!flag){
        printf("Candidates offered a job by the companies are: ");
      }    
      
      flag = 1;
      printf("%s -> %s\n",companies[i],candidates[match[i]]);
    }
  }
  
  if(!flag){
    printf("None of the candidates were offered a job.");
  }
}

//helper function to return the min of two numbers.
int min(int a,int b){
  return (a>b)?b:a;
}

//checks whether we have an edge between two strings.
int check(int candid,int comp){
  int countera[26]={0},counterb[26]={0};
  
  int i;
  for(i=0;i<strlen(candidates[candid]);i++){
    if(candidates[candid][i]>='a' && candidates[candid][i]<='z'){
      countera[candidates[candid][i]-'a']++;
    }else if(candidates[candid][i]>='A' && candidates[candid][i]<='Z'){
      countera[candidates[candid][i]-'A']++;
    }
  }
  
  for(i=0;i<strlen(companies[comp]);i++){
    if(companies[comp][i]>='a' && companies[comp][i]<='z'){
      counterb[companies[comp][i]-'a']++;
    }else if(companies[comp][i]>='A' && companies[comp][i]<='Z'){
      counterb[companies[comp][i]-'A']++;
    }
  }
  
  int common = 0;
  //counting the number of common characters.
  for(i=0;i<26;i++){
    common += min(countera[i],counterb[i]);
    //if(countera[i] && counterb[i]){
      //common++;
    //}
  }
  
  return common>=2;
}

int main(){
  
  //getting input.
  printf("Enter the number of candidates: ");
  scanf("%d",&numberCandidates);
  
  printf("Enter the name of candidates one by one: ");
  int i;
  
  for(i=0;i<numberCandidates;i++){
    scanf("%s",&candidates[i]);
  }
  
  int graph[40][20];    
  
  //building the graph.
  for(i=0;i<numberCandidates;i++){
    int j;
    for(j=0;j<numberCompanies;j++){
      //checking for edge.
      if(check(i,j)){
        graph[i][j] = 1;
      }else{
        graph[i][j] = 0;
      }
    }
  }
  //calling the algorithm.
  findMaxBPM(graph);
  
  return 0;
}
