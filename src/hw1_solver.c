#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"

extern char board[MAX_ROWS][MAX_COLS];
extern char board_string[(MAX_ROWS * MAX_COLS)];

int main(int argc, char **argv)
{
    assert(argc == 4);
    int num_x, num_o;
    
    printf("Initial state: %s\n", argv[3]);
    //initialize values
    int num_rows = (int)strtoul(argv[1], NULL, 10);
    int num_cols = (int)strtoul(argv[2], NULL, 10);

    int result = solve(argv[3], num_rows, num_cols, &num_x, &num_o);
    //print test
    // printf("result success\n");
    // for (int i = 0; i < num_rows; i++) {
    //     for (int j = 0; j < num_cols; j++) {
    //         printf("%c ", board[i][j]);
    //     }
    //     printf("\n");
    // }
    // for (int i = 0; i < num_rows; i++) {
    //     for (int j = 0; j < num_cols; j++) {
    //         if (board_string[i+j] != 'x' && board_string[i+j] != 'o'&& board_string[i+j] != '\n' && board_string[i+j] != '-') {
    //             break;
    //         } else {
    //             printf("%c ", board_string[i+j]);
    //         }
    //     }
    //     printf("\n");
    // }


    // for (int i = 0; i < (MAX_ROWS * MAX_COLS); i++) {
    //     //printf("%c", board_string[i]);
    //    if (board_string[i] != 'x' && board_string[i] != 'o'&& board_string[i] != '\n' && board_string[i] != '-') {
    //        break;
    //    } else {
    //        printf("%c ", board_string[i]);
    //    }
    // }
    
    printf("Result: %d\n", result);
    return 0;
}
