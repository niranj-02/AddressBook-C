#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
    printf("\n------------------------------------\n");
    printf("         ADDRESS BOOK MENU  \n");
    printf("------------------------------------\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                int sortChoice;
                printf("\n📇CONTACTS\n-----------\nSort by: \n1. Name\n2. Phone\n3. Email\n4. Default sort\nEnter your choice: ");
                scanf("%d", &sortChoice);      
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("\nSaving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("\nInvalid choice\nReturning to main menu.\n");
        }
    } while (choice != 7);
    
       return 0;
}
