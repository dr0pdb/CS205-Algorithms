/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to return the final order in which a doctor would attend his patients.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	char name[50];
	int hour,minute,similarity;
	int elementCounter[26];
}patient;

//Global variables
int n,i;
char doctor[50];
int doctorElementCounter[26]={0};
patient *patients;

//function to calculate the frequency of each character for the doctor.
void calculateDoctorCounter(){
	int j;

	for(j=0;j<strlen(doctor);j++){
		char c = doctor[i];
		
		//upper case
		if(c>=65 && c<=90){
			doctorElementCounter[c-'A']++;
		}else if(c>=97 && c<=122){
			doctorElementCounter[c-'a']++;
		}
		
	}
}

//function to calculate the frequency of each character.
void calculateElementCounter(char str[],int len, int index){
	int j;
	patient current = *(patients+index);

	//initialising
	for (j=0;j<26;j++)
	{
		current.elementCounter[j]=0;
	}

	
	for(j=0;j<len;j++){
		char c = str[i];
		
		//upper case
		if(c>=65 && c<=90){
			current.elementCounter[c-'A']++;
		}else if(c>=97 && c<=122){
			current.elementCounter[c-'a']++;
		}
		
	}
}

//function to calculate the similarity among names
void calculateSimilarity(int index){

	patient current = *(patients+i);
	calculateElementCounter(current.name, strlen(current.name),index);

	int j;
	for (j = 0; j < 26; ++j)
	{
		if (current.elementCounter[j]>0 && doctorElementCounter[j]>0)
		{
			current.similarity++;
		}
	}

}

//function to swap two patients at the time of swapping.
void swap_patients(patient *a , patient *b){
	patient *c = (patient*) malloc(sizeof(patient));

	strcpy(c->name,a->name);
	c->similarity=a->similarity;
	c->hour = a->hour;
	c->minute = a->minute;

	strcpy(a->name,b->name);
	a->similarity=b->similarity;
	a->hour = b->hour;
	a->minute = b->minute;

	strcpy(b->name,c->name);
	b->similarity=c->similarity;
	b->hour = c->hour;
	b->minute = c->minute;

}

int main(){	
	
	//Getting the input
	printf("Enter the name of the doctor: ");
	fgets (doctor, 50, stdin);
	calculateDoctorCounter();

	printf("Enter the number of patients: ");
	scanf("%d",&n);
	printf("%d\n",n);

	patients = (patient*)malloc(n*sizeof(patient));

	printf("--------- Enter patient details ---------\n");
	for (i = 0; i < n; ++i)
	{	
		printf("---- Patient-%d ----\n",i+1);
		printf("Name: ");
		scanf (" %[^\n]%*c", (patients+i)->name);
		printf("Hour: ");
		scanf(" %d",&((patients+i)->hour));
		printf("Minute: ");
		scanf(" %d",&((patients+i)->minute));
		calculateSimilarity(i);
	}

	//sorting according to conditions.
	int j;
	for (i = 0; i < n; ++i)
	{
		for (j = i+1; j < n; ++j)
		{
			patient a,b;
			a = patients[i];
			b = patients[j];

			if (a.hour<=8)
			{
				//when both of them arrive before 8
				if (b.hour<=8)
				{
					if (a.similarity<b.similarity)
					{
						swap_patients(patients+i,patients+j);
					}
				}
				//when b arrives after 8 and a arrives before 8
				else{
					continue;
				}
			}else{
				//when a arrives after 8 and b arrives before 8
				if (b.hour<=8)
				{
					swap_patients(patients+i,patients+j);
				}
				//when both arrive after 8
				else{
					if (a.hour>b.hour || ((a.hour==b.hour) && a.minute>b.minute))
					{
						swap_patients(patients+i,patients+j);	
					}else if(a.hour == b.hour && a.minute == b.minute && a.similarity < b.similarity){
						swap_patients(patients+i,patients+j);
					}
				}
			}
		}
	}

	//printing the results.
	printf("--------- The final order of patients ---------\n");
	for (i = 0; i < n; ++i)
	{
		printf(" %s\n",patients[i].name);
	}
	return 0;
}
