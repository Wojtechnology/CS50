#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "/users/wojtekswiderski/documents/cs50/library50-c-5/cs50.c"

#include "list.h"

// linked list
node *first = NULL;

// prototypes
void delete(void);
void insert(void);
void search (void);
void traverse(void);

int main(void)
{
	int c;
	do
	{
		// print instructions
		printf("\nMENU\n\n"
			"1 - delete\n"
			"2 - insert\n"
			"3 - search\n"
			"4 - traverse\n"
			"0 - quit\n\n");
		
		// get command
		printf("Command: ");
		c = GetInt();
		
		// try to execure command
		switch(c)
		{
			case 1: delete(); break;
			case 2: insert(); break;
			case 3: search(); break;
			case 4: traverse(); break;
		}
	}
	while(c != 0);
	
	// free list before exiting
	node *ptr = first;
	while(ptr != NULL)
	{
		node *predptr = ptr;
		ptr = ptr->next;
		free(predptr);
	}
}

void delete(void)
{
    // prompt user for number
    printf("Number to delete: ");
    int n = GetInt();

    // get list's first node
    node* ptr = first;

    // try to delete number from list
    node* predptr = NULL;
    while (ptr != NULL)
    {
        // check for number
        if (ptr->n == n)
        {
            // delete from head
            if (ptr == first)
            {
                first = ptr->next;
                free(ptr);
            }

            // delete from middle or tail
            else
            {
                predptr->next = ptr->next;
                free(ptr);
            }

            // all done
            break;
        }
        else
        {
            predptr = ptr;
            ptr = ptr->next;
        }
    }

    // traverse list
    traverse();
}

void insert(void)
{
	node *newptr = malloc(sizeof(node));
	if(newptr == NULL)
	{
		return;
	}
	
	printf("Number to insert: ");
	newptr->n = GetInt();
	newptr->next = NULL;
	
	if(first == NULL)
	{
		first = newptr;
	}
	else if(newptr->n < first->n)
	{
		newptr->next = first;
		first = newptr;
	}
	else
	{
		node *predptr = first;
		while(true)
		{
			if(predptr->n == newptr->n)
			{
				free(newptr);
				break;
			}
			else if(predptr->next == NULL)
			{
				predptr->next = newptr;
				break;
			}
			else if(newptr->n < predptr->next->n)
			{
				newptr->next = predptr->next;
				predptr->next = newptr;
				break;
			}
			predptr = predptr->next;
		}
	}
	traverse();
}

void search(void)
{
	printf("Number to search for: ");
	int n = GetInt();
	
	node *ptr = first;
	
	while(ptr != NULL)
	{
		if(ptr->n == n)
		{
			printf("\nFound %i!\n", n);
			sleep(1);
			break;
		}
		ptr = ptr->next;
	}
}

void traverse(void)
{
    // traverse list
    printf("\nLIST IS NOW: ");
    node* ptr = first;
    while (ptr != NULL)
    {
        printf("%i ", ptr->n);
        ptr = ptr->next;
    }

    // flush standard output since we haven't outputted any newlines yet
    fflush(stdout);

    // pause before continuing
    sleep(1);
    printf("\n\n");
}