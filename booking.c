#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct moviedetails
{      char code[10];
       char name[50];
       char date[10];
       int rate;
}movie;

struct booking
{   char code1[10];
    char mov_name[50];
    char date1[10];
    int rate1;
    char name1[50];
    char mobile[20];
    int total_seats;
    int total_cost;
}book;

struct logincredentials
{      char username[10];
       char password[10];
}userlogin;

void old_records();
void book_ticket();
void find_movies();
void view_movies();
void insert_movies();
void signup();
int signin();

void old_records()
{   printf("\t\tPREVIOUS TRANSACTIONS\n");
    FILE *fptr;
    if ((fptr=fopen("transaction.txt","r"))==NULL)
    {   printf("Error opening file");
        exit(1);
    }
    while (!feof(fptr))
    {   fread(&book,sizeof(struct booking),1,fptr);
        printf("\nName: ");puts(book.name1);
        printf("\nMobile: ");puts(book.mobile);
        printf("\nMovie Code: ");puts(book.code1);
        printf("\nMovie Name: ");puts(book.mov_name);
        printf("\nMovie Date: ");puts(book.date1);
        printf("\nMovie Ticket rate: %d",book.rate1);
        printf("\nNo. of tickets: %d",book.total_seats);
        printf("\nTotal cost: %d",book.total_cost);
        printf("\n +++++++++++++++++++++++++++++++++++++++++++++++\n");
    }
    printf("\n\tPress any key to continue...");
    getch();
    system("cls");
}
void book_ticket()
{   printf("\t\tBOOKING\n");
    int a=0;
    char selectcode[10];
    FILE *checkptr;
    FILE *moviedisp;
    FILE *writeptr;
    if ((checkptr=fopen("movies.txt","r"))==NULL)
    {   printf("Error opening file");
        exit(1);
    }
    if ((moviedisp=fopen("movies.txt","r"))==NULL)
    {   printf("Error opening file");
        exit(1);
    }
    printf("\t MOVIE CODE\t MOVIE NAME\t\t DATE\t TICKET PRICE\n");
     while (!feof(moviedisp))
    {     fread(&movie,sizeof(movie),1,moviedisp);
          printf("\t %s\t\t %s\t\t %s\t %d\n",movie.code,movie.name,movie.date,movie.rate);
    }
    fclose(moviedisp);
    printf("\tEnter the movie code: ");
    scanf("%s",selectcode);
    while (!feof(checkptr))
    {   fread(&movie,sizeof(movie),1,checkptr);
        if (strcmp(selectcode,movie.code)==0)
        {   a=0;
            fclose(checkptr);
            break;
        }
        else
            a=1;
    }
    fclose(checkptr);
    if (a==1)
        printf("\n\tMovie not found!");
    else if (a==0)
    {   printf("\n\tFill in your details:");
        printf("\n\tEnter your name: ");fflush(stdin);
        gets(book.name1);
        printf("\n\tEnter your mobile number: ");fflush(stdin);
        scanf("%s",book.mobile);
        printf("\n\tEnter number of tickets: ");
        scanf("%d",&book.total_seats);
        book.total_cost=book.total_seats*movie.rate;
        printf("\n\tTotal cost: %d",book.total_cost);
        if ((writeptr=fopen("transaction.txt","a"))==NULL)
        {   printf("\n\tError opening file");
            exit(1);
        }
        strcpy(book.code1,movie.code);
        strcpy(book.mov_name,movie.name);
        strcpy(book.date1,movie.date);
        book.rate1=movie.rate;
        fwrite(&book,sizeof(struct booking), 1, writeptr);
        fclose(writeptr);
        printf("\n\t\tTicket booked successfully!!!");
    }
    printf("\n\tPress any key to continue...");
    getch();
    system("cls");
}

void find_movies()
{   printf("\t\tMOVIE SEARCH\n");
    int a=0;
    char search[10];
    FILE *findptr;
    if ((findptr=fopen("movies.txt","r"))==NULL)
    {  printf("Error opening file");
       exit(1);
    }
    printf("\tEnter the movie code: ");
    scanf("%s",search);
    while (!feof(findptr))
    {   fread(&movie,sizeof(movie),1,findptr);
        if (strcmp(search,movie.code)==0)
        {   printf("\t\t\tMOVIE FOUND\n");
            printf("\t\tMovie code: ");
            puts(movie.code);
            printf("\n\t\tMovie name: ");
            puts(movie.name);
            printf("\n\t\tDate of release: ");
            puts(movie.date);
            printf("\n\t\tTicket rate: %d",movie.rate);
            fclose(findptr);
            a=1;
            break;
        }
    }
    fclose(findptr);
    if (a==0)
        printf("\t\tMovie not found");
    printf("\n\t\tPress any key to continue...");
    getch();
    system("cls");
}

