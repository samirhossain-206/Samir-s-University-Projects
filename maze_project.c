// Add brief description here
// This program simulates the greek mythological story of Theseus and the Minotaur
// It loads the maze from an external text file, finds Theseus's starting position, and then moves him according to the specified movement rules.
// The maze is represented as a 2D array of characters, where 'T' represents Theseus's starting position, 'D' represents the destination, and 'P' represents valid paths.
// Theseus's job is to avoid the walls 'W' and especially the Minotaur 'M'.
// We will be implementing the 'always turn left' strategy and 'turn clockwise at an obstacle' strategy to help Theseus make it through the maze.
// The program tracks the number of steps taken and outputs the results in JSON format, including the starting position, left_steps, directions and optimal_steps
// In this program I have used 4 function prototypes to minimize the syntax inside int main() and have also used structs to make variable usage more efficient.

#include <stdio.h>
// Enter any other #includes that you deem necessary below
#include <stdlib.h>
#include <string.h>  // To use strcat
#include <limits.h> // To use INT_MAX for distance initialization

#define NUMROWS	 12    // map size
#define NUMCOLS  12    // map size

char maze[NUMROWS][NUMCOLS]; // The maze is a 2D array of characters
int start_x, start_y; // Starting coordinates of the maze

void load_maze(const char *filename); // Function prototype to load the maze from a file

// The following code is the main function of the program. It simulates Theseus's movement in the maze.
// It uses a structure to represent Theseus's position and direction, and it implements the "Always Turn Left" strategy for movement.
enum direction{N = 0, E = 1, S = 2, W = 3}; // Enum to represent the four possible directions: North, East, South, and West
void next_position(int x, int y, enum direction dir, int *next_x, int *next_y); // Function to get the next position based on the current position and direction
int path(int x, int y); // Function to check if the next position is a valid path

// This is used to find the shortest path in the maze.
int optimal_path(int start_x, int start_y);

int main(void) {
    
    // Load the map
    load_maze("maze.txt"); // Load the maze from a file named "maze.txt"

    // Do required calculations
    for (int i = 0; i < NUMROWS; i++) {
        for (int j = 0; j < NUMCOLS; j++) {
            if (maze[i][j] == 'T') {
                start_x = i; // Store the row index of 'T'. +1 to convert to 1-based index
                start_y = j; // Store the column index of 'T'. +1 to convert to 1-based index
                break; // Break out of the loop if 'T' is found
            }
        }
    }

    // The struct is for Theseus's position and direction
    // It contains the x and y coordinates, as well as the direction Theseus is facing.
    struct Theseus {
        int x;
        int y;
        enum direction dir;
    };

    struct Theseus theseus;
    theseus.x = start_x;
    theseus.y = start_y;
    theseus.dir = S;  // Theseus starts by facing South

    // For storing direction moves
    char *directionNames[] = {"N", "E", "S", "W"};
    char directions[1000] = ""; // Initialize the directions string as empty
    // - The "= \"\"" sets the first character to the null terminator '\0', which is needed for strcat() to work properly.
    // - The size 1000 is chosen to ensure there's enough space for a long path, assuming worst-case maze sizes and step counts.

    int left_steps = 0;  // Count of left turns

    // Simulate movement
    while (1) { // Infinite loop until 'D' is found
        theseus.dir = (enum direction)((theseus.dir + 3) % 4);  // Turn left
        int nextX, nextY; // Variables to store the next position
        next_position(theseus.x, theseus.y, theseus.dir, &nextX, &nextY);  // Get the next position

        int attempts = 0;
        while (attempts < 4) { // Try all four directions
            if (path(nextX, nextY)) { // Check if the next position is a valid path
                theseus.x = nextX;
                theseus.y = nextY;
                if (left_steps > 0) { // If it's not the first step, add the direction to the directions string
                    strcat(directions, ", ");
                }
                strcat(directions, directionNames[theseus.dir]); // Add the direction to the directions string if it's not the first step
                left_steps++; // Increment the left turn count
                break;
            } else {
                theseus.dir = (enum direction)((theseus.dir + 1) % 4); // theseus.dir = (theseus.dir + 1) % 4; because it is a circular array
                attempts++; // Increment attempts to try the next direction
                next_position(theseus.x, theseus.y, theseus.dir, &nextX, &nextY); // Recalculate the new position based on the updated direction
            }
        }

        if (maze[theseus.x][theseus.y] == 'D') { // Check if Theseus has reached the destination 'D'
            break;
        }
    }

    // Calculate the optimal steps
    // The optimal_path function is called to find the shortest path from the starting position to the destination 'D'
    int optimal_steps = optimal_path(start_x, start_y);

    // This is to remove the first space from the directions string
    if (directions[0] == ' ') {
        memmove(directions, directions + 1, strlen(directions)); // `memmove` shifts the string to remove the leading space
    }

    // Print results in JSON format
    printf("{\"theseus_start\": [%d, %d],\n", start_x, start_y); // Print the starting position of 'T'
    printf(" \"left_steps\": %d,\n", left_steps); // Number of steps taken
    printf(" \"directions\": \"%s\",\n", directions); // Directions taken
    printf(" \"optimal_steps\": %d}", optimal_steps); // Optimal steps to reach 'D' using the function optimal_path

    return 0;
}

