#include <stdio.h>
#include <stdlib.h>
#include "printtree.h"

#define RED 1
#define BLACK 0

int is_red(struct node *head)
{
	return (head == NULL)? 0: head->color;
}
int leftimbalacecorrection(struct node **treeheadRef);
void rotatetoleft(struct node **subtreeRef);
void rotatetoright(struct node **subtreeRef);
int maxOftree(struct node *subtree);
void insertnode(struct node **root, int data);
void printtree(struct node *tree);

int insertNodeHelper(struct node **treeheadRef,int data)
{
	if(*treeheadRef == NULL){
		struct node *newnode = malloc(sizeof(struct node));
		newnode->data = data;
		newnode->color = RED;
		newnode->left = NULL;
		newnode->right = NULL;
		*treeheadRef = newnode;
		return;
	}
	if((*treeheadRef)->data < data){
		insertNodeHelper(&(*treeheadRef)->right, data);
		struct node *temp;
		if(is_red((*treeheadRef)->right)){
			if(is_red((*treeheadRef)->right->right)){
				if(is_red((*treeheadRef)->left)){
					(*treeheadRef)->color = RED;
					(*treeheadRef)->left->color = BLACK;
					(*treeheadRef)->right->color = BLACK;
				}else{
					rotatetoleft(treeheadRef);
				}
			}else if(is_red((*treeheadRef)->right->left)){
				if(is_red((*treeheadRef)->left)){
					(*treeheadRef)->color = RED;
					(*treeheadRef)->right->color = BLACK;
					(*treeheadRef)->left->color = BLACK;
				}else{
					rotatetoright(&(*treeheadRef)->right);
					rotatetoleft(treeheadRef);
				}
			}
		}
	}
	else{
		insertNodeHelper(&(*treeheadRef)->left, data);
		if(is_red((*treeheadRef)->left)){
			if(is_red((*treeheadRef)->left->left)){
				if(is_red((*treeheadRef)->right)){
					(*treeheadRef)->color = RED;
					(*treeheadRef)->right->color = BLACK;
					(*treeheadRef)->left->color = BLACK;
				}else{
					rotatetoright(treeheadRef);
				}
			}else if(is_red((*treeheadRef)->left->right)){
				if(is_red((*treeheadRef)->right)){
					(*treeheadRef)->color = RED;
					(*treeheadRef)->right->color = BLACK;
					(*treeheadRef)->left->color = BLACK;
				}else{
					rotatetoleft(&(*treeheadRef)->left);
					rotatetoright(treeheadRef);
				}
			}
		}
	}
}

void insertnode(struct node **root, int data)
{
	insertNodeHelper(root, data);
	(*root)->color = BLACK;
}

void rotatetoleft(struct node **subtreeRef)
{
	struct node *temp;
	temp = *subtreeRef;
	*subtreeRef = (*subtreeRef)->right;
	(*subtreeRef)->color = BLACK;
	temp->right = (*subtreeRef)->left;
	temp->color = RED;
	(*subtreeRef)->left = temp;
}

void rotatetoright(struct node **subtreeRef)
{
	struct node *temp;
	temp = *subtreeRef;
	*subtreeRef = (*subtreeRef)->left;
	(*subtreeRef)->color = BLACK;
	temp->left = (*subtreeRef)->right;
	temp->color = RED;
	(*subtreeRef)->right = temp;
}

int deleteNodeWithDataHelper(struct node **treeRef, int data)
{
	int status = 0;
	if((*treeRef) == NULL){
		status = 1;
	}else{
		if((*treeRef)->data == data){
			if((*treeRef)->left == NULL || (*treeRef)->right == NULL){
				struct node *temp = *treeRef;
				if((*treeRef)->left == NULL){
					*treeRef = (*treeRef)->right;
				}else{
					*treeRef = (*treeRef)->left;
				}
				if(temp->color){
					status = 1;
				}else if(is_red(*treeRef)){
					if(*treeRef){
						(*treeRef)->color = BLACK;
					}
					status = 1;
				}
				free(temp);
				return status;
			}else{
				(*treeRef)->data = maxOftree((*treeRef)->left);
				status = deleteNodeWithDataHelper(&(*treeRef)->left, (*treeRef)->data);
				if(!status){
					status = leftimbalacecorrection(treeRef);
				}
				return status;
			}
		}else if((*treeRef)->data < data){
			status = deleteNodeWithDataHelper(&(*treeRef)->right, data);
			if(!status){
				printf("right\n");
				status = rightimbalacecorrection(treeRef);
			}
			return status;
		}else{
			status = deleteNodeWithDataHelper(&(*treeRef)->left, data);
			if(!status){
				printf("left\n");
				status = leftimbalacecorrection(treeRef);
			}
			return status;
		}
	}
}

