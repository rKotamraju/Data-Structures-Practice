#include<stdlib.h>
#include<stdio.h>
//Hashtable - 1000 buckets
//Hashfunction : key % buckets
//Input : File name from command line
//Text : i(insert) or s(search) + space + number
//Output : status of each line (inserted, present, duplicate, absent)

struct node{
	int data;
	struct node *next;
};

struct node* array[1000];


void insert(int);
void search(int);

void insert(int insertNumber){ //print inserted or duplicate
	int hashInsert;
	if(insertNumber < 0){
		hashInsert = insertNumber*(-1);
	}
	else{
		hashInsert = insertNumber;
	}

	int hashfunction = hashInsert % 1000;
	struct node* temp = array[hashfunction];
	struct node* insertionNode = malloc(sizeof(struct node));

	while(temp->next!=NULL && temp->data != insertNumber){
		temp = temp->next;
	}
	if(temp == NULL && temp->next == NULL){ //no duplicates - must insert at head
		insertionNode->data = insertNumber;
		insertionNode->next = NULL;
		array[hashfunction] = insertionNode;
		printf("inserted\n");
	}
	else if(temp->data == insertNumber) {
		printf("duplicate\n");
	}
	else{
		insertionNode->data = insertNumber;
		insertionNode->next = NULL;
		temp->next = insertionNode;
		printf("inserted\n");
	}
}

void search(int searchNumber){ //prints present or absent
	//printf("SEARCH METHOD\n");
	int hashNumber;
	if(searchNumber < 0){
		hashNumber = searchNumber * (-1);
	}
	else{
		hashNumber = searchNumber;
	}
		
	int hashfunction = hashNumber%1000;
	struct node* temp = array[hashfunction];
	int answer = 0;

	while(temp!=NULL){
		//printf("SEARCH WHILE LOOP\n");
		if(temp->data == searchNumber){
			answer = 1;
			//printf("if statement\n");
			temp = temp->next;
		}else{
			temp = temp->next;
			//printf("else statement\n");
		}
	}

	if(answer == 1){
		printf("present\n");
	}
	else{
		printf("absent\n");
	}
}

int main(int argc, char** argv){

	for(int i = 0; i < 1000; i++){
		array[i] = malloc(sizeof(struct node));
	}
	//printf("%d\n", array[0]->data);
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("file does not exist\n");
		exit(0);
	}

	char command;
	int num;
	fscanf(fp, "%c\n", &command);
	int zeroCounter;
	while(fscanf(fp, "%d\n", &num) != EOF){

		if(num == 0){
			if(command == 'i'){
				if(zeroCounter == 0){
					insert(num);
					zeroCounter++;
				}else{
					printf("duplicate\n");
				}
			}else{
				if(zeroCounter == 0){
					printf("absent\n");
				}
				else{
					printf("present\n");
				}
			}
		}
		else{
				
			if(command == 'i'){
				insert(num);
			}
			else{
				search(num);
			}
		}

		fscanf(fp, "%c\n", &command);
	}

	fclose(fp);

	return 0;
}