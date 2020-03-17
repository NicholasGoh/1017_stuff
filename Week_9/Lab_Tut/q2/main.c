// CX1007 Data Structures
// Week 9 Lab Tutorial - DynamicData-Linked Lists
// Template for Q2

//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;


void main()
{
	ListNode *head, *p, *temp;
	int n;
	char dummy;


	head=NULL;
	p=NULL;		// pointing to the last node in the list
	printf("Enter a list of numbers, terminated by the value -1:\n");

	/////////////////////////////////////////////////////////////////

	//Question 2
    scanf("%d", &n);
    if (n == -1) return;
    while (n != -1){
        if (head == NULL){
            head = malloc(sizeof(ListNode));
            temp = head;
        }
        else{
            temp->next = malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = n;
        scanf("%d", &n);
    }
    temp->next = NULL;

    printf("Current list: ");
    while (head != NULL){
        printf("%d ", head->item);
        head = head->next;
    }
   //////////////////////////////////////////////////////////////////
}
