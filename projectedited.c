#include "project.h"

Game *games = NULL; // Pointer to array of Games is defined to store all the games

int numGames = 0; // integer variable to store the number of Games

// This function gets the command from the user input
char getCommandFromUser(char* inputFromUser) {
 char readCommand[1000];
 strcpy(readCommand, inputFromUser);
 char* command = strtok(readCommand, " ");
 if (strlen(command) == 1) {
 return command[0];
 } else {
 printf("Invalid command %s\n", command);
 return 0;
 }
}

// This function adds a new game to the database
void add(char* input) { 
 char name[1000];
 float price;
 int numberOfArguments = sscanf(input + 2, "%s %f", name, &price);
 
 // check whether numberOfARguments is equal to 2
 if (numberOfArguments!= 2){
 printf("A should be followed by exactly 2 arguments.\n");
 return;
 }
 
 // price cannot be negative
 if (price <= 0) {
 printf("Game price cannot be negative or zero.\n");
 return;
 }
 
 else {
 // To check if the Game is already stored
 for (int i = 0; i < numGames; i++) {
 if (strcmp(name, games[i].name) == 0) {
 printf("Game %s is already in the database.\n", name);
 return;
 }
 }
 
 // If the Game is not already stored, it is added
 games = realloc(games, (numGames + 1) * sizeof(Game));
 games[numGames].name = malloc(strlen(name) + 1);
 strcpy(games[numGames].name, name);
 games[numGames].price = price;
 games[numGames].revenue = 0.0;
 numGames++;
 
 printf("SUCCESS\n");
 }
}
// Function used to buy
void buy(char* input) {
 char name[1000];
 int count;
 int numberOfArguments = sscanf(input + 2, "%s %d", name, &count);
 
 // check whether numberOfARguments is equal to 2
 if (numberOfArguments!= 2){
 printf("B should be followed by exactly 2 arguments.\n");
 return;
 }
 
 // Can only buy positive number of games
 if (count < 1) {
 printf("Number of bought items cannot be less than 1.\n");
 return;
 }
 
 else{
 // check whether Game is in the database
 for (int i = 0; i < numGames; i++) {
 if (strcmp(name, games[i].name) == 0) {
 float revenue = count * games[i].price;
 games[i].revenue += revenue;
 printf("SUCCESS\n");
 return;
 }
 }
 
 printf("Game \"%s\" is not in the database\n", name);
 }
}
//Helper function used in the next function: Prints a single Game
void printGame(Game* game) {
 printf("%s %.2f %.2f\n", game->name, game->price, game->revenue);
}
// sorts and prints the entire database by using printGame function
void printDatabase() {
 
 //sorts the database
 for (int i = 0; i < numGames - 1; i++) {
 for (int j = i + 1; j < numGames; j++) {
 if (games[i].revenue < games[j].revenue) {
 Game temp = games[i];
 games[i] = games[j];
 games[j] = temp;
 }
 }
 }
 
 for (int i = 0; i < numGames; i++) {
 printGame(&games[i]);
 }
 
 printf("SUCCESS\n");
}
// Saves the current Database to given filename
void saveToFile(char* input) {
 
 char filename[1000];
 
 sscanf(input + 2, "%s", filename); // Gets the filename
 
 FILE* file = fopen(filename, "w");
 if (!file) {
 printf("Error: could not open file %s\n", filename);
 return;
 }
 
 // writes all the games to the given file
 for (int i = 0; i < numGames; i++) {
 fprintf(file, "%s %.2f %.2f\n", games[i].name, games[i].price, 
 games[i].revenue);
 }
 
 fclose(file);
 
 printf("SUCCESS\n");
}
// Loads the databases from the given file name
void loadFromFile(char* input) {
    char filename[1000];
    sscanf(input + 2, "%s", filename);
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open file %s for reading.\n", filename);
        return;
    }
    
    int oldNumGames = numGames;
    for (int i = 0; i < oldNumGames; i++) {
        free(games[i].name);
    }
    free(games);

    numGames = 0;
    char line[1000];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (count == 0) {
        games = malloc((numGames + 1) * sizeof(Game));
        count++;
        } else {
        games = realloc(games, (numGames + 1) * sizeof(Game));
        }
        char name[1000];
        sscanf(line, "%s %f %f", name, &games[numGames].price,
            &games[numGames].revenue);
        games[numGames].name = malloc(strlen(name) + 1);
        strcpy(games[numGames].name, name);
        numGames++;
    }
    fclose(file);
    printf("SUCCESS\n");
}


// In the main function, all the functions defined above are used 
int main() {
 
 char input[1000]; 
 
 // runs an infinite loop. "break" is used to stop the loop
 while (1) {
 
 scanf(" %[^\n]s", input); // stores userinput into another array
 
 char command = getCommandFromUser(input); // gets the command from the userInput using getCommandFromUser
 
 switch (command) {
 
 //if command is 'A', the add function is called
 case 'A':
 add(input);
 break; 
 
 //if command is 'B', the buy function is called
 case 'B':
 buy(input);
 break;
 
 //if command is 'L', the printDatabase function is called
 case 'L':
 printDatabase();
 break;
 
 //if command is 'W', the saveToFile function is called 
 case 'W':
 saveToFile(input);
 break;
 
 //if command is 'O', the loadFromFile function is called
 case 'O':
 loadFromFile(input);
 break;
 
 //if command is 'Q', exit the program
 case 'Q':
 printf("SUCCESS\n");
 
 for (int i = 0; i < numGames; i++) {
 free(games[i].name);
 }
 
 free(games);
 
 return 0;
 
 case 0:
 break;
 
 // any other command prints an error message 
 default:
 printf("Invalid command %c\n", command);
 break;
 }
 }
}