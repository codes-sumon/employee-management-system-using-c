#include <stdio.h>    ///for input output functions like printf, scanf
#include <stdlib.h>
#include <conio.h>
#include <string.h>  ///string operations


int main()
{
    FILE *fp, *ft;
    char another, choice;

    struct emp
    {
        int  age;
        char name[40], id[4];
        float bs;
    };

    struct emp e;           /// structure variable creation
    char empid[40];       /// string to store name of the employee
    long int recsize;       /// size of each record of employee


    fp = fopen("EMP.txt","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.txt","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }

    /// size of each record i.e. size of structure variable e
    recsize = sizeof(e);

    while(1)
    {
          system("cls");                     ///clear the console window
        printf("\n                 Bangladesh University of Business and Technology \n");
        printf("                          Creator ID 008, 009, 028, 031 \n\n\n");
        printf("                                1. Add Record \n");
        printf("                                2. List Records \n");
        printf("                                3. Modify Records \n");
        printf("                                4. Delete Records \n");
        printf("                                5. Exit \n\n");
        printf("                                Your Choice: ");
        fflush(stdin);                  /// flush the input buffer
        choice  = getche();             /// get the input from keyboard

        switch(choice)
        {
        case '1':
            system("cls");
            fseek(fp,0,SEEK_END);             /// search the file and move cursor to end of the file
                                              /// here 0 indicates moving 0 distance from the end of the file

            another = 'y';
            while(another == 'y')             /// if user want to add another record
            {
                printf("\n  Enter ID: ");
                scanf("%s", &e.id);
                printf("\n  Enter name: ");
                fscanf(stdin,"%s",&e.name);
                printf("\n  Enter age: ");
                scanf("%d", &e.age);
                printf("\n  Enter basic salary: ");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp);                    /// write the record in the file

                printf("\n  Add another record(y/n) ");
                fflush(stdin);
                another = getche();
                printf("\n\n");
            }
            break;


        case '2':
            system("cls");
            rewind(fp);                                         ///this moves file cursor to start of the file

                printf("    ID    Name      AGE      BASIC\n");
            while(fread(&e,recsize,1,fp)==1)                    /// read the file and fetch the record one record per fetch
            {
                printf("\n   %s    %s      %d      %.2f",e.id, e.name, e.age, e.bs); /// print the name, age and basic salary
            }
            getch();
            break;

        case '3':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("  Enter the employe ID to modify: ");
                scanf("%s", empid);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)                                            /// fetch all record from file
                {
                    if(strcmp(e.id,empid) == 0)                                             ///if entered name matches with that in file
                    {
                        printf("\n  Enter new ID: ");
                        scanf("%s",&e.id);
                        printf("\n  Enter new Name: ");
                        scanf("%s",&e.name);
                        printf("\n  Enter new AGE: ");
                        scanf("%d",&e.age);
                        printf("\n  Enter new BS: ");
                        scanf("%f",&e.bs);
                        fseek(fp,-recsize,SEEK_CUR);                                          /// move the cursor 1 step back from current position
                        fwrite(&e,recsize,1,fp);                                               /// override the record
                        break;
                    }
                }
                printf("\n  Modify another record(y/n)");
                fflush(stdin);
                another = getche();
                printf("\n\n");
            }
            break;

            case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\n  Enter ID of employee to delete: ");
                scanf("%s",empid);
                ft = fopen("Temp.txt","wb");                                            /// create a intermediate file for temporary storage
                rewind(fp);                                                             /// move record to starting of file
                while(fread(&e,recsize,1,fp) == 1)                                      /// read all records from file
                {
                    if(strcmp(e.id,empid) != 0)                                         /// if the entered record match
                    {
                        fwrite(&e,recsize,1,ft);                                        /// move all records except the one that is to be deleted to temp file
                    }

                }
                fclose(fp);
                fclose(ft);
                remove("EMP.txt");                                                      /// remove the orginal file
                rename("Temp.txt","EMP.txt");                                           /// rename the temp file to original file name
                fp = fopen("EMP.txt", "rb+");
                printf("\n  Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;

        case '5':
            fclose(fp);                                                                 /// close the file
            exit(0);                                                                    /// exit from the program
        }
    }
}