void load_maze(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (file == NULL) {
        perror("Error!"); // The perror() function prints a message to the standard error stream stderr
        exit(EXIT_FAILURE); // Return an error if the file cannot be opened
    }

    for (int i = 0; i < NUMROWS; i++) {
        for (int j = 0; j < NUMCOLS; j++) {
            if (fscanf(file, " %c", &maze[i][j]) != 1) { // If fscanf fails to read a character
                fprintf(stderr, "Error!"); // stderr is used for error messages
                exit(EXIT_FAILURE); // Return an error if the maze data cannot be read
            }
        }
    }

    fclose(file); // Close the file
}

// The next_position function calculates the next position based on the current position and direction
// It takes the current coordinates (x, y), the direction (dir), and pointers to store the next coordinates (next_x, next_y).
void next_position(int x, int y, enum direction dir, int *next_x, int *next_y) {
    switch (dir) {  // check the direction
        case N:  // If the direction is North
            *next_x = x - 1;  // move up (decrease row)
            *next_y = y;      // stay in the same column
            break;

        case E:  // If the direction is East
            *next_x = x;      // stay in the same row
            *next_y = y + 1;  // move right (increase column)
            break;

        case S:  // If the direction is South
            *next_x = x + 1;  // move down (increase row)
            *next_y = y;      // stay in the same column
            break;

        case W:  // If the direction is West
            *next_x = x;      // stay in the same row
            *next_y = y - 1;  // move left (decrease column)
            break;
    }
}

int path(int x, int y) {
    // Ensure 'x' is within the vertical bounds of the maze
    // Ensure 'y' is within the horizontal bounds of the maze
    // Then check if the current cell is a path ('P') or the destination ('D')
    // Return 1 if valid; otherwise, return 0
    return (x >= 0 && x < NUMROWS &&       // within row bounds
            y >= 0 && y < NUMCOLS &&       // within column bounds
            (maze[x][y] == 'P' || maze[x][y] == 'D'));  // on a walkable path or door
}


int optimal_path(int starting_x, int starting_y) { 
    // Function to find the shortest path from the starting position (starting_x, starting_y) to the destination 'D'
    
    // 2D array to track visited positions in the maze
    int visited[NUMROWS][NUMCOLS] = {0};
    
    // 2D array to store the shortest distance from start to each position in the maze
    int distance[NUMROWS][NUMCOLS];
    
    // Initialize all distances to a large number (INT_MAX) to represent unreachable cells
    for (int i = 0; i < NUMROWS; i++)
        for (int j = 0; j < NUMCOLS; j++)
            distance[i][j] = INT_MAX;

    // Define a structure to represent a point (x, y)
    struct Point { int x, y; } queue[NUMROWS * NUMCOLS];
    
    // Initialize front and rear pointers
    int front = 0, rear = 0;

    // Mark the starting position as visited and set its distance to 0
    visited[starting_x][starting_y] = 1;
    distance[starting_x][starting_y] = 0;
    
    // Add the starting point to the queue
    queue[rear++] = (struct Point){starting_x, starting_y};

    // Arrays to define possible movement directions (N, S, E, W)
    int dx[] = {-1, 1, 0, 0}; // N, S, E, W for x-axis (rows)
    int dy[] = {0, 0, 1, -1}; // N, S, E, W for y-axis (columns)

    while (front < rear) {
        // Dequeue the front point from the queue
        struct Point point = queue[front++];

        // Try moving in all four possible directions
        for (int d = 0; d < 4; d++) {
            // Calculate the new position (next_x, next_y) based on the current direction
            int next_x = point.x + dx[d];
            int next_y = point.y + dy[d];

            // Check if the new position is within bounds, not visited, and is either a path ('P') or the destination ('D')
            if (next_x >= 0 && next_x < NUMROWS && next_y >= 0 && next_y < NUMCOLS &&
                !visited[next_x][next_y] &&
                (maze[next_x][next_y] == 'P' || maze[next_x][next_y] == 'D')) {

                // Mark the new position as visited
                visited[next_x][next_y] = 1;
                
                // Set the distance of the new position to be one more than the current position's distance
                distance[next_x][next_y] = distance[point.x][point.y] + 1;
                
                // Add the new position to the queue
                queue[rear++] = (struct Point){next_x, next_y};

                // If the destination ('D') is found, return the distance to it
                if (maze[next_x][next_y] == 'D') {
                    return distance[next_x][next_y];
                }
            }
        }
    }

    // If no path to the destination is found, return -1
    return -1;
}