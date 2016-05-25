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
