//////////////////////////////////////////////////////////////////////

// CE1007/CZ1007 Data Structures
// Week 13 Lab and Tutorial - Binary Search Tree

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////
BTNode *BSTT(BTNode *node, int value);

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{

    if (*node == NULL){
        *node = malloc(sizeof(BTNode));
        (*node)->item = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
    }
    else{
        BTNode *newNode = malloc(sizeof(BTNode));
        newNode->item = value;
        newNode->left = NULL;
        newNode->right = NULL;
        if (value < (*node)->item){
            if ((*node)->left == NULL) (*node)->left = newNode;
            else insertBSTNode(&(*node)->left, value);
        }
        else{
            if ((*node)->right == NULL) (*node)->right = newNode;
            else insertBSTNode(&(*node)->right, value);
        }
    }
}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
    if (node == NULL) return;
    printBSTInOrder(node->left);
    printf("%d ", node->item);
    printBSTInOrder(node->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
    if (node == NULL) return 1;
    if (node->item < min || node->item > max) return 0;
    return isBST(node->left, min, node->item) && isBST(node->right, node->item, max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
    if (node == NULL) return node;
    if (value < node->item) node->left = removeBSTNode(node->left, value);
    else if (value > node->item) node->right = removeBSTNode(node->right, value);
    else{
        if (node->left == NULL){
            BTNode *temp = node->right;
            free(node);
            return temp;
        }
        if (node->right == NULL){
            BTNode *temp = node->left;
            free(node);
            return temp;
        }
        BTNode *successor = findMin(node->right);
        node->item = successor->item;
        node->right = removeBSTNode(node->right, successor->item);

    }
    return node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
    while (p->left != NULL) p = p->left;
    return p;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
