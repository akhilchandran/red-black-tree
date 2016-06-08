
/*
 * Each line is 150 charecter length!
 * Expecting your printing area can print at list 150 in a line.
 */
#include <stdio.h>
#include <stdlib.h>
struct node {
	int color;
	int data;
	struct node *left;
	struct node *right;
};
void printtree(struct node *tree);