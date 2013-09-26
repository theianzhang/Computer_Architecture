#include <stdio.h>  /* include to find declaration of printf */
#include <stdlib.h> /* include to find declaration of malloc */
#include <stdbool.h> /*include to find declaration of bool */ 

struct node {
  
  int me;
  struct node * next;
};

/* Very important global information: the head of the list.
 *  *
 *   * */
struct node *head = NULL;

void bubble_sort(struct node *head)
{
	//this checks if the entire linked list has been sorted, as opposed to iterated through just once
	bool isSorted = false;
	while (!isSorted) 
	{
		//point to head of linked list at beginning of each iteration
		struct node * ptr = head;
		isSorted = true;
		
		//bubble sort algorithm
		while (ptr->next != NULL & ptr != NULL)
		{
			if (ptr->me > (ptr+1)->me)
			{
				int temp = ptr->me;
				ptr->me = (ptr+1)->me;
				(ptr+1)->me = temp;
				isSorted = false; 
			}
			ptr = (ptr+1);
		}
	}		
}

int main()
{
  struct node *ar;
  struct node *p;
  int k;

  ar = (struct node *) malloc(10*sizeof(struct node));

  p = ar;

  for (k = 0; k < 9; k++)
    {
      p->me = rand() % 100;
      p->next = ar + k + 1;
      p++;
    }
   p->me = 9;
   p->next = NULL;

   p = &ar[0];

	/* 
	* If the head of the list is NULL reallocate memory for the list. */
	if (head == NULL){
		head = malloc(sizeof(struct node));
		head->me = -1;
		head->next = NULL;
	}// endif
  
   while (p != NULL) {
	   printf("Pre-Sort: %d 0x%lx 0x%lx\n", \
			   p->me, (unsigned long) p, (unsigned long) p->next);
	   p = p->next;
   }
   
   bubble_sort(&ar[0]); 
   
   p = &ar[0];
   
   while (p != NULL) {
	   printf("Post-Sort: %d 0x%lx 0x%lx\n", \
			   p->me, (unsigned long) p, (unsigned long) p->next);
	   p = p->next;
   }

   return(0);
}