int maxOftree(struct node *tree)
{
	while(tree->right != NULL){
		tree= tree->right;
	}
	return tree->data;
}

int leftimbalacecorrection(struct node **treeheadRef)
{
	int status = 0;
	struct node *parent = *treeheadRef;
	struct node *sibling = parent->right;
	
	if(is_red(sibling)){
		rotatetoleft(treeheadRef);
		sibling = parent->right;
	}
	
	if(sibling != NULL){
		if( !is_red(sibling->left) && !is_red(sibling->right)){
			if(is_red(parent))
				status = 1;
			parent->color = BLACK;
			sibling->color = RED;
		}else{
			int formerColor = parent->color;
			int newRoot = ((*treeheadRef) != parent);
			if(is_red(sibling->right)){
				rotatetoleft(&parent);
			}else{
				rotatetoright(&(parent->right));
				rotatetoleft(&parent);
			}
			parent->color = formerColor;
			parent->right->color = BLACK;
			parent->left->color = BLACK;
			if(!newRoot){
				*treeheadRef = parent;
			}else{
				(*treeheadRef)->left = parent;
			}
			status = 1;
		}
	}
	return status;
}















int rightimbalacecorrection(struct node **treeheadRef)
{
	int status = 0;
	struct node *parent = *treeheadRef;
	struct node *sibling = parent->left;
	
	if(is_red(sibling)){
		rotatetoright(treeheadRef);
		sibling = parent->left;
	}
	
	if(sibling != NULL){
		if( !is_red(sibling->right) && !is_red(sibling->left)){
			if(is_red(parent))
				status = 1;
			parent->color = BLACK;
			sibling->color = RED;
		}else{
			int formerColor = parent->color;
			int newRoot = ((*treeheadRef) != parent);
			if(is_red(sibling->left)){
				rotatetoright(&parent);
			}else{
				rotatetoleft(&(parent->left));
				rotatetoright(&parent);
			}
			parent->color = formerColor;
			parent->left->color = BLACK;
			parent->right->color = BLACK;
			if(!newRoot){
				*treeheadRef = parent;
			}else{
				(*treeheadRef)->right = parent;
			}
			status = 1;
		}
	}
	return status;
}



















void deleteNodeWithData(struct node **treeRef, int data)
{
	deleteNodeWithDataHelper(treeRef, data);
	if ((*treeRef) != NULL){
		(*treeRef)->color = 0;
	}
}

main()
{
	struct node *rbtree = NULL;
	insertnode (&rbtree, 64);
	printf("after inserting 64\n------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 80);
	printf("after inserting 80\n------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 96);
	printf("after inserting 96\n------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 100);
	printf("after inserting 100\n-------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 51);
	printf("after inserting 51\n------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 10);
	printf("after inserting 10\n------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 150);
	printf("after inserting 150\n-------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 70);
	printf("after inserting 70\n------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 15);
	printf("after inserting 15\n------------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 9);
	printf("after inserting 9\n-----------------\n");
	printtree(rbtree);
	insertnode (&rbtree, 8);
	printf("after inserting 8\n-----------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 8);
	printf("deleting nodes with data 8\n--------------------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 100);
	printf("deleting nodes with data 100\n----------------------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 70);
	printf("deleting nodes with data 70\n---------------------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 64);
	printf("deleting nodes with data 64\n---------------------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 80);
	printf("deleting nodes with data 80\n---------------------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 96);
	printf("deleting nodes with data 96\n---------------------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 10);
	printf("deleting nodes with data 10\n---------------------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 9);
	printf("deleting nodes with data 9\n--------------------------\n");
	printtree(rbtree);
	deleteNodeWithData(&rbtree, 150);
	printf("deleting nodes with data 150\n----------------------------\n");
	printtree(rbtree);	
}