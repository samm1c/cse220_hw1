#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "hw1.h"

char board[MAX_ROWS][MAX_COLS] = {0};
/*
Hint: Consider adding a global variable to store a string large enough to store a board.
*/
char board_string[(MAX_ROWS * MAX_COLS)];

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
    initialize_board(initial_state, num_rows, num_cols);
    // for (int a = 0; a < num_rows; a++) {
    //    for (int b = 0; b < num_cols; b++) {
    //        printf("%c ", board[a][b]);
    //    }
    //    printf("\n");
    // }
    int four_in_a_row, row_count, col_count, major_count, minor_count;
    char test_letters[2] = {'x', 'o'};
    //check number of empty spots, x's, and o's
    int spaces_total = 0;



    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (board[i][j] == '-') {
                spaces_total++;
                // check for FORCED four in a row
                //reset
                int x_four_in_a_row = 0; // try putting in x and see if it's a four
                int o_four_in_a_row = 0; // try putting in o and see if it's a four
                
                for (int t = 0; t < 2; t++) {
                    row_count = 0;
                    col_count = 0;
                    major_count = 0;
                    minor_count = 0;
                    board[i][j] = test_letters[t]; //place it in temporarily
                    //row
                    for (int p = j - 4; p < j + 4; p++) {
                        if (p < 0 || p >= num_cols) { // out of bounds
                            continue;
                        } else if (board[i][p] == test_letters[t]) {
                            row_count++;
                            if (row_count >= 4) {
                                if (t == 0) {
                                    x_four_in_a_row = 1;
                                } else {
                                    o_four_in_a_row = 1;
                                }
                            }
                        } else {
                            row_count = 0;
                        }
                    }
                    //column
                    for (int p = i - 4; p < i + 4; p++) {
                        if (p < 0 || p >= num_rows) {
                            continue;
                        } else if (board[p][j] == test_letters[t]) {
                            col_count++;
                            if (col_count >= 4) {
                                if (t == 0) {
                                    x_four_in_a_row = 1;
                                } else {
                                    o_four_in_a_row = 1;
                                }
                            }
                        } else {
                            col_count = 0;
                        }
                    }
                    //major diagonal
                    for (int p = i - 4, q = j - 4; p < i + 4 || q < j + 4; p++, q++) {
                        if (p < 0 || p >= num_rows || q < 0 || q >= num_cols) {
                            continue;
                        } else if (board[p][q] == test_letters[t]) {
                            major_count++;
                        } else {
                            major_count = 0;
                            if (major_count >= 4) {
                                if (t == 0) {
                                    x_four_in_a_row = 1;
                                } else {
                                    o_four_in_a_row = 1;
                                }
                            }
                        }
                    }
                    //minor diagonal
                    for (int p = i - 4, q = j + 4; p < i + 4 || q >= 0; p++, q--) {
                        if (p < 0 || p >= num_rows || q < 0 || q >= num_cols) {
                            continue;
                        } else if (board[p][q] == test_letters[t]) {
                            minor_count++;
                            if (minor_count >= 4) {
                                if (t == 0) {
                                    x_four_in_a_row = 1;
                                } else {
                                    o_four_in_a_row = 1;
                                }
                            }
                        } else {
                            minor_count = 0;
                        }
                    }
                    //printf("min : %d   min count: %d\n", four_in_a_row, minor_count);
                }

                //printf("i: %d \t j: %d \t x_4: %d \t o_4: %d \n", i, j, x_four_in_a_row, o_four_in_a_row);
                if (x_four_in_a_row && o_four_in_a_row) {
                    return INITIAL_BOARD_NO_SOLUTION;
                }
                board[i][j] = '-'; // put it back again no matter the result


            } else if (board[i][j] == 'x' || board[i][j] == 'o') { // check whether there is already a 4-in-a-row
                //reset
                four_in_a_row = 0;
                row_count = 0;
                col_count = 0;
                major_count = 0;
                minor_count = 0;
                // row
                for (int k = j - 4; k < j + 4; k++) {
                    if (k < 0 || k >= num_cols) { // out of bounds
                        continue;
                    } else if (board[i][k] == board[i][j]) {
                        row_count++;
                        if (row_count >= 4) {
                            four_in_a_row = 1;
                            break;
                        }
                    } else {
                        row_count = 0;
                    }
                }
                //column
                for (int k = i - 4; k < i + 4; k++) {
                    if (k < 0 || k >= num_rows) { // out of bounds
                        continue;
                    } else if (board[k][j] == board[i][j]) {
                        col_count++;
                        if (col_count >= 4) {
                            four_in_a_row = 1;
                            break;
                        }
                    } else {
                        col_count = 0;
                    }
                }
                //major diagonal
                for (int k = i - 4, m = j - 4; k < i + 4 || m < j + 4; k++, m++) {
                    if (k < 0 || k >= num_rows || m < 0 || m >= num_cols) {
                        continue;
                    } else if (board[k][m] == board[i][j]) {
                        major_count++;
                        if (major_count >= 4) {
                            four_in_a_row = 1;
                            break;
                        }
                    } else {
                        major_count = 0;
                    }
                }
                //minor diagonal
                for (int k = i - 4, m = j + 4; k < i + 4 || m >= 0; k++, m--) {
                    if (k < 0 || k >= num_rows || m < 0 || m >= num_cols) { // out of bounds
                        continue;
                    } else if (board[k][m] == board[i][j]) {
                        minor_count++;
                        if (minor_count >= 4) {
                            four_in_a_row = 1;
                            break;
                        }
                    } else {
                        minor_count = 0;
                    }
                }
                //is there a 4 in a row?
                if (four_in_a_row) {
                    return INITIAL_BOARD_FOUR_IN_A_ROW;
                }


            } else { // not a -, x, o, bad character
                return INITIAL_BOARD_INVALID_CHARACTERS;
            }
        }
    }




    int spaces_left = spaces_total;
    //printf("spaces total:  %d\n" , spaces_total);
    // you check for four in a rows -> keep placing
    for (int s = 0; (s < spaces_total) && (spaces_left > 0); s++) {
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                if (board[i][j] == '-') {  // empty space 
                    //printf("i: %d \t   j:  %d\n", i, j);
                    // check for four-in-a-row for both x and o
                    four_in_a_row = 0;
                    //check at least 4 spaces out
                    for (int t = 0; t < 2; t++) {
                        //reset
                        row_count = 0;
                        col_count = 0;
                        major_count = 0;
                        minor_count = 0;

                        board[i][j] = test_letters[t]; // place the test letter inside the board for now
                        //row
                        for (int k = j - 4; k < j + 4; k++) {
                            if (k < 0 || k >= num_cols) {
                                continue;
                            } else if (board[i][k] == test_letters[t]) {
                                row_count++;
                                if (row_count >= 4) {
                                    // if (four_in_a_row && t == 1) {
                                    //     return INITIAL_BOARD_FOUR_IN_A_ROW;
                                    // }
                                    four_in_a_row = 1;
                                    break;
                                }
                            } else {
                                row_count = 0;
                            }
                        }
                        //printf("row : %d   row count: %d\n", four_in_a_row, row_count);
                        //column
                        for (int k = i - 4; k < i + 4; k++) {
                            if (k < 0 || k >= num_rows) {
                                continue;
                            } else if (board[k][j] == test_letters[t]) {
                                col_count++;
                                if (col_count >= 4) {
                                    // if (four_in_a_row && t == 1 && row_count != 4) {
                                    //     return INITIAL_BOARD_FOUR_IN_A_ROW;
                                    // }
                                    four_in_a_row = 1;
                                    break;
                                }
                            } else {
                                col_count = 0;
                            }
                        }
                        //printf("col : %d   col count: %d\n", four_in_a_row, col_count);
                        ///major diagonal
                        for (int k = i - 4, p = j - 4; k < i + 4 || p < j + 4; k++, p++) {
                            if (k < 0 || k >= num_rows || p < 0 || p >= num_cols) {
                                continue;
                            } else if (board[k][p] == test_letters[t]) {
                                major_count++;
                                if (major_count >= 4) {
                                    // if (four_in_a_row && t == 1 && row_count != 4 && col_count != 4) {
                                    //     return INITIAL_BOARD_FOUR_IN_A_ROW;
                                    // }
                                    four_in_a_row = 1;
                                    break;
                                }
                            } else {
                                major_count = 0;
                            }
                        }
                        //printf("maj : %d   maj count: %d\n", four_in_a_row, major_count);

                        //minor diagonal
                        for (int k = i - 4, p = j + 4; k < i + 4 || p >= 0; k++, p--) {
                            if (k < 0 || k >= num_rows || p < 0 || p >= num_cols) {
                                continue;
                            } else if (board[k][p] == test_letters[t]) {
                                minor_count++;
                                if (minor_count >= 4) {
                                    // if (four_in_a_row && t == 1 && row_count != 4 && col_count != 4 && major_count != 4) {
                                    //     return INITIAL_BOARD_FOUR_IN_A_ROW;
                                    // }
                                    four_in_a_row = 1;
                                    break;
                                }
                            } else {
                                minor_count = 0;
                            }
                        }
                        //printf("min : %d   min count: %d\n", four_in_a_row, minor_count);
                        //check if this current letter creates four in a row. if so, replace with opposite letter
                        if (four_in_a_row) {
                            if (test_letters[t] == 'x') {
                                board[i][j] = 'o';
                            } else if (test_letters[t] == 'o') {
                                board[i][j] = 'x';
                            }
                            spaces_left--;
                            break;
                        }
                    }
                    
                    if (!four_in_a_row) { // replace test letter
                        board[i][j] = '-';
                    }
                    
                    // for (int a = 0; a < num_rows; a++) {
                    //    for (int b = 0; b < num_cols; b++) {
                    //        printf("%c ", board[a][b]);
                    //    }
                    //    printf("\n");
                    // }
                }
            }
        }
        
        
        //printf("s %d < spaces_total %d || spaces_left %d > 0\n", s, spaces_total, spaces_left);
        if (spaces_left == spaces_total) { // absolutely no difference, meant that you made no moves, so no solution
            return INITIAL_BOARD_NO_SOLUTION;
        }
        //printf("\nspaces: %d\n", spaces_left);
    }




    if (spaces_left == 0) { // success
        // move the results of the board into the board string and update number of x's and o's
        int str_index = 0;
        (*num_x) = 0;
        (*num_o) = 0;
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                board_string[str_index++] = board[i][j];
                //printf("%c", board_string[str_index]);
                if (board[i][j] == 'x') {
                    (*num_x)++;
                } else {
                    (*num_o)++;
                }
            }
            //board_string[str_index++] = '\n';
        }
        return FOUND_SOLUTION;
    } else {
        return HEURISTICS_FAILED;
    }
    //printf("%c  %d  %d  %p   %p", initial_state[0], num_rows, num_cols, (void *)num_x, (void *)num_o);
    //return 0;
}

