#include<stdlib.h>
#include<stdio.h>
//Deletion with Binary Search Tree
/*
Input : File Name from command line
Text : i(insert) or s(search) or d(delete) + space + #
Output : Status of each line
	 All same from eighth.c - Binary Search Tree
	 Also success or fail if deletion
*/
//ADD DELETE
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
int delete_node(int num);
struct treeNode* searchForDelete(int num);
struct treeNode* minValForDelete(struct treeNode*);

struct treeNode* minValForDelete(struct treeNode* deleteNode){

	struct treeNode* ptr = deleteNode->right;
	while(ptr->left!=NULL){
		ptr = ptr ->left;
	}
	return ptr;
}

struct treeNode* searchForDelete(int num){
	//int height = 1;
	struct treeNode *ptr = root;
	struct treeNode* prev = NULL;
	while(ptr != NULL){
		if(ptr->value == num){

			if(prev == NULL){

				return root;
			}
			else{
				return prev; //found
			}
		}
		prev = ptr;
		if(num < ptr->value){
			//if(ptr->left != NULL){
				ptr = ptr->left;
			/*}
			else{
				ptr = NULL;
				return ptr;
			}*/
		}else{
			//if(ptr->right !=NULL){
				ptr = ptr->right;
			/*}else{
				ptr = NULL;
				return ptr;
			}*/
		}
	}
	//printf("HIIIIIIII");
	ptr = NULL; //NULL if ABSENT
	return ptr;
}

int delete_node(int num){ //what happens to height after deletion?
	int side = 0;
	int answer;
	struct treeNode* searchPREV = searchForDelete(num);
	struct treeNode* ptr;
	//if(searchPREV == NULL && searchPREV->right == NULL && searchPREV->left == NULL){
	if(searchPREV == NULL){
		//printf("fail\n"); //could not find node to delete
		answer = 0; //FAIL = 0
		return answer;
	}else{
		if(searchPREV->left != NULL && searchPREV->left->value == num){ 
			side = 0; //left
			ptr = searchPREV->left;
		}else if(searchPREV->right != NULL && searchPREV->right->value == num) {
			side = 1; //right
			ptr = searchPREV->right; //set ptr equal to actual node
		}else{
			ptr = searchPREV; //no children
		}
		//actual deletion
		if(ptr->right == NULL && ptr->left == NULL){
			if(side == 0){ //if node to be deleted is a left with no children
				searchPREV->left = NULL;
			}
			else{
				searchPREV->right = NULL;
			}

		}else if(ptr->right != NULL && ptr->left == NULL){ //1 child - left
			if(searchPREV->value < ptr->right->value){
				searchPREV -> right = ptr -> right;
			}
			else if(ptr == root){ //if root
				root = ptr->right;
			}
			else{
				searchPREV->left = ptr->right;
			}
		}
		else if(ptr->right == NULL && ptr->left != NULL){ //1 child - right
			if(searchPREV->value < ptr->left->value){
				searchPREV->right = ptr->left;
			}
			else if(ptr == root){ //if root
				root = ptr->left;
			}
			else{
				searchPREV->left = ptr->left;
			}
		}
		else{ //2 children
			//remember to write case for if need to delete root
			struct treeNode* temp = ptr;
			struct treeNode* deleteNode = minValForDelete(ptr);
			int insertionValue = deleteNode->value;
			delete_node(deleteNode->value);
			temp->value = insertionValue;
			answer = 1; //success!!!!
		}

	}
	return answer;
}

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
		//printf("Command: %c\n", command);
		
		if(command == 'i'){
			insert(num);
		}else if(command == 's'){
			search(num);
		}else{
			int answer = delete_node(num);
			if(answer == 0){
				printf("fail\n");
			}
			else{
				printf("success\n");
			}
			
		}

		fscanf(fp, "%c\n", &command);
	}
	fclose(fp);
	//print_tree(root);
	free_tree(root);
	return 0;
}
