#include<stdlib.h>
#include<stdio.h>
//Linked List
//Input : File Name from command line
//File : i (insert) or d (delete) + space + number
//Output : first line - how many numbers in list
//	   second line - list in order
//	   error if file does not exist

//Node Structure
struct node{
	int data;
	struct node *next;
};

struct node *head = NULL;
void insert(int);
void print_list();
void free_list();
void delete_list(int);
int checkForDuplicates(int);

void delete_list(int number){
	struct node* temp = head;
	int counter = 0;
	while(temp->data != number){
		temp = temp->next;
		counter++;
	}

	if(counter == 0){
		head = head->next;
	}
	else{
		//if(temp->next == NULL){
			
		struct node* prev = head;
		for(int i = 0; i < counter-1; i++){
			prev = prev->next;
		}
		prev->next = temp->next;
	}
}


void print_list(){
	struct node* temp = head;
	while(temp != NULL){
		printf("%d	", temp -> data);
		temp = temp->next;
	}	
}

void insert(int newData){
	
	struct node* insertionNode = malloc(sizeof(struct node));
	insertionNode->data = newData;
	
	//if have to insert at the beginning
	if(head == NULL){
		head = insertionNode;
	}
	else if(newData < (head->data)){
		insertionNode->data = newData;
		insertionNode->next = head;
		head = insertionNode;
	}else{
		//iterate through linked list
		struct node* temp = head;
		while((temp->next != NULL) && (temp->next->data < newData)){
			temp = temp->next; //mark
		}
	
		insertionNode->next = temp->next;
		temp->next = insertionNode;
	}
	
}

int checkForDuplicates(int data){
	int answer = 0; 
	struct node* temp = head;
	while(temp!=NULL){
		if(temp->data == data){
			answer = 1; //means number is already in list
		}
		temp = temp-> next;
	}
	return answer;

}

void free_list(){
	struct node* temp = head;
	while(temp != NULL){
		struct node* temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
}

int main(int argc, char** argv){
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error");
		exit(0);
	}

	int numberOfNodes = 0;
	char command;
	if(fscanf(fp, "%c\n", &command) == EOF){
		printf("0\n");
		exit(0);
	}
	
	int numberData;	//works till here	
	while(fscanf(fp, "%d\n", &numberData) != EOF){
		if(command == 'i'){
			if(checkForDuplicates(numberData) == 0){
				insert(numberData);
				numberOfNodes++;
			}
		}
		else{
			if(checkForDuplicates(numberData) == 1){
				delete_list(numberData);
				numberOfNodes=numberOfNodes-1;
			}
		}
		fscanf(fp, "%c\n", &command);
	}
	fclose(fp);

	printf("%d\n", numberOfNodes);
	print_list();
	return 0;
}

