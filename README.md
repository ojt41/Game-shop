## Game Database Management System

This code represents a simple game database management system that allows users to perform various operations on a collection of games, such as adding new games, buying games, printing the database, saving the database to a file, and loading a database from a file. The system is controlled through a command-line interface, where users enter commands followed by arguments to perform different actions.

### Usage Instructions

1. **Compilation**: Compile the code using a C compiler (e.g., GCC) with the appropriate flags.

   ```shell
   gcc -o game_database game_database.c
   ```

2. **Running the Program**: Run the compiled executable to start the game database management system.

   ```shell
   ./game_database
   ```

3. **Commands and Actions**:

   - `A <game_name> <price>`: Add a new game to the database with the given name and price.
   - `B <game_name> <count>`: Purchase a specific count of a game, updating its revenue.
   - `L`: Print the entire game database, sorted by revenue in descending order.
   - `W <filename>`: Save the current database to a file with the provided filename.
   - `O <filename>`: Load a database from a file with the given filename.
   - `Q`: Exit the program.

4. **Exiting the Program**: To exit the program, use the `Q` command. This will free memory and terminate the program gracefully.

### Code Structure

The code is structured as follows:

- `getCommandFromUser`: Extracts the command from user input.
- `add`: Adds a new game to the database if it doesn't exist already.
- `buy`: Allows purchasing a specific count of a game and updates the revenue.
- `printGame`: Helper function to print details of a single game.
- `printDatabase`: Sorts and prints the entire database in descending order of revenue.
- `saveToFile`: Saves the current database to a specified file.
- `loadFromFile`: Loads a database from a specified file.
- `main`: The main loop that takes user input, processes commands, and performs actions accordingly.

### Error Handling

The code includes error handling for various scenarios, such as invalid input, negative prices, negative counts, file I/O errors, and more. Error messages are provided to guide users and prevent incorrect operations.

### Conclusion

This simple game database management system provides users with the ability to manage and track games in a collection. It demonstrates basic file I/O, memory management, and command processing techniques. Users can add, buy, print, save, and load game records in a structured manner.
