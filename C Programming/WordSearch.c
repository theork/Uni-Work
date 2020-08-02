#include <time.h>
#include <stdio.h>
#include <string.h>

/*
 * Title: Word Search
 * Author: Theo Rook
 * Date: 24/04/18
 * 
 * A wordsearch game that creates and plays a wordsearch in a set time from a set of words
 */

//change the size of the board
#define WIDTH 20
#define HEIGHT 20
//change length of time player has to complete puzzle
#define TIME 120

char** create2DArray();
char** populate2DArray(char ** array, char replace);
void printArray(char** array);
void insertHorizontally(char* word, char** array, char** mask);
void insertVertically(char* word, char** array, char** mask);
void insertDiagonally(char* word, char** array, char** mask);

//creating the two 2D arrays
char** grid;
char** mask;

mainMenu(){
	//words to find
	char *planets[8] = {"MERCURY", "VENUS", "EARTH", "MARS", "JUPITER", "SATURN", "URANUS", "NEPTUNE"};
	char *animals[8] = {"CAT", "DOG", "PIG", "SHEEP", "HORSE", "DOLPHIN", "AARDVARK", "HAMSTER"};
	char *programLanguages[8] = {"PYTHON", "JAVA", "JAVASCRIPT", "BASIC", "MATLAB", "HTML", "SQL", "ASSEMBLY"};
	
	//seeds random function with time
	srand(time(NULL));	
	
	//welcomes user and asks for input 
	printf("WORD SEARCH");
	printf("\n************");
	printf("\n\nCategories");
	printf("\n**********");
	printf("\n1 - Planets\n2 - Animals\n3 - Programming Languages");
	
	printf("\n\nWhat category of words would you like? ");
	int option;
	scanf("%d", &option); getchar();
	//clear screen
	system("cls");
	
	//finds what option the user picked and assigns the set to 'words'
	char *(*words)[8];
	switch(option){
		case 1:
			words = &planets;
			break;
		case 2:
			words = &animals;
			break;
		case  3:
			words = &programLanguages;
			break;
		default:
			//exits the program
			printf("\nInvalid input\n");
			return 0;
			
	}
	
	//creates and populates the arrays
	grid = create2DArray();
	grid = populate2DArray(grid, '.');
	mask = create2DArray();
	mask = populate2DArray(mask, 0);
	
	int i;
	//puts each word into grid in a random orientation
	for(i = 0; i < 8; i ++){
		int rng = rand() % 3;
		if (rng == 0){
			insertHorizontally((*words)[i], grid, mask);		
		}
		
		else if (rng == 1){
			insertVertically((*words)[i], grid, mask);	
		}
		
		else if (rng == 2){
			insertDiagonally((*words)[i], grid, mask);
		}
	}
	
	
	int complete = 0;
	int correct = 0;
	float seconds = 0;
	char guess[30] = "";
	//array to find if each item has already been picked
	int guesses[8] = {0};
	//starts a timer
	clock_t start = clock();
	
	//loops until all words have been found or the player runs out of time
	while (complete == 0 && seconds < TIME){
		printf("\n");
		printArray(grid);
		printf("\nGuess a word: ");
		scanf("%s", &guess);
		//clears the screen
		system("cls");
		
		//converts the user input to uppercase
		for(i = 0; i < strlen(guess); i++){
			guess[i] = toupper(guess[i]);
		}
		
		//for finding out if input is wrong
		int found = 0;
		int prev = correct;
		
		for(i = 0; i < 8; i++){
			//compares the user input with each item in the chosen word set
			if (strcmp(guess, (*words)[i]) == 0){
				//checks if the user has already found this item
				if (guesses[i] == 1){
					printf("You've already found this");
					found = 1;
					break;
				}
				printf("Correct guess!");
				correct++;
				guesses[i] = 1;
				break;
			}
		}
		
		//finds if the input is wrong
		if (prev == correct && found == 0){
			printf("WRONG!");
		}
		
		//breaks loop if all 8 words have been found
		if(correct == 8){
			complete = 1;
		}
		
		//finds the end time
		clock_t end = clock();
		//converts time to seconds
		seconds = (float) (end - start) / CLOCKS_PER_SEC;
		
	}
	
	if(complete == 1){
		printf("\n\nCONGRATUALTIONS!!");
		printf("\nYou managed to complete the word search in %.2f seconds", seconds);
	}
	else{
		printf("\n\nYou have run out of time, better luck next time.");
	}
	
	//clears allocated memory
	free(grid);
}

//allocates space for a 2D array
char** create2DArray(){
	int i, j;
	char **array = (char**) malloc(sizeof(char*) * WIDTH);
	
	for(i = 0; i < WIDTH; i++){
		array[i] = (char*) malloc(sizeof(char) * HEIGHT);
	}
	
	return array;
}

//populates a 2D array with a character 
//if the character is '#', random letters will be placed
char** populate2DArray(char ** array, char replace){
	char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int i, j;
	
	for(i = 0; i < WIDTH; i++){
		for(j = 0; j < HEIGHT; j++){
			if (replace == '#'){
				int rng = rand() % 25;
				array[i][j] = letters[rng];			
			}
			else{
				array[i][j] = replace;
			}
			
		}
	}
	return array;	
}

