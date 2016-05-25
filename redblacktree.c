#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct node {
	int color;
	int data;
	struct node *left;
	struct node *right;
};

int is_red(struct node *head)
{
	return (head == NULL)? 0: head->color;
}

int insertnode(struct node **treeheadRef,int data)
{
	
	if(*treeheadRef == NULL){
		struct node *newnode = malloc(sizeof(struct node));
		newnode->data = data;
		newnode->color = RED;
		newnode->left = NULL;
		newnode->right = NULL;
		*treeheadRef = newnode;
	}
	if((*treeheadRef)->data < data){
		insertnode(&(*treeheadRef)->right, data);
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
			}else if(is_red((*treeheadRef)->right->left){
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
		insertnode(&(*treeheadRef)->left, data);
		if(is_red((*treeheadRef)->left)){
			if(is_red((*treeheadRef)->left->left)){
				if(is_red((*treeheadRef)->right)){
					(*treeheadRef)->color = RED;
					(*treeheadRef)->right->color = BLACK;
					(*treeheadRef)->left->color = BLACK;
				}else{
					rotatetoright(treeheadRef);
				}
			}else if(is_red((*treeheadRef)->left->right){
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
void rotatetoleft(struct node **subtreeRef)
{
	struct node *temp;
	temp = *subtreeRef;
	*subtreeRef = (*subtreeRef)->right;
	*subtreeRef->color = BLACK;
	temp->right = (*subtreeRef)->left;
	temp->color = RED;
	(*subtreeRef)->left = temp;
}

void rotatetoright(struct node **subtreeRef)
{
	struct node *temp;
	temp = *subtreeRef;
	*subtreeRef = (*subtreeRef)->left;
	*subtreeRef->color = BLACK;
	temp->left = (*subtreeRef)->right;
	temp->color = RED;
	(*subtreeRef)->right = temp;
}

main()
{
	struct node *head = malloc(sizeof(struct node));
	head->color = 1;
	printf("%d\n",is_red(head));
	head->color = 0;
	printf("%d\n",is_red(head));
	printf("%d\n",is_red(NULL));
	
}