# include<stdio.h>
# define LENGTH 4

typedef struct BatterClass{
	char firstName[30];
	char lastName[30];
	int runs;
} allBatters[LENGTH], Batter;
// allBatters is initialised make memory room for 10 batters
// batter can now be used for shorthand instead of strict BatterClass 

void printBatter(struct BatterClass batter);

int main(){
	Batter allBatters[LENGTH];
	int runs;

	for (int i = 0; i < 4; i++){
		printf("Enter Name and Score for batter %d: ", i + 1);

		// checks if the input is within 30s and that there are 3 inputs, otherwise it will not save the data
		Batter batter;
		//an access the string directly because strings are just the pointer to the first
		// for the int, you need to use the pointer because it needs to access the address instead
		if (scanf("%s %s %d", batter.firstName, batter.lastName, &batter.runs) == 3) {
			allBatters[i] = batter;
		}
	}

	for (int i = 0; i < LENGTH; i++){
		printBatter(allBatters[i]);
	}

	return 0;
}

void printBatter(struct BatterClass batter){
	// gets the first character of the name
	printf("%c. %s: %d\n",batter.firstName[0], batter.lastName, batter.runs);
}

/*
melky mlek 8
limey lim 11
beab beabs 24
lemon horse 8

if the variables are in order, then itll just automatically assign to the respective variables
the ones that are there as parameters, it does not need to match the attribute names
Batter batter = {firstName, lastName, runs};

otherwise you can do this
Batter batter = {.name = firstName, .surname = lastName, .run = runs }
*/
