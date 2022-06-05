#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
typedef struct Stack Stack;

struct Stack {
	Node** head;
	int size;
};

struct Node {
	int data;
	Node* next;
};

Stack* init_stack(){
	Stack* stack = malloc(sizeof(Stack));
	stack->head = malloc(sizeof(Node*));
	(*stack->head) = NULL;

	// printf("initilised head %p\n", *stack->head);
	stack->size = 0;
	return stack;
}

Node* new_node(int data){
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

int pop(Stack* stack){
	if (*stack->head == NULL){
		return -1;
	}

	Node* temp = *stack->head; 
	(*stack->head) = (*stack->head)->next;
	int data = temp->data;
	free(temp);
	stack->size--;
	return data;
}

void push(Stack* stack, int data){
	Node* node = new_node(data); 
	Node* temp = (*stack->head);
	(*stack->head) = node;
	node->next = temp;
	stack->size++;
}

void free_stack(Stack* stack){
	Node* node = *(stack->head);

	// printf("inside freeing the stack head %p\n", *(stack->head));

	while(node != NULL){
		Node* temp = node;
		node = node->next;
		free(temp);
	}
	
	free(stack);
}