//displays the 2D array to the user
void printArray(char** array){
	int i,j;
	for(i = 0; i < WIDTH; i++){
		for(j = 0; j < HEIGHT; j++){
			printf(" %c ", array[i][j]);
		}
		printf("\n");
	}
}

//finds a place and inserts a word horizontally into the grid
void insertHorizontally(char* word, char** array, char** mask){
	int x, y, i, valid;
	int validPosition = 0;
	//finds the length of the word
	int len = strlen(word);
	int count = 0;
	
	//loops until a position is found for the word
	while(validPosition == 0){
		//finds random coordinates in the grid
		//x only finds coordinates that the end position will fit
		x = rand() % (WIDTH - (len - 1));
		y = rand() % HEIGHT;
		
		valid = 0;
		
		//iterates grid to the length of the word
		for(i = 0; i < len; i++){
			//finds if a position is invalid and breaks loop to try again with new numbers
			if(mask[y][x+i] == 1){				
				break;
			}
			else{
				valid++;
			}		
		}
		
		//if a position is found that is the length of the word, while loop = true
		if (valid == len){
			validPosition = 1;
		}
		
		//prevents infinate loop  if there is no valid position
		count++;
		if(count > 10000){
			printf("ERROR - cannot find position for word, restart.");
			//closes program
			exit(1);
		}
	}
	
	for(i = 0; i < len; i++){
		//inserts word into the grid
		array[y][x+i] = word[i];
		//inserts 1's into mask to the length of the word
		mask[y][x+i] = 1;
	}
	
}

//finds a place and inserts a word vertically into the grid
void insertVertically(char* word, char** array, char** mask){
	int x, y, i, valid;
	int validPosition = 0;
	//finds the length of the word
	int len = strlen(word);
	int count = 0;
	
	//loops until a position is found for the word
	while(validPosition == 0){
		//finds random coordinates in the grid
		//y only finds coordinates that the end position will fit
		x = rand() % WIDTH ;
		y = rand() % (HEIGHT- (len - 1));
		
		valid = 0;
		
		//iterates grid to the length of the word
		for(i = 0; i < len; i++){
			//finds if a position is invalid and breaks loop to try again with new numbers
			if(mask[y+i][x] == 1){				
				break;
			}
			else{
				valid++;
			}			
		}
		
		//if a position is found that is the length of the word, while loop = true
		if (valid == len){
			validPosition = 1;
		}
		
		//prevents infinate loop  if there is no valid position
		count++;
		if(count > 10000){
			printf("ERROR - cannot find position for word, restart.");
			exit(1);
		}
	}
	
	for(i = 0; i < len; i++){
		//inserts word into the grid
		array[y+i][x] = word[i];
		//inserts 1's into mask to the length of the word
		mask[y+i][x] = 1;
	}
}

//finds a place and inserts a word diagonally (up or down) into the grid
void insertDiagonally(char* word, char** array, char** mask){
	int x, y, i, valid;
	//finds the length of the word
	int len = strlen(word);
	int validPosition = 0;
	int count = 0;
	
	//choses direction where 0 = down, 1 = up
	int direction = rand() % 2;
	
	//down
	if (direction == 0){
		
		//loops until a position is found for the word
		while(validPosition == 0){
			//finds random coordinates in the grid
			//x and y only finds coordinates that the end position will fit
			x = rand() % (WIDTH - (len - 1));
			y = rand() % (HEIGHT - (len - 1));
			valid = 0;
			
			//iterates grid to the length of the word
			for(i = 0; i < len; i++){
				//finds if a position is invalid and breaks loop to try again with new numbers
				if(mask[y+i][x+i] == 1){				
					break;
				}
				else{
					valid++;
				}				
			}
			
			//if a position is found that is the length of the word, while loop = true
			if (valid == len){
				validPosition = 1;
			}
			
			//prevents infinate loop  if there is no valid position
			count++;
			if(count > 10000){
				printf("ERROR - cannot find position for word, restart.");
				exit(1);
			}
		}
		
		for(i = 0; i < len; i++){
			//inserts word into the grid
			array[y+i][x+i] = word[i];
			//inserts 1's into mask to the length of the word
			mask[y+i][x+i] = 1;
		}
	}
	
	//up
	else if (direction == 1){
		//loops until a position is found for the word
		while(validPosition == 0){
			//finds random coordinates in the grid
			//x and y only finds coordinates that the end position will fit
			x = rand() % (WIDTH - (len - 1));
			y = (len - 1) + (rand() % (HEIGHT - (len - 1)));
			valid = 0;
			
			//iterates grid to the length of the word
			for(i = 0; i < len; i++){
				//finds if a position is invalid and breaks loop to try again with new numbers
				if(mask[y-i][x+i] == 1){				
					break;
				}
				else{
					valid++;
				}				
			}
			
			//if a position is found that is the length of the word, while loop = true	
			if (valid == len){
				validPosition = 1;
			}
			
			//prevents infinate loop  if there is no valid position
			count++;
			if(count > 10000){
				printf("ERROR - cannot find position for word, restart.");
				exit(1);
			}
		}
		

		for(i = 0; i < len; i++){
			//inserts word into the grid
			array[y-i][x+i] = word[i];
			//inserts 1's into mask to the length of the word
			mask[y-i][x+i] = 1;
		}
	}
}

