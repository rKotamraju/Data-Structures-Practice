#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//String Operations II
/*
Input: String of space separated words
Rules : Take last letter/punctuation from each word and make it one word
Output: Single word
*/
int main(int argc, char** argv){

	for(int i = 1; i < argc; i++){ //loops through words in sentence
		int j = 0;
		while(argv[i][j]!= '\0'){
			j++;
		}
		j--;
		printf("%c", argv[i][j]);
	}
	return 0;
}

