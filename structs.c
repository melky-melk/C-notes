#include "default.h"

/////////////////////////////STACK AND QUEUES///////////////////////////
typedef struct Node Node;

struct Node{
	void* data; //remember to typecast to Order* or InventoryData*
	Node* next;
	int priority;
};

Node* new_node(void* data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void* list_get(Node* head, int index){
	for (int i = 0; i < index; i++)	{head = head->next;}
	return head->data;
}

void stack_push(Node** head, void* data){
	Node* node = new_node(data);
	// make the node's next the current head
	node->next = *head;
	// sets the current head to point to the new node
	*head = node;
}

void queue_push(Node** head, void* data){
	if ((*head) == NULL) {
		(*head) = new_node(data);
		return;
	}
	Node* node = (*head);

	// get the last node
	while (node->next != NULL)
		node = node->next;
	
	// sets the last node to point to the new node created
	node->next = new_node(data);
}

void* peek(Node** head) {return (*head) == NULL ? NULL : (*head)->data;}

void* pop(Node** head) {
	Node* temp = *head;
	(*head) = (*head)->next;
	void* data = temp->data;
	free(temp);
	return data;
}

// removes the node storing the data it but not the actual data itself
int remove_data(Node** head, void* data){
    if ((*head) == NULL) {return 0;}
    Node* deleted_node;

    if ((*head)->data == data)    {
        deleted_node = (*head); 
        (*head) = (*head)->next;
    } 
    else {
        // tries to get the node before the one you need to delete
        if ((*head)->next == NULL) return 0;
        Node* previous_node = (*head);

        // keeps looping until it finds the node, where its next noded matches the data
        if (previous_node->next == NULL){return 0;}
        while (previous_node->next->data != data){
            //if it cant find it, then return False 
            if (previous_node->next == NULL){return 0;}
            previous_node = previous_node->next;
        }

        // the data who matches is the deleted node
        deleted_node = previous_node->next;
        // skip the deleted node by giving the previous node the next node
        previous_node->next = deleted_node->next;
    }
    
    free(deleted_node);
    return 1;
}

/* Given a reference (pointer to pointer) to the head of a
   list and a key, deletes the first occurrence of key in
   linked list */
void deleteNode(struct Node** head_ref, int key)
{
    // Store head node
    struct Node *temp = *head_ref, *prev;
 
    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
 
    // If key was not present in linked list
    if (temp == NULL)
        return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 
    free(temp); // Free memory
}

void free_nodes(Node** node){
	while ((*node) != NULL){
		Node* temp = (*node);
		(*node) = (*node)->next;
		free(temp);
	}
}

void* find_data(Node* head, void* data){	
	Node* node = head;
	while (node != NULL){
		if (node->data == data) {return data;}
		node = node->next;
	}

	return NULL;
}

///////////////////////////////DYNAMIC ARRAYS/////////////////////////////
#define INIT_SIZE 10

typedef struct dyn_array dyn_array;
struct dyn_array{
	int length;
	int size;
	void** elements;
}

dyn_array* init_dyn_array(){
	dyn_array* new_array = malloc(sizeof(dyn_array));
	new_array->length = 0;
	new_array->size = INIT_SIZE;

	new_array->elements = malloc(new_array->size * sizeof(void*));

	return new_array;
}

void add_to_array(){

}

void array_get_index(){
	
}

void array_put_index(){
	
}

//////////////////////////////PRIORITY QUEUE///////////////////////////////

void priority_max_queue_push(Node** head, int priority, void* data) {
	if ((*head) == NULL) {
		(*head) = new_node(data);
		return;
	}

	Node* node = (*head);
	Node* temp = new_node(data);

	// if current head is lower than the new head, then the new head is the head
	if (((*head)->priority < priority) {
		temp->next = *head;
		(*head) = temp;
	} 
	
	else {
		// while there is more nodes, and the priority of the current nodes are higher than the new order, keep going
		// keep moving until the current node priority is lower or there are no more nodes 
		while (node->next != NULL && node->next->priority > priority) {
			node = node->next;
		}
		
		// the temp is placed where the current node is its next is move
		temp->next = node->next;
		// the node moves behind the temp
		node->next = temp;
	}
}

void priority_max_queue_push(Node** head, int priority, void* data) {
	if ((*head) == NULL) {
		(*head) = new_node(data);
		return;
	}

	Node* node = (*head);
	Node* temp = new_node(data);

	// if current head is lower than the new head, then the new head is the head
	if (((*head)->priority > priority) {
		temp->next = *head;
		(*head) = temp;
	} 
	
	else {
		// while there is more nodes, and the priority of the current nodes are higher than the new order, keep going
		// keep moving until the current node priority is lower or there are no more nodes 
		while (node->next != NULL && node->next->priority < priority) {
			node = node->next;
		}
		
		// the temp is placed where the current node is its next is move
		temp->next = node->next;
		// the node moves behind the temp
		node->next = temp;
	}
}

///////////////////////////////////BST/////////////////////////////////////

typedef struct tree_node tree_node;
typedef struct bst bst;

typedef struct tree_node{
	int val;
	tree_node *left;
	tree_node *right;
};

struct bst
{
	tree_node *root;
};

/* Construct the binary search tree */
bst *init_bst()
{
	int (*comparator) (const void* a, const void* b); //a function pointer returnning whether its greater or lesserthan
	calloc(1, sizeof(bst));
}
/* Insert value 'val' into the binary search tree */
void bst_insert(bst *root, int val)
{
	tree_node* new_node = calloc(1, sizeof(tree_node));
	
	while(root != NULL){
		// if (comparator(val, root->val) <= 0){
		if (val <= root->val){
			// if the left value is empty then set it to the new node
			if (root->left == NULL){
				root->left = new_node;
				break;
			}
			// otherwise continue seaching down the left tree
			else {
				root = root->left;
			}
		}

		else if (val > root->val) {
			if (root->right == NULL){
				root->right = new_node;
				break;
			}
			else {
				root = root->right;
			}
		}
	}
}
/* Return 1 if the target value in the binary search tree exists otherwise 0 */
int bst_exists(bst *root, int target)
{
	while (root != NULL){
		if (target == root->val)
			return 1;

		if (target <= root->val)
			root = root->left;
		
		else 
			root = root->right;
	}

	return 0;
}

void recursive_free(tree_node* cur){
	if (cur == NULL)
		return;
	
	// keep calling on the left and right until it hits the bottom, then starts freeing from the ground up
	recursive_free(cur->left);
	recursive_free(cur->right);
	free(cur);
}

/* Destroy the binary search tree */
void destroy_bst(bst *root)
{
	if (root == NULL)
		puts("nothing to destroy");
	else {
		if (root->root == NULL)
			recursive_free(root->root);

		// free the actual
		free(root);
	}
}

