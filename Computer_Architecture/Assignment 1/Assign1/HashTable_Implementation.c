#include <stdio.h>
#include <stdlib.h>

struct student{

	int id;

	int exam1;

	int exam2;

	char name[16];

	struct student *next;

}student;

struct student *array[13]={NULL};

void lookup(int ID){

	int hashcode;

	hashcode = ID * 17;/*using 17 because it is a prime number */

	struct student *ptr = array[hashcode];/* point to the start of the array */

	int not_found=0;



	while (ptr!=NULL){

		if (ptr->id==ID){

			printf("ID is already in the list.\n ID: %d, Exam 1:%d, Exam 2: %d, Name: %s\n", ptr->id, ptr->exam1, ptr->exam2,ptr->name);

			not_found=1;/*change boolean to 1*/

		}

		ptr=ptr->next;

	}



	if (not_found){/*since not found is true*/

		printf("ID: %d is not found.\n", ptr->id);

	}

	return;

}



void add_item(int hashcode, int ID, int exam1_score, int exam2_score, char stu_name[16]){

	struct student *tail=array[hashcode];

	struct student *prev = NULL;



	while (tail->next!=NULL){

		if (tail->id==ID){

			printf("ID is already in the list.\n ID: %d, Exam 1:%d, Exam 2: %d, Name: %s\n", tail->id, tail->exam1, tail->exam2,tail->name);

			return;

		}

		prev=tail;

		tail=tail->next;

	}

	/*now we are at the tail of the list*/

	struct student *stu = malloc(sizeof(struct student));

	stu->id=ID;

	stu->exam1=exam1_score;

	stu->exam2=exam2_score;

	*stu->name=stu_name;

	prev->next=stu;

	printf("Record was added successfully. ID: %d, Exam 1:%d, Exam 2: %d, Name: %s\n", stu->id, stu->exam1, stu->exam2,stu->name);

	return;

}



void print_array(){

	int j;/*declare the variable*/

	for (j=0;j<13;j++){

		struct student *ptr=array[j];/*iterate through array*/

		while(ptr!=NULL){

			printf("ID: %d, Exam 1:%d, Exam 2: %d, Name: %s\n", ptr->id, ptr->exam1, ptr->exam2,ptr->name);/*print*/

			ptr=ptr->next;/*move the pointer*/

		}

		printf("End of List.\n");

	}

	return;

}



void delete_item(int hashcode, int ID){

	struct student *stu = NULL;

	struct student *linkedlist=array[hashcode];



	while (linkedlist!=NULL){/*check the list*/

		if (stu->id==ID){/*find the student*/

			if (stu==array[hashcode]){/*verify hashcode*/

				array[hashcode]=stu->next;

			}

			stu->next=linkedlist->next;

			free(linkedlist);/*delete and free*/

			linkedlist=NULL;

			printf("ID removed. ID: %d.\n", ID);

			return;

		}

		stu=linkedlist;

		linkedlist=linkedlist->next;/*change the pointer*/

	}

	printf("ID not found. ID: %d.\n", ID);



}

int main() {

	char op[1];

	int input_id;

	int input_exam1;

	int input_exam2;

	char input_name[16];



	while (scanf("%s %d %d %d %s", op, &input_id, &input_exam1, &input_exam2, &input_name) != EOF) {

		int hashcode=input_id*17;

			if (*op =='i'){

				printf("Adding record");

				if (array[hashcode]==NULL){

					struct student *ptr=malloc(sizeof(struct student));

					ptr->id=input_id;

					ptr->exam1=input_exam1;

					ptr->exam2=input_exam2;

					*ptr->name=input_name;

					ptr->next=NULL;

					array[hashcode]=ptr;

					printf("Record was added successfully. ID: %d, Exam 1:%d, Exam 2: %d, Name: %s\n", ptr->id, ptr->exam1, ptr->exam2,ptr->name);

				}

				else{

					add_item(hashcode, input_id,input_exam1,input_exam2,input_name );

				}

			}

			else if (*op=='d'){

				delete_item(hashcode, input_id);

			}

			else if (*op=='l'){

				lookup(input_id);

			}

			else if (*op=='p'){

				print_array();

			}

		}

	return 0;

}


