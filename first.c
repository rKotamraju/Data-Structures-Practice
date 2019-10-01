#include<stdlib.h>
#include<stdio.h>

//Trucatable Right Primes
//Input : File Name
//Output : Yes or No for each value in input file

int isPrime(int num); //must declare function isPrime

int main(int argc, char** argv){

		//Read file
		FILE* fp = fopen(argv[1], "r");
		if(fp == NULL){
			printf("file does not exist\n");
			exit(0);
		}
		int num = 0;
		/*Now read the first line in the file */
		if(fscanf(fp, "%d\n", &num) == EOF){
			printf("empty file\n");
			exit(0);
		}
		
		for(int i = 0; i < num; i++){
			int temp;
			fscanf(fp,"%d\n", &temp);
			int final = 0; //yes = prime
			while(temp > 0){
				//printf("Is the number prime?%d\n",isPrime(temp));
				if(temp < 10){
					if(temp == 2 || temp == 5 || temp == 7 || temp == 3){
						final = 1;
					}else{
						final = 0;
					}
					break; //Question : is 1 a prime?
				}				
				else if(isPrime(temp) == 1){
					double divByTen = temp/10;
					int modByTen = temp%10;
					double dec = modByTen/10;
					temp = divByTen-dec;
				}else{
					final = 0; //no
					break;
				}
			}
			//printf("final : %d\n", final);
			if(final == 1){
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
		}
	fclose(fp);
	return 0;
}


int isPrime(int num){
	int prime = 1;//1 = true
	for(int i = 2; i <= num/2; i++){
		if(num % i == 0){
			prime = 0; //0 = false
			break;
		}
	}
	return prime;
}