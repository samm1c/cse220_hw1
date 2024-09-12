#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"

// globalize board for this file
extern char board[MAX_ROWS][MAX_COLS];

int main(int argc, char **argv) {
    assert(argc == 4);
    
	//Write your code here

    //initialize values
    int num_rows = (int)strtoul(argv[1], NULL, 10);
    int num_cols = (int)strtoul(argv[2], NULL, 10);
    initialize_board(argv[3], num_rows, num_cols);

    char piece;
    int row_choice, col_choice, spaces = 0;

    for (int i = 0; i < num_rows; i++) { // run this one time, don't need to calculate spaces continuously
        for (int j = 0; j < num_cols; j++) {
                if (board[i][j] == '-') { // counting for number of empty spaces
                    spaces++;
                }
        }
    }
    while (spaces > 0) { // while board still has spaces
        //reset variables
        piece = ' ';
        row_choice = -1;
        col_choice = -1;
        
        //print board and check for spaces
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }

        // choose piece
        while (piece != 'x' && piece != 'o') { // keep repeating loop if invalid choice
            printf("Choose a piece (x or o) or q to quit: ");
            scanf(" %c", &piece);
            if (piece == 'q') {
                return 0;
            } else if (piece != 'x' && piece != 'o') {
                printf("Invalid choice. ");
            }
        }
        // choose row
        while (row_choice < 0 || row_choice >= num_rows) {
            printf("Choose a row (0-%d): ", num_rows - 1);
            scanf(" %d", &row_choice);
            if (row_choice < 0 || row_choice >= num_rows) {
                printf("Invalid choice. ");
            }
        }
        // choose column
        while (col_choice < 0 || col_choice >= num_cols) {
            printf("Choose a column (0-%d): ", num_cols - 1);
            scanf(" %d", &col_choice);
            if (col_choice < 0 || col_choice >= num_cols) {
                printf("Invalid choice. ");
            }
        }

        //update board
        if (board[row_choice][col_choice] == '-') {
            //check for 4 in a row
            int four_in_a_row = 0; // flag, 0 for false, 1 for true 
            board[row_choice][col_choice] = piece; // test the piece inside
            //check row
            int row_count = 0;

            for (int i = col_choice - 4; i < col_choice + 4; i++) { // iterating over column number, row stays the same
                if (i < 0 || i >= num_cols) { // skip if out of bounds
                    continue;
                } else if (board[row_choice][i] == piece) {
                    row_count++;
                    if (row_count >= 4) { // stop once four in a row detected
                        four_in_a_row = 1;
                        break;
                    }
                } else {
                    row_count = 0;
                }
            }
            //check column
            int col_count = 0;
            for (int i = row_choice - 4; i < row_choice + 4; i++) { // iterating over row number, column stays the same
                if (i < 0 || i >= num_rows) { // skip if out of bounds
                    continue;
                } else if (board[i][col_choice] == piece) {
                    col_count++; // increment
                    if (col_count >= 4) { // check if its four in a row
                        four_in_a_row = 1;
                        break;
                    }
                } else {
                    col_count = 0;
                }
            }
            //check main diagonal
            int main_count = 0;
            for (int i = row_choice - 4, j = col_choice - 4;  i < row_choice + 4 || j < col_choice + 4; i++, j++) {
                if (i < 0 || i >= num_rows || j < 0 || j >= num_cols) { // check for out of bounds
                    continue;
                } else if (board[i][j] == piece) {
                    main_count++;
                    if (main_count >= 4) {
                        four_in_a_row = 1;
                        break;
                    }
                } else {
                    main_count = 0;
                }
            }
            //check minor diagonal
            int minor_count = 0;
            for (int i = row_choice - 4, j = col_choice + 4;  i < row_choice + 4 || j > 0; i++, j--) {
                if (i < 0 || i >= num_rows || j < 0 || j >= num_cols) { // check for out of bounds
                    continue;
                } else if (board[i][j] == piece) {
                    minor_count++;
                    if (minor_count >= 4) {
                        four_in_a_row = 1;
                        break;
                    } 
                } else {
                    minor_count = 0;
                }
            }
            if (four_in_a_row) {
                printf("Invalid choice. You have created 4-in-a-row.\n");
                board[row_choice][col_choice] = '-'; //reset
            } else { // otherwise leave the piece in
                spaces--;
            }
        } else {
            printf("Invalid choice. That space is already occupied.\n");
        }
    }

    // final print
    printf("Congratulations, you have filled the board with no 4-in-a-rows!\n");
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("%c ", board[i][j]);
        }
            printf("\n");
    }
    return 0;
}
