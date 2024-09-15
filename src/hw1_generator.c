#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"

extern char board[MAX_ROWS][MAX_COLS];
extern char board_string[(MAX_ROWS * MAX_COLS)];

int main(int argc, char **argv)
{
    assert(argc == 4);
    char *initial_state;
    
    printf("Initial state: %s\n", argv[3]);
    int num_rows = (int)strtoul(argv[1], NULL, 10);
    int num_cols = (int)strtoul(argv[2], NULL, 10);

    initial_state = generate_medium(argv[3], num_rows, num_cols);

    // printf("\nresult success\n");
    // for (int i = 0; i < num_rows; i++) {
    //     for (int j = 0; j < num_cols; j++) {
    //         printf("%c ", board[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("Result: %s\n", initial_state);
    return 0;
}
