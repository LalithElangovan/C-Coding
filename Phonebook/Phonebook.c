#include <stdio.h>
#include <stdlib.h>
//#include "contactList.h"
#include <string.h>
#include <ctype.h>

// IF IT'S EASIER, YOU NEED NOT BE OVERLY GENERAL/FLEXIBLE
// BUT CAN ASSUME THESE LIMITS
#define MAXCONTACTS 30 /* max # of contacts */
#define MAXPHONES 10   /* max # of phone numbers for each contact */

#define PHONE_NUMBER_MAX_LENGTH 12
//Structure for the numbers in contactList.h along with pointer to link them
typedef struct _number
{
	struct _number *next;
	char number[4096];

} number;
//Structure for the contact along with a pointer for the next contact and the first number of the present contact
typedef struct _contact
{
	struct _contact *next;
	char name[4096];
	number *firstNum;

} contact;
//Structure to help with finding duplicates as it has both number and name
typedef struct _numName
{
	struct _numName *next;
	char *name;
	char *number;

} numName;
//Global Variable
contact *first;

// INCLUDE YOUR OWN "HELPER" ROUTINES AS YOU SEE FIT
//Helper subroutine to sort the list alphabetically
void SortAlphabetical()
{
	//Previous, current and next contact to help with linking when we need to rearrange
	contact *previousContact = first;
	contact *currentContact = first;
	contact *nextContact = first->next;
	//Sorting algorithm that uses strcmp to compare and sort the names
	while (nextContact)
	{
		if (strcmp(currentContact->name, nextContact->name) > 0)
		{
			//Special case if we have to swap the first and second elements within the list, as we need to update the first pointer
			if (first == currentContact)
				first = nextContact;
			else
			{
				//Swapping the two elements
				previousContact->next = nextContact;
			}
			currentContact->next = nextContact->next;
			nextContact->next = currentContact;
			//Goes back to the beginning and comes out of the loop when everything has been swapped
			previousContact = first;
			currentContact = first;
			nextContact = first->next;
		}
		//Move forward in the list
		else
		{
			//When currentcontact is the first node, there is no previous node, so previous node will be the first node.
			if (previousContact != currentContact)
			{
				previousContact = currentContact;
			}

			currentContact = nextContact;
			nextContact = nextContact->next;
		}
	}
}

void ListAllContacts()
{
	if (first == NULL)
	{
		return;
	}
	SortAlphabetical();

	contact *currentContact = first;
	number *currentNum;

	while (currentContact)
	{
		//Print name of the contact
		printf("Name: %s\n", currentContact->name);
		currentNum = currentContact->firstNum;
		printf("Phone(s):");
		//While loop to print numbers
		while (currentNum)
		{
			printf(" %s", currentNum->number);
			currentNum = currentNum->next;
		}

		printf("\n");
		//Move to next contact until you hit a null
		currentContact = currentContact->next;
	}
}

/*
 * convertInputToDataStructure
 * Takes the information in contactList.h and puts it into a data
 * structure of your choosing, however: 1 mark of the lab will be
 * for using structs with pointers in your solution.
 * You might also want to consider the outputs from the program
 * (see the menu printed in printMenu) since some structures will
 * make this easier than others.
 */
void convertInputToDataStructure()
{
	if ((sizeof(contactList) / (sizeof(contactList[0]))) == 0)
	{
		first = NULL;
		return;
	}
	//Allocate memory to the first vairable.
	first = malloc(sizeof(contact));
	//Sets currentcontact to the first contact in the memory
	contact *currentContact = first;
	currentContact->next = 0;
	//Copy the contact name from contactList.h
	strcpy(currentContact->name, contactList[0]);
	//Allocate memory for the numbers of each contact
	currentContact->firstNum = malloc(sizeof(number));
	//sets the pointer to the number of current contact
	number *currentNum = currentContact->firstNum;
	currentNum->next = 0;
	//Copies the number of the contact
	strcpy(currentNum->number, contactList[1]);
	//For loop to check whether something is a name or number, i=2 to start from second person as first has already been regarded
	for (int i = 2; i < sizeof(contactList) / sizeof(contactList[0]); i++)
	{
		if (isalpha(contactList[i][0]))
		{
			currentContact->next = malloc(sizeof(contact));
			currentContact = currentContact->next;
			strcpy(currentContact->name, contactList[i]);
			currentContact->firstNum = malloc(sizeof(number));
			//Store the number strings, and use i to traverse the array and check numbers
			currentNum = currentContact->firstNum;
			currentNum->next = 0;
			strcpy(currentNum->number, contactList[i + 1]);
			i++;
		}
		//If we need to add more than one number to the person.
		else
		{
			number *newNum = malloc(sizeof(number));
			newNum->next = currentNum;
			currentContact->firstNum = newNum;
			currentNum = newNum;
			strcpy(currentNum->number, contactList[i]);
		}
	}

	return;
}

/*
 * printMenu - Prints out the user menu
 */
void printMenu()
{
	printf("\n\nEnter a command by number\n");
	printf("1. List all contacts in alphabetical order\n");
	printf("2. Print phone(s) for a contact\n");
	printf("3. Find duplicate entries\n");
	printf("4. Delete contact\n");
	printf("5. Exit the program\n");
	printf("Your input: ");
}

