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