#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct mystruct{

	int me;
	struct mystruct * next;
}mystruct;

/* Very important global information: the head of the list.
 *  *
 *   * */
struct mystruct *head = NULL;

void add_item(int val){

	/* We create a ptr tail pointing initially to the head of the list */
	struct mystruct * tail = head;
	struct mystruct * prev = NULL;
	/* First we need to lookup in the linked list and check if  *
 * 	 * the item is already in the list 					*/
	while (tail != NULL){

		/* If the value already exists, we just exit */
		if (tail->me == val){
			printf("value %d already exists.\n", val);
			return;
		
		}//endif
		prev = tail;
		tail = tail->next;
	}//endwhile


	/* At this point curr is the pointer with the last item of the linked list.
 * 	 * We also parsed the list and didn't find any node with value val.
 * 	 	 * Which means we can proceed to adding a new node to the end of the list */
	struct mystruct *ptr = malloc(sizeof(struct mystruct));
	/* create the node */
	ptr->me = val;
	ptr->next = NULL;

	/* Add the node to the end of the list */
	prev->next = ptr;
	return;
}

void remove_item(int val){
	
	/* to_del is a pointer which initially points to the head of the list.
 * 	 * After we are done searching this pointer should point to the node we want to delete. */

	/* prev is a pointer to the node exactly before the one we want to delete */
	struct mystruct * to_del = head;
	struct mystruct * prev = NULL;

	/* We need to parse the list and get the item */
	while (to_del != NULL){

		/* This means that we found the correct node */
		if (to_del->me == val){

			/* If the node to remove is the head of the list: */			
			if (to_del == head){
				/* We just make a new head of the list! */
				head = to_del->next;			
			}

			/* If the item to remove has a previous node linked to it
 * 			 * We need to keep the list linked !				*/			
			if (prev != NULL){
				prev->next = to_del->next;

			}

			/* We make the actual delete and return */
			free(to_del);
			to_del = NULL;
			return;
		}//endif
		/* Keep the iteration going */
		prev = to_del;
		to_del = to_del->next;
	}//endwhile
	/* If the while loop ended w/o finding val */
	printf("Item with value %d not found!\n", val);
}

void print_list(){
	
	struct mystruct * ptr = head;
	printf("Printing the linked list:\n");
	while (ptr != NULL){
		
		printf("%d -->  ", ptr->me);
		ptr = ptr->next;
	
	}
	printf("NULL\n");
	return;
}

void bubble_sort()
{
	//this checks if the entire linked list has been sorted, as opposed to iterated through just once
	bool isSorted = false;
	while (!isSorted) 
	{
		//point to head of linked list at beginning of each iteration
		struct mystruct * ptr = head;
		isSorted = true;

		//bubble sort algorithm
		while (ptr->next != NULL & ptr != NULL)
		{
			if (ptr->me > ptr->next->me)
			{
				int temp = ptr->me;
				ptr->me = ptr->next->me;
				ptr->next->me = temp;
				isSorted = false; 
			}
			ptr = ptr->next;
		}
	}		
}

int main(){

	/* Variables where we store each operation from the input file */
	char op[1];
	int val;

	while (scanf("%s %d", op, &val) != EOF) {

		/* 
 * 		 * If the head of the list is NULL reallocate memory for the list.
 * 		 		 */
		if (head == NULL){
			head = malloc(sizeof(struct mystruct));
			head->me = -1;
			head->next = NULL;
		}	// endif
		printf("%s\n", op);
		if (*op == '+') {
			printf("Adding %d\n", val);
			add_item(val);
		}
		if ((strcmp (op, "-") == 0)){
			printf("Removing %d\n", val);
			remove_item(val);
		}
	} // endwhile
	/* Now we want to print the linked list */
	bubble_sort();
	print_list();
}