//eliminate trailing \n
char *rtrim(char *str)
{
	int i;
	for (i = strlen(str) - 1; i >= 0 && str[i] == '\n'; i--)
		str[i] = '\0';
	return str;
}

void PrintContact()
{
	char name[4096];

	printf("Enter name: ");
	//Scan to get the name of the person
	fgets(name, sizeof(name), stdin);
	rtrim(name);
	if (first == NULL)
	{
		printf("Contact not found\n");
		return;
	}
	contact *currentContact = first;
	number *currentNum;
	//This while loop is to compare the strings within the linked lists
	while (currentContact)
	{
		//This checks to see if the contact name matches if it does it proceeds to print the phone numbers
		if (!strcmp(currentContact->name, name))
		{
			printf("Name: %s\n", name);
			currentNum = currentContact->firstNum;
			printf("Phone(s):%s", currentNum);
			//This is in case a person has multiple numbers
			while (currentNum)
			{
				printf(" %s", currentNum->number);
				currentNum = currentNum->next;
			}

			printf("\n");
			return;
		}

		currentContact = currentContact->next;
	}

	printf("Contact not found\n");
}

/*
 * DeleteContact deletes a contact from the list
 * The user must enter the name of the contact to delete
 * 
 */

void DeleteContact()
{
	//Compare the names and if it exists delete the data regarding the name (node) and link the surrounding nodes
	char name[4096];
	printf("Enter name: ");
	fgets(name, sizeof(name), stdin);
	rtrim(name);
	char *test;
	if (first == NULL)
	{
		printf("Contact not found\n");
		return;
	}
	contact *previousContact = first;
	contact *currentContact = first;
	contact *nextContact = first->next;
	if (!strcmp(currentContact->name, name))
	{
		first = nextContact;
		return;
	}
	while (strcmp(currentContact->name, name) && nextContact != NULL)
	{
		previousContact = currentContact;
		currentContact = currentContact->next;
		nextContact = nextContact->next;
		test = currentContact->name;
	}
	if (strcmp(test, name))
	{
		printf("Contact not found\n");
	}
	else
	{
		previousContact->next = nextContact;
	}
}

/*
 * findDuplicates finds the names of contacts with 
 * a phone number in common
 */

void FindDuplicates()
{
	if (first == NULL)
	{
		printf("No duplicates found\n");
		return;
	}
	//First sort the name in order
	SortAlphabetical();
	int counter = 0;
	contact *currentContact = first;
	number *currentNum = currentContact->firstNum;
	//Allocate the memory for name and number, using the third structure
	numName *firstNumName = malloc(sizeof(numName));
	numName *currentNumName = firstNumName;
	currentNumName->next = 0;
	currentNumName->name = currentContact->name;
	currentNumName->number = currentNum->number;
	//To traverse through the nested linklists (1st and 2nd structure) and expand the data into a new linked list/ 3rd structure
	while (currentContact)
	{
		currentNum = currentContact->firstNum;
		//To create new nodes for the thrid structure
		while (currentNum)
		{
			currentNumName->next = malloc(sizeof(numName));
			currentNumName = currentNumName->next;
			currentNumName->next = 0;
			currentNumName->name = currentContact->name;
			currentNumName->number = currentNum->number;

			currentNum = currentNum->next;
		}

		currentContact = currentContact->next;
	}

	currentNumName = firstNumName;
	numName *checkNumName;
	//Current is first element, and check is the second, that gets iterated and is used to check the next number
	char *currentName = "";
	char *checkName = "";

	while (currentNumName)
	{
		checkNumName = currentNumName->next;
		//If the numbers are the same, but the names are different.
		while (checkNumName)
		{
			if (!strcmp(currentNumName->number, checkNumName->number))
				if (strcmp(currentNumName->name, checkNumName->name))
					//To check if we already have done the two names prior
					if (strcmp(currentNumName->name, currentName) || strcmp(checkNumName->name, checkName))
					{
						currentName = currentNumName->name;
						checkName = checkNumName->name;
						printf("%s and %s have a phone number in common\n",currentName, checkName);
							   counter++;
					}

			checkNumName = checkNumName->next;
		}

		currentNumName = currentNumName->next;
	}
	//Goes back to the start of the linkedlist and frees it.
	currentNumName = firstNumName;
	numName *previousNumName;

	while (currentNumName)
	{
		previousNumName = currentNumName;
		//Free the dynamically allocated memory
		free(previousNumName);
		currentNumName = currentNumName->next;
	}
	if (counter == 0)
	{
		printf("No duplicates found\n");
	}
	return;
}

int main()
{
	// first move data from contactList.h to a data structure
	convertInputToDataStructure();

	char notDone = 1;
	while (notDone)
	{
		printMenu();
		char userChoice[100];
		char *s = fgets(userChoice, sizeof(userChoice), stdin);
		if (!s)
		{
			printf("Wrong input\n");
			continue;
		}
		s = rtrim(s); /* eliminate trailing \n */
		//printf("selection = %s\n", s);
		int userSelection = atoi(s);

		switch (userSelection)
		{
		case 1:
			ListAllContacts();
			break;
		case 2:
			PrintContact();
			break;
		case 3:
			FindDuplicates();
			break;
		case 4:
			DeleteContact();
			break;
		case 5:
			notDone = 0;
			break;
		default:
			printf("Bad command...\n");
			break;
		}
	}

	// PUT ANY POST_RUN CODE HERE

	return 0;
}
