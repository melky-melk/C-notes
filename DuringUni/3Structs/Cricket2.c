# include<stdio.h>

typedef struct BatterClass{
	char firstName[30];
	char lastName[30];
	int runs;
} allBatters[10], Batter;
// allBatters is initialised make memory room for 100 batters
// batter can now be used for shorthand instead of strict BatterClass 

void printBatter(struct BatterClass batter);

int main(){
	// char firstName[30];
	// char lastName[30];
	Batter allBatters[10];
	int runs;

	for (int i = 0; i < 10; i++){
		printf("Enter Name and Score for batter %d: ", i + 1);

		Batter batter;
		scanf("%s", batter.firstName); scanf("%s", batter.lastName); scanf("%d", &batter.runs);

		allBatters[i] = batter;
	}

	for (int i = 0; i < 1; i++){
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
*/