#include <stdio.h>
#include <stdlib.h>

int countVowels(char *string);

int main(){
    char *str = NULL;
    str = (char *) malloc (50 * sizeof(char));

	while (*str){

        if (*str == 'a' || *str == 'e' || *str == 'i' || *str == 'o' || *str == 'u'){
            vowelCounter++;
        }
        else {
            consonantCounter++;
        }

        vowels = startOfVowels;
        str++;
    }

    printf("Number of vowels : %d\n", vowelCounter);
    
    return 0;   
}

/*
I WAS TRYING TO FAMILIARISE MYSELF BUT THIS IS A STUPID SOLUTION

printf("Input a string: ");
scanf("%s", str);

char * vowels = "aeiou"; 
char * startOfVowels = vowels;
int vowelCounter = 0;

//its like while string != NULL
while (*str){

	while (*vowels){
		if (*str == *vowels++){
			vowelCounter++;
		}
	}

	vowels = startOfVowels;
	str++;
}
*/