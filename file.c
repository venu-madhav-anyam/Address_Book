#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
  FILE *file = fopen("contacts.csv", "w");

  if(file==NULL)
  {
    printf("\nError while opening file\n");
    return;
  }
    
    fprintf(file, "#%d#\n",addressBook->contactCount);

    for (int i=0;i<addressBook->contactCount;i++)
        fprintf(file, "%s,%s,%s\n", addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].mail);
    
    fclose(file);

    printf("\nContacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *file = fopen("contacts.csv", "r"); 

    if(file==NULL)
  {
    printf("\nError while opening file\n");
    return;
  }
    
    fscanf(file,"%*[^\n]");

    addressBook->contactCount = 0;

    while (addressBook->contactCount < MAX_CONTACTS && !(feof(file)))
    {
        fscanf(file, " %[^,]", addressBook->contacts[addressBook->contactCount].name);
        fgetc(file);
        fscanf(file, " %[^,]", addressBook->contacts[addressBook->contactCount].num);
        fgetc(file);
        fscanf(file, " %[^\n]", addressBook->contacts[addressBook->contactCount].mail);
        addressBook->contactCount++;
    }

    addressBook->contactCount--;

    fclose(file);

    printf("\nContacts loaded successfully\n");
}




