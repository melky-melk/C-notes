#include <stdio.h>
#include <stdlib.h> 

struct node{
	// void *data; //dont know what the data will contain so instead we just store the address
	int data; //dont know what the data will contain so instead we just store the address
	struct node *next; //a pointer to the next node, it will be 8 bytes
};

void print_list(struct node *head){

	if (head == NULL){
		return;
	}

	// assert head != NULL
	int counter = 0;
	while (head != NULL){
		printf("%d\n", head -> data);

		head = head->next;

		counter ++;
	}
}

int main(){
	struct node *n1;
	struct node *n2;

	n1 = (struct node*)malloc(sizeof(struct node));
	n2 = (struct node*)malloc(sizeof(struct node));

	// set the data
	n1->data = 1;
	n2->data = 2;

	n1->next = n2; //store the address of n2 as n1->next;
	n2->next = NULL;

	struct node *head = n1; 

	print_list(head);
}