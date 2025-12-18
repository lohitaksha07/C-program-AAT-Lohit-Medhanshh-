#include <stdio.h>

#define ROWS 10
#define COLS 20   // 2 * ROWS

// . = wall, ' ' = path, S = start, E = exit, T = trap
char maze[ROWS][COLS + 1] = {
    "....................",
    ".S            T     .",
    ". .... ......... ...",
    ". ..         ...   .",
    ". .. . ... ..   ....",
    ".    . . .    .    .",
    ". .... . .T. ...T. .",
    ".     T  .     .  E.",
    ". ..... .. .........",
    "...................."
};

int playerRow = 1, playerCol = 1; // start at S
int lives = 3;

void printMaze() {
    printf("\nLives: %d\n", lives);
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (r == playerRow && c == playerCol)
                printf("P");
            else if (maze[r][c] == 'T')
                printf(" ");      // hide traps
            else
                printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main() {
    char move;

    printf("Maze Runner (rows=%d, cols=%d)\n", ROWS, COLS);
    printf("Controls: W=up, A=left, S=down, D=right, Q=quit\n");
    printf("Hidden traps (T): stepping on one costs a life and sends you back to start.\n");

    while (lives > 0) {
        printMaze();
        printf("Move: ");
        if (scanf(" %c", &move) != 1) break;

        int newRow = playerRow;
        int newCol = playerCol;

        if (move == 'w' || move == 'W') newRow--;
        else if (move == 's' || move == 'S') newRow++;
        else if (move == 'a' || move == 'A') newCol--;
        else if (move == 'd' || move == 'D') newCol++;
        else if (move == 'q' || move == 'Q') {
            printf("Goodbye!\n");
            return 0;
        } else {
            printf("Invalid key.\n");
            continue;
        }

        if (maze[newRow][newCol] == '.') {
            lives--;
            printf("You hit a wall! Lives left: %d\n", lives);
            if (lives == 0) {
                printf("No lives left. Game over!\n");
                return 0;
            }
            continue;
        
        playerRow = 1;
        playerCol = 1;
        continue;
        }

        if (maze[newRow][newCol] == 'T') {
            lives--;
            printf("You stepped on a trap! Lives left: %d\n", lives);
            if (lives <= 0) {
                printf("No lives left. Game over!\n");
                return 0;
            }
            playerRow = 1;
            playerCol = 1;
            continue;
        }

        playerRow = newRow;
        playerCol = newCol;

        if (maze[playerRow][playerCol] == 'E') {
            printMaze();
            printf("You reached the exit! You win!\n");
            return 0;
        }
    }

    printf("No lives left. Game over!\n");
    return 0;
}
