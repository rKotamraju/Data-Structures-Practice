#include<stdlib.h>
#include<stdio.h>
//Binary Search Tree
/*
Input: File Name from command line - can be blank
       i(insert) or s(search) + space + number
Rules : Node must be greater than left subnode and less than right subnode. Must dynamically allocate 		and free space at end.
Output: Status of each line
	- error = file does not exist
	- inserted + space + height of inserted node at 
	  tree
	- duplicate = already there, can't be inserted
	- present + space + height of node
	- absent - not there so can't find
*/

//DONT FORGET TO FREE
struct treeNode{
	int value;
	struct treeNode* left;
	struct treeNode* right;

};

struct treeNode *root = NULL; //intialize root

void free_tree(struct treeNode*);
void insert(int num);
void search(int num);
void print_tree(struct treeNode*);
struct treeNode* allocateNode(int value);

struct treeNode* allocateNode(int value){ //allocate memory for nodes

	struct treeNode* temp = malloc(sizeof(struct treeNode));
	temp->value = value;
	temp->left = NULL;
	temp->right = NULL;
	return temp;

}

void free_tree(struct treeNode* root){
		if(root == NULL){
			return;
		}
		free_tree(root->left);
		free_tree(root->right);
		free(root);

}

void print_tree(struct treeNode* root){
	if(root==NULL){
		return;
	}
	printf("Value: %d\n", root->value);
	print_tree(root->left);
	print_tree(root->right);

}

void insert(int num){
	int height = 1;
	struct treeNode *temp = allocateNode(num);
	//printf("temp value: %d\n", temp->value);
	struct treeNode *prev = NULL;
	struct treeNode *ptr = root;

	while(ptr != NULL){ //search for place to insert
		if(ptr->value == num){
			printf("duplicate\n");
			return;
		}

		prev = ptr;
		
		if(ptr->value > num){
			ptr = ptr->left;
		}
		else{
			ptr = ptr->right;
		}
		height++;
	} 
		
	if(prev == NULL){
		root = temp;
		height = 1;
		printf("inserted %d\n", height);
		return;
	}
	else if(num < prev->value){
		prev->left = temp;
	}
	else{
		prev->right = temp;
	}
	
	ptr = temp;

	printf("inserted %d\n", height);

}

void search(int num){
	int height = 1;
	struct treeNode *ptr = root;
	while(ptr != NULL){
		//printf("ptr value: %d\n", ptr->value);
		/*if(ptr->left->value == NULL){
			printf("NULL\n");
		}*/
		//printf("ptr left : %d\n", ptr->left->value);

		if(ptr->value == num){
			printf("present %d\n", height);
			return;
		}

		if(num < ptr->value){
			ptr = ptr->left;
			
		}else{
			ptr = ptr->right;
			
		}
		height++;
	}
	printf("absent\n");
}

int main(int argc, char** argv){
	//Read File
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error");
		exit(0);
	}

	int num;
	char command;

	if(fscanf(fp, "%c\n", &command) == EOF){
		printf("Empty File\n");
		exit(0);
	}

	while(fscanf(fp, "%d\n", &num) != EOF){
		
		if(command == 'i'){
			insert(num);
		}else{
			search(num);
		}

		fscanf(fp, "%c\n", &command);
	}
	fclose(fp);
	//print_tree(root);
	free_tree(root);
	return 0;


}