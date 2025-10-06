#include <stdio.h>
#include "file.h"

// Save all contacts to contacts.csv file
void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv", "w"); // Open file for writing
    if (fptr == NULL)
    {
        printf("No contacts found\n");
        return; // Exit if file can't be opened
    }
    fprintf(fptr, "%d\n", addressBook->contactCount); // Save total number of contacts to file
    for(int i=0;i<addressBook->contactCount;i++) // Write contact in csv format
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr); // Close file
}

// Load contacts from csv file
void loadContactsFromFile(AddressBook *addressBook) {
    // Open file for reading
    FILE *lptr = fopen("contacts.csv", "r");
    if (lptr == NULL)
    {
        printf("No contacts found\n");
        return; // Exit if file don't exit
    }
    fscanf(lptr, "%d", &addressBook->contactCount); // Read total number of contacts
    for (int i=0; i<addressBook->contactCount; i++) // Read each contacts
    {
        fseek(lptr,1,SEEK_CUR);
        fscanf(lptr," %[^,]",addressBook->contacts[i].name);
        fseek(lptr,1,SEEK_CUR);
        fscanf(lptr," %[^,]",addressBook->contacts[i].phone);
        fseek(lptr,1,SEEK_CUR);
        fscanf(lptr,"%[^\n]",addressBook->contacts[i].email);
    }
    fclose(lptr); // Close file
}