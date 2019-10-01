#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//Pig Latin 
/*
Input: String of space separated words
Output: Pig Latin
Rules : If word starts with a vowel, add "yay" to the end
If word starts with a consonant, take all letters up to first vowel and put at end then add "ay" to the end
*/

int main(int argc, char**argv){

	for(int i = 1; i < argc; i++){ //loops through words
		if(argv[i][0] == 'a' || argv[i][0] == 'e' || argv[i][0] == 'o' || argv[i][0]=='i' || 			argv[i][0] == 'u' || argv[i][0] == 'A' || argv[i][0] == 'E' || argv[i][0] == 'O' || 			argv[i][0] == 'I' || argv[i][0] == 'U'){
			//remember to take into account uppercase vowels too
			printf("%s", argv[i]);
			printf("yay ");
		}else{

			int j = 0;
			while ((argv[i][j]!='o') && (argv[i][j]!='a') && (argv[i][j]!='i') && (argv[i][j]!='e')&&(argv[i][j]!='u')&&(argv[i][j]!='O')&&(argv[i][j]!='A')&&(argv[i][j]!='I')&&(argv[i][j]!='E')&&(argv[i][j]!='U')) {
					j++;
			}
			for(int c = j; c < strlen(argv[i]); c++){
				printf("%c", argv[i][c]);
			} //print letters after first vowel
			for(int a = 0; a < j; a++){
				printf("%c", argv[i][a]); //move beginning to end
			}
			printf("ay "); 
		}
	
	}
	return 0;

}