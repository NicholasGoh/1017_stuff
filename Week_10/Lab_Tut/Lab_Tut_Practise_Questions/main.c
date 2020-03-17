// CE1007/CZ1007 Data Structures
// Week 10 Lab Tutorial - Linked List

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////
////////////

typedef struct _listnode{
	int num;
	struct _listnode *next;
} ListNode;
typedef struct _linkedlist{
	ListNode *head;
	int size;
} LinkedList;
typedef struct _dbllistnode{
	int num;
	struct _dbllistnode *pre;
	struct _dbllistnode *next;
} DblListNode;

////////////////////////////////////////////////////////////////////
////////////
int removeNode(ListNode **ptrHead, int index);
int removeNode2(LinkedList *ll, int index);
int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList);
int duplicateReverse(ListNode *head, ListNode **ptrNewHead);

void printList(ListNode *head);
ListNode * findNode(ListNode *head, int index);
int insertNode(ListNode **ptrHead, int index, int value);


// these are for the practice questions
int moveMaxToFront(ListNode **ptrHead);
int concatenate(ListNode **ptrHead1, ListNode *head2);
int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2);
int insertDbl(DblListNode **ptrHead, int index, int value);
void printDblList(DblListNode *head);

////////////////////////////////////////////////////////////////////
////////////

int main()
{
	int i;
	ListNode *head = NULL;
	ListNode *dupRevHead = NULL;
	ListNode *oddHead = NULL;
	ListNode *evenHead = NULL;
	ListNode *list1Head = NULL, *list2Head = NULL;
	ListNode *combAltHead = NULL;
	DblListNode *dblHead = NULL;
	LinkedList llist;
	int size = 0;

	//build a linked list
	if (insertNode(&head, 0, 6) == 0) size++;
	if (insertNode(&head, 0, 4) == 0) size++;
	if (insertNode(&head, 0, 2) == 0) size++;
	printf("After inserting 3 values.");
	printList(head);


	//removeNode(): question 1
	if (removeNode(&head, 3) == 0) size--;//this one can't be removed.
	if (removeNode(&head, 1) == 0) size--;
	if (removeNode(&head, 0) == 0) size--;

	printf("\nafter remove using removeNode(), ");
	printList(head);

	//insert some nodes
	if (insertNode(&head, 2, 3) == 0) size++; // this one can't be inserted.
	if (insertNode(&head, 1, 1) == 0) size++;
	if (insertNode(&head, 0, 0) == 0) size++;

	printf("\nafter insert, ");
	printList(head);

	//removeNode2(): question 2
	llist.head = head;
	llist.size = size;
	removeNode2(&llist, 2);
	removeNode2(&llist, 0);
	removeNode2(&llist, 0);
	head = llist.head;


	printf("\nafter remove using removeNode2(), ");
	printList(llist.head);
	// empty linked list now

	//split(): question 3
	for (i = 1; i <10; i++)//build a new linked list
		insertNode(&head, 0, i);
	printf("\n\ninsert 1-9 to the linked list,");
	printList(head);
	printf("split the current list, results:\n");
	split(head, &evenHead, &oddHead);
	printf("the even list");
	printList(evenHead);
	printf("the odd list");
	printList(oddHead);

	//duplicateReverse(): question 4
	printf("\n");
	printList(head);
	duplicateReverse(head, &dupRevHead);
	printf("After duplicateReverse(),");
	printList(dupRevHead);

	////////////////////////////////////////////////////////////////////////
	//the following are for the PRACTICE QUESTIONS

	printf("\n\nNow for the practice questions");

	//1.moveMaxToFront()
	printf("\n************** moveMaxToFront *******************\n");
	printList(dupRevHead);
	moveMaxToFront(&dupRevHead);
	printf("after moveMaxToFront()");
	printList(dupRevHead);

	//2. concatenate()
	printf("\n************** concatenate() *******************\n");
	concatenate(&head, dupRevHead);
	printf("concatenate(current list, duplicate reverse list)\n  ");
	printList(head);

	//3.combineAlternating()
	printf("\n************** combineAlternating() *******************\n");
	for (i = 3; i > 0; i--)				//build linked list 1
		insertNode(&list1Head, 0, i);
	for (i = 13; i > 10; i--)			//build linked list 2
		insertNode(&list2Head, 0, i);
	printf("List 1:");
	printList(list1Head);
	printf("List 2: ");
	printList(list2Head);
	combineAlternating(&combAltHead, list1Head, list2Head);
	printf("After combineAlternating(): ");
	printList(combAltHead);

	//4. insertDbl()
	printf("\n************** insertDbl() *******************\n");
	printf("insertDbl()\nDoubly-linked list: ");
	insertDbl(&dblHead, 0, 10);
	insertDbl(&dblHead, 0, 20);
	insertDbl(&dblHead, 1, 30);
	insertDbl(&dblHead, 2, 40);
	printDblList(dblHead);
	return 0;
}

////////////////////////////////////////////////////////////////////
////////////

