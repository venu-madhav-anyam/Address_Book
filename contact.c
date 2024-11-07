#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


//mobile num validate
int validate_num(char *num, const AddressBook *addressBook)
{
    int i,k=0;

    if(strlen(num)!=10)
    {
        printf("\nDigits of mobile number is insufficient\n");
        return 1;
    }

    for(i=0;num[i]!=0;i++)
    {
        if(isdigit(num[i])==0)
        {
            printf("\nEnter a valid mobile number (Numerical digits)\n");
            return 1;
        }
    }

    for(i=0;i<addressBook->contactCount;i++)
    {
        //if(i!=(n-1))
        {
            if(strcmp(addressBook->contacts[i].num,num)==0)
            {
                printf("\nEntered Mobile Number is already existed\n");
                return 1;
            }
        }
    }

    return 0;
}


//mail i'd validate
int validate_mail(char *mail)
{
    int flag=1;
    for(int i=0;mail[i]!=0;i++)
    {
        if((strchr(mail,'@'))!=0)
        {
            if((strstr(mail,".com"))!=NULL)
                flag=0;
        }
    }

    if(flag)
    {
        printf("\nEnter a valid mail i'd\n");
        return 1;
    }
    return 0;
}


//Creating contact
void createContact(AddressBook *addressBook)
{
    int rep=0;

	printf("Enter Name :");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);

    enter:
    printf("Enter Mobile Number :");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].num);

    {
        int val=validate_num(addressBook->contacts[addressBook->contactCount].num, addressBook);

        if(val)
        {
            if(rep++<1)
                goto enter;
            else
                return;
        }
    }

    rep=0;

    validate:
    printf("Enter Mail I'D :");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].mail);

    {
        int val=validate_mail(addressBook->contacts[addressBook->contactCount].mail);

        if(val)
        {
            if(rep++<1)
                goto validate;
            else
                return;
        }
            
    }
    addressBook->contactCount++;
    printf("\nContact created successfully\n");
    
}

//Display contacts
void listContacts(AddressBook *addressBook) 
{
    //loadContactsFromFile(addressBook);

    printf("\n%20s\n","-CONTACTS-");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("\n%d)",i+1);
        printf("->Name : %s\n",addressBook->contacts[i].name);
        printf("  ->Mobile No : %s\n",addressBook->contacts[i].num);
        printf("  ->Mail I'D : %s\n",addressBook->contacts[i].mail);
    }
}

//Initializing dummy contacts
void initialize(AddressBook *addressBook) {
    //addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    
    loadContactsFromFile(addressBook);
}


char search[100];
//Searching contacts
int searchContact(AddressBook *addressBook) 
{
    int choice=0,flag=1;
    char elem[10];

    for(int i=0;search[i]!='\0';i++)
        search[i]=0;

    repeat3:
    printf("\n1. search By Name\n");
    printf("2. search By Mobile number\n");
    printf("3. search By Mail I'D\n");
    printf("4. Exit\n");
    printf("Enter your choice :");
    scanf("%d",&choice);
    getchar();

    switch(choice)
    {
        case 1:
            printf("Enter the Name :");
            scanf(" %[^\n]",elem);

            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].name,elem)!=NULL)
                {
                    printf("\n%d)",i+1);
                    printf("->Name : %s\n",addressBook->contacts[i].name);
                    printf("  ->Mobile No : %s\n",addressBook->contacts[i].num);
                    printf("  ->Mail I'D : %s\n",addressBook->contacts[i].mail);
                    flag=0;
                    search[i]=1;
                }
            }

            if(flag){
                printf("\nContact Not Found\n");
                return 0; }
            return 1;
        break;

        case 2:
            printf("Enter the Mobile Number :");
            scanf(" %[^\n]",elem);

            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].num,elem)!=NULL)
                {
                    printf("\n%d)",i+1);
                    printf("->Name : %s\n",addressBook->contacts[i].name);
                    printf("  ->Mobile No : %s\n",addressBook->contacts[i].num);
                    printf("  ->Mail I'D : %s\n",addressBook->contacts[i].mail);
                    flag=0;
                    search[i]=1;
                }
            }
            if(flag){
                printf("\nContact Not Found\n");
                return 0; }
            return 1;
        break;

        case 3:
            printf("Enter the Mail I'D :");
            scanf(" %[^\n]",elem);

            for(int i=0;i<addressBook->contactCount;i++)
            {    
                if(strstr(addressBook->contacts[i].mail,elem)!=NULL)
                {
                    printf("\n%d)",i+1);
                    printf("->Name : %s\n",addressBook->contacts[i].name);
                    printf("  ->Mobile No : %s\n",addressBook->contacts[i].num);
                    printf("  ->Mail I'D : %s\n",addressBook->contacts[i].mail);
                    flag=0;
                    search[i]=1;
                }
            }

            if(flag)
            {
                printf("\nContact Not Found\n");
                return 0; 
            }
            return 1;
            break;

        case 4:
            return 0;
            break;

        default:
            printf("\nInvalid choice please try again\n");
            goto repeat3;
    }
}


