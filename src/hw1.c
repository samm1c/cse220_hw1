#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"

char board[MAX_ROWS][MAX_COLS] = {0};
/*
Hint: Consider adding a global variable to store a string large enough to store a board.
*/
//char board_str[][];

void initialize_board(const char *initial_state, int num_rows, int num_cols) {
    int index = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            board[i][j] = initial_state[index];
            index++;
        }
    }
}

int solve(const char *initial_state, int num_rows, int num_cols, int *num_x, int *num_o) {   
    printf("%c  %d  %d  %p   %p", initial_state[0], num_rows, num_cols, (void *)num_x, (void *)num_o);
    return 0;
}

char* generate_medium(const char *final_state, int num_rows, int num_cols) { 
    printf("%c   %d  %d", final_state[0], num_rows, num_cols);
    return 0;
}
