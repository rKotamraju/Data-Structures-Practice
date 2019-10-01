#include<stdlib.h>
#include<stdio.h>
//Matrix Squares
/* Input: File as command line input
   Text: First Line - size of matrix (one number since 
	 	      nxn
	Second Line - row 1 separated by spaces
	Third Line - row 2 separated by spaces etc
   Output: Magic or Not Magic
*/
//FIX COLUMNS
int main(int argc, char** argv){
	FILE* fp = fopen(argv[1],"r");
	if(fp==NULL){
		printf("file does not exist\n");
		exit(0);
	}
	int num = 0;
	//Now read the first line in the file
	if(fscanf(fp, "%d\n", &num) == EOF){
		printf("empty file\n");
		exit(0);
	}
	//check rows
	int originalNum = num;
	int counter = 0;
	int i = 0;
	int temp;
	int firstSum = 0;
	while(counter < originalNum){
		int sum = 0;
		while(i < num){
			fscanf(fp, "%d\n", &temp);
			sum = sum + temp;
			i++;
		}
		if(counter == 0){
			firstSum = sum;
		}
		if(sum != firstSum){
			printf("not-magic\n");
			exit(0);
		}
		counter ++;	
		num = num + originalNum;
	}
	fclose(fp);

	FILE* read = fopen(argv[1],"r");
	//now read first line
	int arrayNum;
	if(fscanf(read,"%d\n", &arrayNum)==EOF){
		printf("Empty file");
		exit(0);
	}
	//put in array
	int total = originalNum*originalNum;
	int r = 0;
	int array[total];
	while(r < 9){
		fscanf(read, "%d\n", &arrayNum);
		array[r] = arrayNum;
		//printf("%d\n", array[r]);
		r++;
	} 
	
	//check for unique numbers
	int k = 0;
	for(int i = 0; i < total; i++){
		k = i+1;
		while(k < total){
			if(array[i] == array[k]){
				printf("not-magic\n");
				exit(0);
			}
			else{
				k++;
			}
		}
	}
	num = originalNum;
	//check columns

	int j = 0;
	counter = 0;
	while(counter < originalNum){
		int sum = 0;
		while(j < total){
			sum = sum + array[j];
			//printf("columns\n");
			//printf("%d\n", array[j]);
			j=j+originalNum;
		}
		if(sum != firstSum){
			printf("not-magic\n");
			exit(0);
		}
		counter++;
		j = counter;
	}
	
	num = originalNum;
	//check diagonals
	//right to left diagonal
	counter = 0;
	int m = num -1;
	int sumRightDiag = 0;
	while(counter < originalNum){
		sumRightDiag = sumRightDiag + array[m];
		m = m + (num - 1);
		counter++;
	}
	if(sumRightDiag != firstSum){
		printf("not-magic\n");
		exit(0);
	}
	

	//left to right diagonal
	counter = 0;
	int s = 0;
	int sumLeftDiag = 0;
	while(counter < originalNum){
		sumLeftDiag = sumLeftDiag + array[s];
		s = s + (num + 1);
		counter++;
	}
	if(sumLeftDiag != firstSum){
		printf("not-magic\n");
		exit(0);
	}
	fclose(read);

	printf("magic\n");

	return 0;
}