void view_movies()
{   printf("\t\tVIEW ALL MOVIES\n");
    FILE *moviedisp;
     if ((moviedisp=fopen("movies.txt","r"))==NULL)
     {  printf("Error opening file");
        exit(1);
     }
     printf("\t MOVIE CODE\t MOVIE NAME\t\t DATE\t TICKET PRICE\n");
     while (!feof(moviedisp))
    {     fread(&movie,sizeof(movie),1,moviedisp);
          printf("\t %s\t\t %s\t\t %s\t %d\n",movie.code,movie.name,movie.date,movie.rate);
    }
    fclose(moviedisp);
    printf("\n\tPress any key to continue");
    getch();
    system("cls");
}



void insert_movies()
{    FILE *moviein;
     if ((moviein=fopen("movies.txt","a"))==NULL)
     {  printf("Error opening file");
        exit(1);
     }
     printf("\t\tINSERT MOVIE \n");
     printf("\tEnter movie code: ");
     scanf("%s",movie.code); fflush(stdin);
     printf("\n\tEnter movie name: ");
     gets(movie.name);
     printf("\n\tEnter date of showing: ");
     scanf("%s",movie.date);
     printf("\n\tEnter the price of ticket: ");
     scanf("%d",&movie.rate);
     fwrite(&movie,sizeof(struct moviedetails), 1, moviein);
     fclose(moviein);
     printf("\n\tMovie Successfully added");
     getch();
     system("cls");
}

void signup()
{   system("cls");
    struct logincredentials user;
    char check[10];
    int a=0;
    FILE *fptr1;
    if ((fptr1=fopen("users.txt","a"))==NULL)
    {  printf("Error opening file");
       exit(1);
    }
    printf("\tSIGN UP \n");
    printf("\t**The username and password must not have more than 10 characters**");
    while (a==0)
    { printf("\n\tEnter username: ");
      scanf("%s",user.username);
      printf("\n\tEnter password: ");
      scanf("%s",user.password);
      printf("\n\tConfirm password: ");
      scanf("%s",check);
      if (strcmp(user.password,check)==0)
      {  a=1;}
      else
      {   system("cls");
          printf("\tPassword did not match. Re-enter again");}
    }
    fwrite(&user,sizeof(struct logincredentials), 1, fptr1);
    printf("\tAccount created successfully!!");
    printf("\n\tYour username is: "); puts(user.username);
    printf("\n\tYour password is: "); puts(user.password);
    getch();
    fclose(fptr1);
}

int signin()
{   system("cls");
    char username[10];
    char password[10];
    FILE *fptr2;
    if ((fptr2=fopen("users.txt","r"))==NULL)
    {  printf("Error opening file");
       exit(1);
    }
    printf("\tUSER SIGNIN");
    printf("\n\tEnter username: ");
    scanf("%s",username);
    printf("\n\tEnter password: ");
    scanf("%s",password);
    while (!feof(fptr2))
    {     fread(&userlogin,sizeof(userlogin),1,fptr2);
          if ((strcmp(userlogin.username,username)==0) && (strcmp(userlogin.password,password)==0))
          {  fclose(fptr2);
             return 1;
          }
    }
    fclose(fptr2);
    return 0;
}




int main()
{   int success;
    int choice, ch;
    here:
    printf("***************************BOOK MOVIE TICKET ONLINE***************************\n");
    printf("1. Sign UP \n2. Sign IN \nEnter your choice(1/2) ");
    scanf("%d", &choice);
    if (choice==1)
    {   signup();
    }
    else if (choice==2)
    {   success=signin();
        if (success==0)
        {  printf("\tUser not found.");
           getch();
           system("cls");
           goto here;
        }
        if (success==1)
        {  printf("\tLogin Successfull!");
           printf("\n\tPress any key to continue");
           getch();
        }
    }
    system("cls");
    while (1)
    {     printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		printf("\n\t\t\t Book Movie Ticket \n");
		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		printf("\n\tEnter >1< To Insert A Movie\n\tEnter >2< To View All Movies\n\tEnter >3< To Find A Movie\n\tEnter >4< To Book A Ticket(s)\n\tEnter >5< To View All Recent Transactions\n\tEnter >0< To Exit \n\tEnter your Choice :");
	   	scanf("%d",&ch);
	   	system("cls");
          switch (ch){
	    		case 1: insert_movies();
	   			break;
			case 2: view_movies();
	   			break;
			case 3: find_movies();
	   			break;
			case 4: book_ticket();
				break;
			case 5: old_records();
				break;
            case 0: exit(0);
	    		default: printf("Enter a valid option.");
                     }

    }
    getch();
    return 0;
}
