#include "printtree.h"
struct bufferlist {
	char buff[150];
	struct bufferlist *next;
};
void makeStrList(struct node *tree, struct bufferlist *list, int pos, int len);
void printlist(struct bufferlist *list);
void printtree(struct node *tree)
{
	int i;
	struct bufferlist *list = malloc(sizeof(struct bufferlist));
	list->next = NULL;
	for(i= 0; i < 150; i++)
	        list->buff[i] = ' ';
	list->buff[150] = '\0';
	makeStrList(tree, list, 75, 37);
	printf("Each line is 150 charecter length!\n Expecting your printing area can print at list 150 in a line\n");
	printlist(list);  
}

void printlist(struct bufferlist *list)
{
	while(list != NULL){
		printf("%s\n\n",list->buff);
		list = list->next;
	}
}

void makeStrList(struct node *tree, struct bufferlist *list, int pos, int len)
{
	int i;
	if(tree == NULL){
		list->buff[pos] = '*';
		list->buff[pos+2] = '0';
		return;
	}
	
	char str[4];
	sprintf(str, "%d", tree->data);
	for(i = 0; str[i] != '\0'; i++){
		list->buff[pos+i] = str[i];
	}
	if(tree->color){
		list->buff[pos+i+2] = '1';
	}else{
		list->buff[pos+i+2] = '0';
	}
	int childlen = len/2;
	if(list->next == NULL){
		struct bufferlist *listnode = malloc(sizeof(struct bufferlist));
		listnode->next = NULL;
		for(i = 0; i < 150; i++)
	                listnode->buff[i] = ' ';
		listnode->buff[150] = '\0';
		list->next = listnode;
	}
	makeStrList(tree->left, list->next,pos-len, childlen);
	makeStrList(tree->right, list->next, pos+len, childlen);
}