//Editing the contact
void editContact(AddressBook *addressBook)
{
    int n=0,m,flag=1,rep=0;
    char no[15];

    if(searchContact(addressBook))
    {
        printf("Enter the index number of contact to be edited :");
        scanf("%d",&n);
        getchar();

            if(search[n-1]==1)
            {

                printf("1. Edit Name\n2. Edit Mobile Number\n3. Edit Mail i'd\n4. Exit\nEnter your choice :");
                scanf("%d",&m);
                getchar();

                switch (m)
                {
                    case 1 :
                        printf("Enter Name :");
                        scanf(" %[^\n]",addressBook->contacts[n-1].name);

                        printf("\nContact's Name Edited Successfully\n");
                        flag=0;
                        break;

                    case 2 :
                        repeat:
                        printf("Enter Mobile Number :");
                        scanf(" %[^\n]",no);

                        {
                            int val=validate_num(no, addressBook);

                            if(val)
                            {
                                if(rep++<1)
                                    goto repeat;
                                else
                                    return;
                            }
                            else
                            {
                                for(int i=0;no[i]!='\0';i++)
                                    addressBook->contacts[n-1].num[i]=no[i];
                            }

                            printf("\nContact's Mobile Number Edited Successfully\n");
                        flag=0;

                        }
                        break;

                    case 3:
                        repeat1:
                        printf("Enter Mail I'D :");
                        scanf(" %[^\n]",no);

                        {
                            int val=validate_mail(no);

                            if(val)
                            {
                                if(rep++<1)
                                    goto repeat1;
                                else
                                    return;
                            }
                            else
                            {
                                for(int i=0;no[i]!='\0';i++)
                                    addressBook->contacts[n-1].mail[i]=no[i];
                            }
                        }
                        printf("\nContact's Mail i'd Edited Successfully\n");
                        flag=0;

                    case 4:
                        return;
                        break;
                    
                    default:
                        printf("\nEnter a valid choice\n");
                        break;
                    }
                
            }

        for(int i=0;search[i]!='\0';i++)
        search[i]=0;

        if(flag)
            printf("\nEnter a valid index number\n");
    }
}


//Deleting contact
void deleteContact(AddressBook *addressBook)
{
	int n=0,flag=1;

    if(searchContact(addressBook))
    {
        repeat2:
        printf("Enter the index number of contact to be deleted :");
        scanf("%d",&n);
        getchar();

            if(search[n-1]==1)
            {
                for(int i=(n-1);i<=addressBook->contactCount;i++)
                    addressBook->contacts[i]=addressBook->contacts[i+1];

                addressBook->contactCount--;

                printf("\nContact Deleted Successfully\n");
                flag=0;
            }

        for(int i=0;search[i]!='\0';i++)
                search[i]=0;

        if(flag)
        {
            printf("\nEnter a valid index number\n");
            goto repeat2;
        }
    }
}


void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}