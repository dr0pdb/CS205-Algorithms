/*
	Name-Saurav Roll-1601CS41
	The aim of this program is to build a small library system.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct 
{
	//issueStatus-0 if unissued and 1 if issued.
	int serial,issueStatus;
	char title[50];
	char author[50];
} Book;

int nbooks=0,i;
Book books[1000];

//Helper function to print the details of a single book
int bookFound=0;
void printBook(int serialn){
	bookFound=0;
	for (i = 0; i < nbooks; ++i)
	{
		Book curr = books[i];
		if (curr.serial == serialn)
		{
			printf("Title - %s\n", curr.title);
			printf("Author - %s\n", curr.author);
			printf("Serial - %d\n\n", curr.serial);
			bookFound=1;
			return;
		}
	}
}

//Helper function to check whether the serial number has already been taken
int checkSerial(int serialn){
	for (i = 0; i < nbooks; ++i)
	{
		Book curr = books[i];
		if (curr.serial == serialn)
		{
			return 0;
		}
	}
	return 1;
}

//Helper function to create a book.
void createBook(){
	//getting the input about the book
	printf("Enter the Serial number: ");
	int serialn;
	scanf("%d",&serialn);
	int res = checkSerial(serialn);
	if (!res)
	{
		printf("This serial has already been taken");
		return;
	}
	books[nbooks].serial=serialn;
	printf("Enter the title of the Book: ");
	fgets(books[nbooks].title, 50, stdin);
	books[nbooks].title[strlen(books[nbooks].title)-1] = '\0';
	printf("Enter the Author name: ");
	scanf("%63[^\n]s",books[nbooks].author);
	books[nbooks].issueStatus=0;
	
	nbooks++;
	printf("New entry successful\n");
}

//Helper function to print the options
void printOptions(){
	printf("a. Make a new entry of book\n");
	printf("b. view Details of a book\n");
	printf("c. Show list of available books\n");
	printf("d. Issue a book\n");
	printf("e. Return a book\n");
	printf("f. exit\n");
}

//To show the details of a book by its serial number
void showBookBySerial(){
	printf("Enter the serial number of the book:");
	int serialn;
	scanf("%d",&serialn);

	printBook(serialn);
	//in case if book is not found
	if (!bookFound)
	{
		printf("Couldn't find the book, Check the serial number!\n\n");
	}
}

//To show the details of a book by its title
void showBookByTitle(){
	printf("Enter the title of the book:");
	char titlen[50];
	fgets(titlen, 50, stdin);
	titlen[strlen(titlen)-1] = '\0';

	bookFound=0;
	for (i = 0; i < nbooks; ++i)
	{
		Book curr = books[i];
		if (strcmp(curr.title, titlen)==0)
		{
			bookFound=1;
			printBook(curr.serial);
			return;
		}
	}
	//in case if book is not found
	if (!bookFound)
	{
		printf("No book found by this title\n");
	}
}

//To show the details of a book by its author
void showBookByAuthor(){
	printf("Enter the author name:");
	char authorName[50];
	fgets(authorName, 50, stdin);
	authorName[strlen(authorName)-1] = '\0';

	bookFound=0;
	for (i = 0; i < nbooks; ++i)
	{
		Book curr = books[i];
		if (strcmp(curr.author, authorName)==0)
		{
			bookFound=1;
			printBook(curr.serial);
		}
	}

	//in case if book is not found
	if (!bookFound)
	{
		printf("No book found by this author\n");
	}
}

//Function to show the requested book
void showBooks(){
	printf("View details of a book(Enter the character): \n");
	printf("a. By Serial No.\n");
	printf("b. By title\n");
	printf("c. By Author\n");

	char option,x;
	scanf(" %c%c",&option,&x);

	//Depending on the option we choose function
	switch(option){
		case 'a':
			//By serial
			showBookBySerial();
			break;
		case 'b':
			//By title
			showBookByTitle();
			break;
		case 'c':
			//By author
			showBookByAuthor();
			break;
		default:
			printf("Select one of the given options\n\n");
	}
			
}

//Function to show the list of available books
void showAvailableBooks(){
	bookFound=0;
	for (i = 0; i < nbooks; ++i)
	{
		Book curr = books[i];
		if (curr.issueStatus == 0)
		{
			if (!bookFound)
			{
				printf("Here are the list of available books:\n");
				bookFound=1;
			}			
			printBook(curr.serial);
		}
	}
	//in case if book is not found
	if (!bookFound)
	{
		printf("No available books right now\n\n");
	}
}

//Function to issue a book
void issueBook(){
	//printing the list of available books 
	showAvailableBooks();
	if (bookFound)
	{
		int serialn;
		printf("Enter the serial number of book to be issued: ");
		scanf("%d",&serialn);
		for (i = 0; i < nbooks; ++i)
		{
			Book curr = books[i];
			if (curr.serial == serialn && curr.issueStatus==0)
			{
				books[i].issueStatus = 1;
				break;
			}else if(curr.serial == serialn && curr.issueStatus==1){
				printf("Book is already issued\n\n");
				return;
			}
		}
		printf("Issuing successful\n\n");

	}else{
		return;
	}
}

//Helper function to return a book
void returnBook(){
	int serialn;
	printf("Enter the serial number of book to be returned: ");
	scanf("%d",&serialn);

	for (i = 0; i < nbooks; ++i)
	{
		Book curr = books[i];
		if (curr.issueStatus==1 && curr.serial == serialn)
		{
			books[i].issueStatus=0;
			printf("Successfully returned\n\n");
			return;
		}else if (curr.issueStatus==0 && curr.serial == serialn)
		{
			printf("You haven't issued this book\n\n");
			return;
		}
	}
	printf("Wrong serial number\n\n");
}

int main()
{
	//x will accomodate the newline character
	char option,x;
	int toContinue=1;
	printf("Choose one of these options-Input lowercase letter\n");
	while(toContinue){
		printOptions();
		scanf(" %c%c",&option,&x);

		//Depending on the option we choose function
		switch(option){
			case 'a':
				//create a new entry
				createBook();
				break;
			case 'b':
				//view details of a book
				showBooks();
				break;
			case 'c':
				//show list of available books
				showAvailableBooks();
				break;
			case 'd':
				//issue a book
				issueBook();
				break;
			case 'e':
				//return a book
				returnBook();
				break;
			case 'f':
				toContinue=0;
				break;
			default:
				printf("\nChoose only the available options!\n");

		}
	}
	return 0;
}