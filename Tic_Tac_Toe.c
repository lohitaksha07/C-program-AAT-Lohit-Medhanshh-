#include <stdio.h>

char board[3][3];
char currentPlayer = 'X';

void initBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

int checkWin() {
    // rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) return 1;
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) return 1;
    }
    // diagonals
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) return 1;
    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) return 1;

    return 0;
}

int isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    int row, col;
    initBoard();

    printf("Tic Tac Toe (Player X vs Player O)\n");
    printBoard();

    while (1) {
        printf("Player %c, enter row and column (1-3 1-3): ", currentPlayer);
        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input.\n");
            return 0;
        }

        row--; col--;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            printf("Out of range, try again.\n");
            continue;
        }
        if (board[row][col] != ' ') {
            printf("Cell already taken, try again.\n");
            continue;
        }

        board[row][col] = currentPlayer;
        printBoard();

        if (checkWin()) {
            printf("Player %c wins!\n", currentPlayer);
            break;
        }
        if (isDraw()) {
            printf("It's a draw.\n");
            break;
        }

        switchPlayer();
    }

    return 0;
}
