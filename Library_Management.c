#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void addBook();
void booksList();
void del();
void issueBook();
void issueList();

struct books{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
}b;

struct student{
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
}s;

FILE *fp;

int main(){

    int ch;

    while(1){
        system("cls");
        printf("                     ==================================================================\n");
        printf("                     ||     Daffodil International University Library Management     ||\n");
        printf("                     ==================================================================\n");
        printf("                                           1.Add Book\n");
        printf("                                           2.Books List\n");
        printf("                                           3.Remove Book\n");
        printf("                                           4.Issue Book\n");
        printf("                                           5.Issued Book List\n");
        printf("                                           0.Exit\n\n");
        printf("                     =================================================================\n");
        printf("                                           Enter your choice: ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            booksList();
            break;

        case 3:
            del();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            issueList();
            break;

        default:
            printf("                         Invalid Choice...\n\n");

        }
        printf("                             Press Any Key To Continue...");
        getch();
    }

    return 0;
}


void addBook(){
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate,                 "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("                                           Enter Book id: ");
    scanf("%d", &b.id);

    printf("                                           Enter Book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("                                           Enter Author name: ");
    fflush(stdin);
    gets(b.authorName);
    printf("                              ================================================\n");
    printf("                                    Book Added Successfully In your library\n");
    printf("                              ================================================= \n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}


void booksList(){

    system("cls");
    printf("                 ==================================================================\n");
        printf("                 ||                       Available Books                        ||\n");
        printf("                 ==================================================================\n");
    printf("                 %-10s %-30s %-20s %s\n\n", "Book id",  "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("                  %-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
        printf("           =====================================================================\n  ");
    }

    fclose(fp);
}

void del(){
    int id, f=0;
    system("cls");
    printf("                 ==================================================================\n");
        printf("                 ||                         Remove Books                         ||\n");
        printf("                 ==================================================================\n");
    printf("                                       Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(id == b.id){
            f=1;
        }else{
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if(f==1){
        printf("\n\n                 Deleted Successfully.\n");
    }else{
        printf("\n\n                 Record Not Found !\n");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");

}


void issueBook(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate,                  "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f=0;

    system("cls");
     printf("                 ==================================================================\n");
        printf("                 ||                         Books Issue                          ||\n");
        printf("                 ==================================================================\n");

    printf("                                         Enter Book id to issue: ");
    scanf("%d", &s.id);


    fp = fopen("books.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.id == s.id){
            strcpy(s.bookName, b.bookName);
            f=1;
            break;
        }
    }

    if(f==0){
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList(){
    system("cls");
     printf("                     ==================================================================\n");
        printf("                     ||                        Books Issue List                      ||\n");
        printf("                     ==================================================================\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "Id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1){
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}
