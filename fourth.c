#include<stdlib.h>
#include<stdio.h>
//Matrix Multiplication
/*Input : File Name
  Text : First line - # of rows and columns
	 Numbers in row 1 next, separated by spaces
	 Numbers in row 2 next, etc
	 Followed by second matrix in same format
  Output : Output matrix in same format, without 
	   specifying dimensions
*/
//remember to check tabs at end
int** allocate_matrix(int, int);
void free_matrix(int, int, int**);

int** allocate_matrix(int rows, int columns){
	int** returnValue = malloc(rows*sizeof(int*));
	for(int i = 0; i < rows; i++){
		returnValue[i] = malloc(columns * sizeof(int));
	}
	return returnValue;
}

void free_matrix (int rows, int columns, int** matrix){
	for(int i = 0; i < rows; i ++){
		free(matrix[i]);
	}
	free(matrix);
}

int main(int argc, char** argv){
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("File does not exist\n");
		exit(0);
	}
	//Store first matrix's rows and columns
	int firstRow = 0;
	fscanf(fp, "%d\n", &firstRow);
	//printf("%d\n", firstRow);
	
	int firstColumn = 0;
	fscanf(fp, "%d\n", &firstColumn);
	//printf("%d\n", firstColumn);
	
	//Store second matrix's rows and columns
	int counter = 0;
	int temp;
	while(counter < (firstColumn*firstRow)){
		fscanf(fp, "%d\n", &temp);
		counter ++;
	}
	
	int secondRow = 0;
	fscanf(fp, "%d\n", &secondRow);
	//printf("%d\n", secondRow);

	int secondColumn = 0;
	fscanf(fp,"%d\n", &secondColumn);
	//printf("%d\n", secondColumn);
	
	fclose(fp);
	//if matrices cannot be multiplied
	if(firstColumn != secondRow){
		printf("bad-matrices\n");
		exit(0);
	}
	
	//Stores matrices in arrays
	FILE* read = fopen(argv[1], "r");
	
	int** firstMatrix;
	firstMatrix = allocate_matrix(firstRow, firstColumn);

	int** secondMatrix;
	secondMatrix = allocate_matrix(secondRow, secondColumn);

	counter = 0;
	while(counter < 2){
		fscanf(read, "%d\n", &temp);
		counter ++;
	}
	//populate first matrix
	for(int i = 0; i < firstRow; i ++){
		for(int j = 0; j < firstColumn; j++){
			fscanf(read, "%d\n", &firstMatrix[i][j]);
	//		printf("%d ", firstMatrix[i][j]);
		}
	//	printf("\n");
	}

	counter = 0;
	while (counter < 2){
		fscanf(read, "%d\n", &temp);
		counter++;
	}

	//populate second matrix
	for(int i = 0; i < secondRow; i++){
		for(int j = 0; j < secondColumn; j++){
			fscanf(read, "%d\n", &secondMatrix[i][j]);
	//		printf("%d ", secondMatrix[i][j]);
		}
	//	printf("\n");
	}
	//multiply 
	//int answerMatrix[firstRow][secondColumn];
	int** answerMatrix;
	answerMatrix = allocate_matrix(firstRow, secondColumn);

	//populate answer matrix with 1s

	for(int i = 0; i < firstRow; i ++){
		for(int j = 0; j < secondColumn; j++){
			answerMatrix[i][j] = 0;
		}
	}
	
	int tempSum = 0;
	for(int i = 0 ; i < firstRow; i++){
		for(int j = 0; j < secondColumn; j++){
			for(int s = 0; s < secondRow; s++){
				tempSum = firstMatrix[i][s]*secondMatrix[s][j];
				answerMatrix[i][j] = answerMatrix[i][j] + tempSum;
			}
		}
	}

	//print
	//int rowCounter = 0;
	for(int i = 0; i < firstRow; i++){
		for(int j = 0; j < secondColumn; j++){
			//if(rowCounter == firstRow-1){
			//	printf("%d", answerMatrix[i][j]);
			//}else{
				printf("%d	", answerMatrix[i][j]);
			//}
			//rowCounter++;
		}
		printf("\n");
	}

	free_matrix(firstRow, firstColumn, firstMatrix);
	free_matrix(secondRow, secondColumn, secondMatrix);
	free_matrix(firstRow, secondColumn, answerMatrix);
	return 0;
}