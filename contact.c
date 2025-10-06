#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

// Lists all contacts, sorting enabled if specified
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    int i,j;
    Contact temp; // temp -> variable for swapping
    if (sortCriteria == 1)
    {
        printf("\nContacts sorted by name:\n");  
        printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
        
        // Sorting logic w.r.t name
        for (i=0; i<(addressBook->contactCount)-1; i++)
        {
            for (j=0; j<(addressBook->contactCount)-1-i; j++)
            {
                if (strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
        }
        // Printing contacts
        for (i=0; i<addressBook->contactCount; i++)
        {
            printf("%-30s %-30s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (sortCriteria == 2)
    {
        printf("\nContacts sorted by phone:\n");
        printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
        // Sorting logic w.r.t phone
        for (i=0; i<(addressBook->contactCount) - 1; i++)
        {
            for (j=0; j<(addressBook->contactCount) -i-1; j++)
            {
                if (strcasecmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
        }
        // Printing contacts
        for (i=0; i<addressBook->contactCount; i++)
        {
            printf("%-30s %-30s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (sortCriteria == 3)
    {
        printf("\nContacts sorted by email:\n");
        printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
        // Sorting logic w.r.t email id
        for (i=0; i<(addressBook->contactCount) - 1; i++)
        {
            for (j=0; j<(addressBook->contactCount) -i-1; j++)
            {
                if (strcasecmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp; 

                }
            }
        }
        // Printing contacts
        for (i=0; i<addressBook->contactCount; i++)
        {
            printf("%-30s %-30s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
// For default order, display the contacts without sorting
    if (sortCriteria == 4)
    {
        printf("\nDefault sorting:\n");
        printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
        for (i=0; i<addressBook->contactCount; i++)
        {
            printf("%-30s %-30s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
}

/*
Load contacts from file into address book
Read existing contacts from file to address book
*/

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// Save contacts to file, then exit
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// Create a new contact
void createContact(AddressBook *addressBook)
{
  /* Define the logic to create a Contacts */
    printf("\n📝CREATE CONTACT\n-----------------\n");
    printf("Enter the details: \n");
    char name[50], phone[50], email[50];
    int choice; // choice -> to store value whether the user wants to add another contact (1: Yes, 2: No)
    while (choice!=2)
    {
        printf("Enter contact name : ");
        scanf(" %[^\n]", name);
        printf("Enter phone number : ");
        scanf(" %[^\n]", phone);
        printf("Enter email address: ");
        scanf(" %[^\n]", email);
        //validation logic for contact entered
        if (validate_name(name) && validate_phone(phone, addressBook) && validate_email(email, addressBook))
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            addressBook->contactCount++;
            // Prompt to continue with program
            printf("\nContact added successfully\n\n\nAdd another contact?\n---------------------------\n1. Yes\n2. No, back to main menu\n---------------------------\nEnter your choice: ");
            scanf(" %d", &choice);
        }
        else // End "createcontact" function is input is other than '1'
        {
            printf("Invalid data\n");
            return;
        }
    }
}

// Search contacts using name, phone, or email
int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf("\n🔍 SEARCH CONTACTS\n-------------------\n1. Name\n2. Phone\n3. Email\n4. Back to menu\nEnter your choice: ");
    int c; // c -> to store user's choice for search criteria (1: Name, 2: Phone, 3: Email, 4: Back)
    scanf("%d", &c);
    if (c == 1) // Logic for searching contact w.r.t name
    {
        printf("Enter the name to search: ");
        char name[50];
        scanf(" %[^\n]", name);
        int i;
        for (i=0; i<addressBook->contactCount; i++)
        {
            int ret = strcmp(addressBook->contacts[i].name, name);
            if (ret == 0)
            {
                printf("\nContact found at index: %d\n", i);
                printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
                printf("%-30s %-30s %-30s", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\n");
                return 1;
            }
        }
        printf("\nNo results found\nRedirecting to main menu...\n");

    }
    else if (c == 2) // Logic for searching contact w.r.t phone
    {
        printf("Enter the number to search: ");
        char phone[50];
        scanf(" %[^\n]", phone);
        int i;
        for (i=0; i<addressBook->contactCount; i++)
        {
            int ret = strcmp(addressBook->contacts[i].phone, phone);
            if (ret == 0)
            {
                printf("\nContact found at index: %d\n", i);
                printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
                printf("%-30s %-30s %-30s", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\n");
                return 1;
            }
        }
        printf("\nNo results found\nRedirecting to main menu...\n");
    }
    else if (c == 3) // Logic for searching contact w.r.t email id
    {
        printf("Enter the email id to search: ");
        char mail[50];
        scanf(" %[^\n]", mail);
        int i;
        for (i=0; i<addressBook->contactCount; i++)
        {
            int ret = strcmp(addressBook->contacts[i].email, mail);
            if (ret == 0)
            {
                printf("\nContact found at index: %d\n", i);
                printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
                printf("%-30s %-30s %-30s", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\n");
                return 1;
            }
        }
        printf("\nNo results found\nRedirecting to main menu...\n");
    }
    else if (c == 4) // Return to main menu
    {
        return 2;
    }
    return 0;
}

// Edit an existing contact
void editContact(AddressBook *addressBook)
{
     /* Define the logic for Editcontact */
    printf("\n✏️  EDIT CONTACT\n----------------\nFind the contact you wish to update\n");
    int ret, ind, var;
    /*
    ret -> to store return value from searchContact(addressBook) function
    ind -> to store the index value entered by the user
    var -> to store the user's choice to edit (1: Name, 2: Phone, 3: Email)
    */
    ret = searchContact(addressBook); // Search for the contact to edit
    if (ret == 0)
    {
        return; //return to main menu
    }
    else if (ret == 1)
    {
        printf("\nEnter the Index to edit: ");
        scanf("%d", &ind);
        printf("\nWhat would you like to edit:\n1. Name\n2. Phone\n3. Email\nEnter your choice: ");
        scanf("%d", &var);
        getchar(); // Remove new line from the buffer

        if (var == 1)
        {
            char ch1[30];
            int ret1;
            printf("Update Name to: ");
            scanf("%[^\n]", ch1);
            ret1 = validate_name(ch1);
            if (ret1 == 1)
            {
                strcpy(addressBook->contacts[ind].name, ch1);
                printf("Updated succesfully\n");
            }
            else
            {
                printf("Invalid name\n");
            }
        }
        else if (var == 2)
        {
            char ch2[30];
            int ret2;
            printf("Update Phone to: ");
            scanf("%[^\n]", ch2);
            ret2 = validate_phone(ch2, addressBook);
            if (ret2 == 1)
            {
                strcpy(addressBook->contacts[ind].phone, ch2);
                printf("Updated succesfully\n");
            }
            else
            {
                printf("Invalid phone number\n");
            }
        }
        else if (var == 3)
        {
            char ch3[30];
            int ret3;
            printf("Update Email to: ");
            scanf("%[^\n]", ch3);
            ret3 = validate_email(ch3, addressBook);
            if (ret3 == 1)
            {
                strcpy(addressBook->contacts[ind].email, ch3);
                printf("Updated succesfully\n");
            }
            else
            {
                printf("Invalid email id entered\n");
            }
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

// Delete an existing contact
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf("\n🗑️  DELETE CONTACT\n------------------\nFind the contact you wish to delete\n");
    int ret = searchContact(addressBook); // Search for contact to delete
    if (ret != 1)
    {
        return; // If contact not found, return to main menu
    }
    int ind; // ind -> to store index entered by user to delete
    printf("\nEnter index to delete: ");
    scanf("%d", &ind);
    int del;
    printf("\nAre you sure you want to move to trash?\n1. Yes\n2. No\nEnter your choice: ");
    scanf("%d", &del);
    if (del == 1)
    {
        for (int i=ind; i<addressBook->contactCount-1; i++)
        {
            strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
            strcpy(addressBook->contacts[i].phone, addressBook->contacts[i+1].phone);
            strcpy(addressBook->contacts[i].email, addressBook->contacts[i+1].email);
        }
        addressBook->contactCount--; // After ontact deletion, decrement contact count.
        printf("Contact deleted successfully\n");      
    }
    else
    {
        printf("Deletion cancelled\n");
    }
}

// Validate name (Should only contain letters and spaces)
int validate_name(char *name)
{
    int i=0;
    while (name[i])
    {
        // Only uppercase, lowercase and spaces are allowed
        if ((name[i] >=65 && name[i] <=90) || (name[i] >= 97 && name[i] <= 122) || (name[i] == ' '))
        {
            i++;
        }
        else // If invalid character found return 
        {
            return 0; 
        }
    }
    return 1;
    
}

// Validate phone number (Must be 10 digits and unique)
int validate_phone(char *Phone , AddressBook *addressBook)
{
    if((strlen(Phone)) == 10)
    {
        int i=0;
        while(Phone[i]) // Check all characters are digits or not
        {
            if(Phone[i] >= '0' && Phone[i] <= '9')
            {
                i++;
            }
            else
            {
                return 0;
            }   
        }
        int j=0; // Check if number is unique or not
        while(j <= addressBook->contactCount)
        {
            if((strcmp(Phone , addressBook->contacts[j].phone)) != 0)
            {
                j++;
            }
            else
            {
                return 0; // If not unique return 0
            }    
        }
        return 1;
    }
    return 0;
}

// Validate email id: uniqe and proper formatting
int validate_email(char *Email , AddressBook *addressBook)
{
    for (int i=0; i<addressBook->contactCount; i++)
    {
        if (strcmp(Email, addressBook->contacts[i].email) == 0)
        {
            return 0;
        }
    }
    char *p1 = strchr(Email, '@'); // Find '@' inside email
    char *p2 = strchr(Email, '.'); // Find '.' inside email
    if (p1 != NULL)
    {
        if (p2 != NULL)
        {
            if (p2 > p1)
            {
                // Check position of '@' and '.' is around characters or not
                if (isalnum(*(p1+1)) && isalnum(*(p1-1)) && isalnum(*(p2+1)) && isalnum(*(p2-1)))
                {
                   int j=0;
                   while (Email[j]) // Ensure all characters are only letters, digits, '@', '.'
                   {
                        if (islower(Email[j]) || isdigit(Email[j]) || Email[j] == '@' || Email[j] == '.')
                        {
                            j++;
                        }
                        else
                        {
                            return 0;
                        }
                    }   
                    return 1;                 
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}