void printList(ListNode *head){
	ListNode *cur = head;

	if (cur == NULL)
		return;

	printf("the current linked list is:\n");
	while (cur != NULL){
		printf("%d ", cur->num);
		cur = cur->next;
	}
	printf("\n");
}

void printDblList(DblListNode *head){
	if (head == NULL) return;
	while (head != NULL){
		printf("%d ", head->num);
		head = head->next;
	}
	printf("\n");
}

ListNode * findNode(ListNode *head, int index){
	if (head == NULL || index < 0) return NULL;
	while (index > 0){
		head = head->next;
		if (head == NULL)
			return NULL;
		index--;
	}
	return head;
}


int insertNode(ListNode **ptrHead, int index, int value){
	ListNode *pre, *cur;
	// If empty list or inserting first node, need to update head pointer
	if (*ptrHead == NULL || index == 0){
		cur = *ptrHead;
		*ptrHead = malloc(sizeof(ListNode));
		(*ptrHead)->num = value;
		(*ptrHead)->next = cur;
		return 0;
	}
	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ptrHead, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->num = value;
		pre->next->next = cur;
		return 0;
	}
	return -1;
}

////////////////////////////////////////////////////////////////////
////////////

int removeNode(ListNode **ptrHead, int index){
    ListNode *after, *pre;

    if (*ptrHead == NULL) return -1;
    if (index == 0){
        pre = *ptrHead;
        *ptrHead = (*ptrHead)->next;
        free(pre);
    }
	else if ((pre = findNode(*ptrHead, index - 1)) != NULL){
        if (pre->next == NULL) return -1; // out of index
        else{
            after = pre->next->next;
            pre->next = after;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int removeNode2(LinkedList *ll, int index) {
    ListNode *after, *pre;

    if (ll->head == NULL) return -1;
    if (index == 0){
        pre = ll->head;
        ll->head = ll->head->next;
        free(pre);
    }
	else if ((pre = findNode(ll->head, index - 1)) != NULL){
        if (pre->next == NULL) return -1; // out of index
        else{
            after = pre->next->next;
            pre->next = after;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList)
{
    ListNode *temp;
    int evenOrodd = 0, evenCount = 0, oddCount = 0;

    temp = head;
    while(temp != NULL){
        if (evenOrodd % 2 == 0){
            insertNode(ptrEvenList, evenCount, temp->num);
            evenCount++;
        }
        else{
            insertNode(ptrOddList, oddCount, temp->num);
            oddCount++;
        }
        evenOrodd++;
        temp = temp->next;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int duplicateReverse(ListNode *head, ListNode **ptrNewHead){
    ListNode *temp;

    temp = head;
    if (temp == NULL) return -1;
    while(temp != NULL){
        insertNode(ptrNewHead, 0, temp->num);
        temp = temp->next;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////
////////////

int moveMaxToFront(ListNode **ptrHead){
    ListNode *maxNode, *temp;
    int index = 0, maxIndex;

    temp = *ptrHead;
    maxNode = temp->num;
    while (temp != NULL){
        if (temp->num > maxNode){
            maxNode = temp->num;
            maxIndex = index;
        }
        temp = temp->next;
        index++;
    }
    if (maxNode == (*ptrHead)->num) return -1;
    removeNode(ptrHead, maxIndex);
    insertNode(ptrHead, 0, maxNode);
    return 0;
}


int concatenate(ListNode **ptrHead1, ListNode *head2){
    ListNode *temp;

    if (*ptrHead1 == NULL){
        if (head2 == NULL) return -1;
        *ptrHead1 = malloc(sizeof(ListNode));
        (*ptrHead1)->next = head2;
    }
    if (head2 == NULL) return -1;
    else{
        temp = *ptrHead1;
        while(temp->next != NULL) temp = temp->next;
        temp->next = head2;
    }
    return 0;
}


int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2){
    ListNode *temp;
    int index = 0;

    while(head1 != NULL){
        insertNode(ptrHead, index, head1->num);
        head1 = head1->next;
        index++;
        if (head1 == NULL && head2 == NULL) break;
        insertNode(ptrHead, index, head2->num);
        head2 = head2->next;
        index++;
    }
}


int insertDbl(DblListNode **ptrHead, int index, int value){
    DblListNode *preNode, *cur, *newNode;

    // If empty list or inserting first node, need to update head pointer
	if (*ptrHead == NULL || index == 0){
		cur = *ptrHead;
		*ptrHead = malloc(sizeof(ListNode));
		(*ptrHead)->num = value;
		(*ptrHead)->next = cur;
		(*ptrHead)->pre = NULL;
		if (cur != NULL) cur->pre = *ptrHead;
		return 0;
	}
	// get preNode
	preNode = *ptrHead;
	index--;
	while (index > 0){
		preNode = preNode->next;
		if (preNode == NULL)
			return -1;
		index--;
	}
	// make newNode and connect doubly
    cur = preNode->next;
    newNode = malloc(sizeof(DblListNode));
    newNode->num = value;
    newNode->next = cur;
    newNode->pre = preNode;
    if (cur != NULL) cur->pre = newNode;
    preNode->next = newNode;
    return 0;
}
////////////////////////////////////////////////////////////////////
