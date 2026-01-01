#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define ROWS 10
#define COLS 20
#define CELL_SIZE 30

// . = wall, ' ' = path, S = start, E = exit
const char maze[10][21] = {
    ".............   ....",
    ".S            .    .",
    "... ..... .... . ...",
    ".    .        .   .",
    ". ..... . ... .. . .",
    ".       .   .    . .",
    ". ..... . . .... . .",
    ".     .      .     E.",
    ". ... . ........ ...",
    ". ... .............."
};

int playerRow = 1;
int playerCol = 1;
int exitRow   = 8;
int exitCol   = 18;
int gameWon   = 0;
bool won = false;

void update_player(int drow, int dcol) {
    if (won) return;

    int newRow = playerRow + drow;
    int newCol = playerCol + dcol;

    if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS)
        return;

    char cell = maze[newRow][newCol];
    if (cell == '.') {
        return; // wall
    }

    playerRow = newRow;
    playerCol = newCol;

    if (cell == 'E') {
        printf("You reached the exit! You win!\n");
        won = true;
    }
}

void render_maze(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            char cell = maze[r][c];

            if (cell == '.') {
                SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);   // wall
            } else if (cell == 'S') {
                SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);    // start
            } else if (cell == 'E') {
                SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);    // exit
            } else {
                SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);   // path
            }

            SDL_Rect rect = { c * CELL_SIZE, r * CELL_SIZE, CELL_SIZE, CELL_SIZE };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_SetRenderDrawColor(renderer, 220, 220, 0, 255);
    SDL_Rect playerRect = {
        playerCol * CELL_SIZE,
        playerRow * CELL_SIZE,
        CELL_SIZE,
        CELL_SIZE
    };
    SDL_RenderFillRect(renderer, &playerRect);

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "SDL2 Maze",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        COLS * CELL_SIZE, ROWS * CELL_SIZE,
        0
    );
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event e;

    printf("Controls: W/A/S/D or arrow keys, Esc or Q to quit.\n");

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                SDL_Keycode key = e.key.keysym.sym;

                if (key == SDLK_ESCAPE || key == SDLK_q) {
                    running = false;
                } else if (key == SDLK_w || key == SDLK_UP) {
                    update_player(-1, 0);
                } else if (key == SDLK_s || key == SDLK_DOWN) {
                    update_player(1, 0);
                } else if (key == SDLK_a || key == SDLK_LEFT) {
                    update_player(0, -1);
                } else if (key == SDLK_d || key == SDLK_RIGHT) {
                    update_player(0, 1);
                }

                if (playerRow == exitRow && playerCol == exitCol && !gameWon) {
                gameWon = 1;
                printf("YOU WIN!\n");
                }
            }
        }

        render_maze(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