char* generate_medium(const char *final_state, int num_rows, int num_cols) {
    // calculate initial quantities of x's and o's
    int num_x = 0;
    int num_o = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (board[i][j] == 'x') {
                num_x++;
            } else {
                num_o++;
            }
        }
    }
    initialize_board(final_state, num_rows, num_cols);
    // gen will be our generated board, which is a copy of the original board
    char gen[num_rows][num_cols];
    //strcpy(gen, board);
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            gen[i][j] = board[i][j];
        }
    }
    // //print test
    // for (int i = 0; i < num_rows; i++) {
    //     for (int j = 0; j < num_cols; j++) {
    //         printf("%c ", board[i][j]);
    //     }
    //     printf("\n");
    // }


    //printf("\nx's: %d \t o's: %d \n\n", num_x, num_o);
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            // change current position to empty -
            char temp = gen[i][j];
            gen[i][j] = '-';
            // update x and o values
            if (temp == 'x') {
                num_x--;
            } else {
                num_o--;
            }

            // convert gen into char STRING so that it can be passed into solve
            int str_index = 0;
            for (int p = 0; p < num_rows; p++) {
                for (int q = 0; q < num_cols; q++) {
                    board_string[str_index++] = gen[p][q];
                }
            }

            // is this solveable? if so keep the board, if not, put it back together again
            if (solve(board_string, num_rows, num_cols, &num_x, &num_o) == 1) {
                continue;
            } else {
                gen[i][j] = temp;
                if (temp == 'x') {
                    num_x++;
                } else {
                    num_o++;
                }
            }
            //print test for each index
            // for (int a = 0; a < num_rows; a++) {
            //     for (int b = 0; b < num_cols; b++) {
            //        printf("%c ", board[a][b]);
            //     }
            //     printf("\n");
            // }
            // printf("\n");
        }
    }
    
    //convert one more time into string
    int str_index = 0;
    for (int p = 0; p < num_rows; p++) {
        for (int q = 0; q < num_cols; q++) {
            board_string[str_index++] = gen[p][q];
        }
    }

    // lastly, put the unsolved, generated board into the actual board variable
    initialize_board(board_string, num_rows, num_cols);
    return board_string;
    
    //printf("%c   %d  %d", final_state[0], num_rows, num_cols);
    //return 0;
}
