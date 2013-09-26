#include <stdio.h>
#include <stdlib.h>

struct student
{
	int id;
	int exam1;
	int exam2;
	char name[16];
	struct student *next;
}typedef student;

//global declaration of struct so I can add nodes anywhere locally
struct student *array[13];

	char operator;
	int id;
	int exam1;
	int exam2;
	char *name[16];

void lookup(int ID)
{
	int hash = ID % 13;
	struct student *ptr = array[hash];
	int not_found = 0;

	while (ptr != NULL)
	{
		if (ptr->id == ID)
		{
			printf("ID already exists");
			not_found = 1;
		}

		ptr = ptr->next;

	}
	if (not_found){
		printf("ID: %d is not found.\n", ptr->id);
	}
	return;
}

void insert(int hash, int ID, int exam1, int exam2, char student[16])
{
	struct student *tail = array[hash];
	struct student *prev = NULL;

	while (tail->next!=NULL)
	{
		if (tail->id==ID)
		{
			printf("Student is already in the list!");
			return;
		}
		prev = tail;
		tail=tail->next;
	}

	/*now we are at the tail of the list*/

	struct student *stu = malloc(sizeof(struct student));

	stu->id = ID;
	stu->exam1 = exam1;
	stu->exam2 = exam2;
	*stu->name = student;
	prev->next = stu;

	printf("Record added. ID: %d, Exam 1:%d, Exam 2: %d, Name: %s\n", stu->id, stu->exam1, stu->exam2,stu->name);
	return;
}

void print_ht()
{
	int j;
	for (j=0;j<13;j++){

		struct student *ptr=array[j];

		while(ptr!=NULL)
		{
			printf("ID: %d, Exam 1:%d, Exam 2: %d, Name: %s\n", ptr->id, ptr->exam1, ptr->exam2,ptr->name);
			ptr = ptr->next;
		}
		printf("End of List.\n");
	}
	return;
}

void delete(int hash, int ID){

	struct student *stu = NULL;
	struct student *linkedlist = array[hash];

	while (linkedlist != NULL)
	{
		if (stu->id == ID)
		{
			if (stu==array[hash]){ array[hash]=stu->next;}
			stu->next = linkedlist->next;
			free(linkedlist);
			linkedlist = NULL;

			printf("Student Record with ID %d Deleted.\n", ID);
			return;
		}
		stu = linkedlist;
		linkedlist = linkedlist->next;
	}
	printf("Student ID not located: %d.\n", ID);
}

int main() 
{
	while(scanf("%s %d %d %d %s", &operator, &id, &exam1, &exam2, &name) != EOF) 
	{
		int hash = id % 13;
		if (operator == 'i') 
		{
			insert(hash, id, exam1, exam2, name);
		}
		else if (operator == 'd')
		{
			delete(hash, id);
		}
		else if (operator == 'l')
		{
			lookup(id);
		}
		else if (operator == 'p')
		{
			print_ht();
		}
	}
	return 0;
}
