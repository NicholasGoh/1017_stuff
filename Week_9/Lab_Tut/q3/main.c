// CX1007 Data Structures
// Week 9 Lab Tutorial - DynamicData-Linked Lists
// Template for Q2 and Q3

//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

//////////////////////////////////////////////////////

int searchList(ListNode *head, int value);

//////////////////////////////////////////////////////

void main()
{
	ListNode *head, *p, *temp;
	int n, result;


	head=NULL;
	p=NULL;		// pointing to the last node in the list
	printf("Enter a list of numbers, terminated by the value -1:\n");

 ////////////////////////////////////////////////////////////////////

 // Question 2
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
    temp = head;

    printf("Current list: ");
    while (temp != NULL){
        printf("%d ", temp->item);
        temp = temp->next;
    }

//////////////////////////////////////////////////////////////////////

//search for a value in the list. Q3

	printf("\nEnter value to search for: ");
	scanf("%d", &n);
	result = searchList(head,n);
    printf("Value %d found at index %d", n, result);
//////////////////////////////////////////

}

////////////////////////////////////////////////////////////

int searchList(ListNode *head, int value)
{

////////////////////////////////////////////////////////////////////

 // Question 3
    int index = 0;
    while (head != NULL){
        if (head->item == value) return index;
        head = head->next;
        index++;
    }
    return -1;

//////////////////////////////////////////////////////////////////////
}
