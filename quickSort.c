#include <stdio.h>
#include <stdlib.h>

struct mynode
{
	int value;
	struct mynode *next;
	struct mynode *previous;
};

/* function declarations*/
struct mynode* getTail(struct mynode *current);
struct mynode* insertnode(struct mynode *a, int x);
void sort(struct mynode *list);
struct mynode* quicksort(struct mynode *head, struct mynode *tail);
void print(struct mynode *ptr);

int main() 
{

	/* Creates a null pointer to be the head of the list. */
	struct mynode *head;
	struct mynode *current;
	int x = 1;
	head = NULL;
	
	/*
	Prompts user to enter values and creates nodes for each value entered
	except zero.*/
	printf("Enter a value (0 to exit) : \n");
	while (x != 0){
		scanf("%d", &x);
		if(x == 0){
			break;
		}else if (head == NULL) {
			current = insertnode(head, x);
			head = current;
		}else
			current = insertnode(head, x);
	}
	sort(head);
return 0;
}

void sort(struct mynode *list)
{
	struct mynode *head = list;
	struct mynode *tail = getTail(list);
	struct mynode *sortedList = quicksort(head, tail);
	
	print(sortedList);
}

struct mynode* quicksort(struct mynode *head, struct mynode *tail)
{
	if (head == NULL) {
		return NULL;
	}
	if (head == tail) {
		return head;
	}else{
		struct mynode *pivot = head;
		struct mynode *currentN = head->next;
		struct mynode *temp = NULL;
		struct mynode *rightTail = NULL;
		struct mynode *leftTail = NULL;
		struct mynode *left = NULL;
		struct mynode *right = NULL;
		
		while (currentN != tail) {
			if (currentN->value > pivot->value) {
				if (right == NULL) {
					right = currentN;
					currentN = currentN->next;
					right->next = NULL;
					right->previous = NULL;
				}else{
					rightTail = getTail(right);
					rightTail->next = currentN;
					currentN = currentN->next;
					rightTail->next->next = NULL;
					temp = rightTail->next;
					temp->previous = rightTail;
				}
			}else{
				if (left == NULL) {
					left = currentN;
				//	temp = currentN;
					currentN = currentN->next;
					left->next = NULL;
					left->previous = NULL;
				}else{
					leftTail = getTail(left);
					leftTail->next = currentN;
					currentN = currentN->next;
					leftTail->next->next = NULL;
					temp = leftTail->next;
					temp->previous = leftTail;
				}
			}
		}
		
		
		if (tail->value > pivot->value) {
			if (right == NULL) {
				right = tail;
				right->next = NULL;
			}else{
				rightTail = getTail(right);
				rightTail->next = tail;
				rightTail->next->next = NULL;
				temp = rightTail->next;
				temp->previous = rightTail;
			}
		}else{
			if (left == NULL) {
				left = tail;
				left->next = NULL;
			}else{
				leftTail = getTail(left);
				leftTail->next = tail;
				leftTail->next->next = NULL;
				temp = leftTail->next;
				temp->previous = leftTail;
			}
		}
	
	leftTail = getTail(left);
	rightTail = getTail(right);			
	left = quicksort(left, leftTail);
	right = quicksort(right, rightTail);
	
	if (leftTail != NULL) {
		leftTail = getTail(left);
		temp = leftTail;
		leftTail->next = pivot;
		pivot->previous = temp;
	}		
	if (left == NULL) {
		left = pivot;
	}	
	
	pivot->next = right;
	
	return left;
	}
}

/* Iterates through list and assigns tail to the last node*/
struct mynode* getTail(struct mynode *current) {
	struct mynode *tail; 
	
		if (current == NULL) {
			return current;
		}
	
		while (current->next != NULL) { //iterates through the list until tail is reached.
			current = current->next;
		}
	tail = current;
	return tail;
}

/* Prints out the whole list */
void print(struct mynode *ptr)
{	
    if(ptr == NULL)
    {
        return;
    }
    printf("%d  ",ptr->value);
    print(ptr->next);
}

/* Creates a new node in a list and enters the value into the node*/
struct mynode* insertnode(struct mynode *a, int x)
{
	struct mynode *temp;
	
	if(a == NULL)
	{
		a = malloc(sizeof(struct mynode));	//Sets aside memory for the node.
		a->value = x;
		a->next = NULL;
		a->previous = NULL;
	}else{
		a = getTail(a);
		a->next = malloc(sizeof(struct mynode));
		temp = a;
		a = a->next;
		a->value = x;
		a->next = NULL;
		a->previous = temp;		//doubly links the nodes/list.
	}
	return a;
}
