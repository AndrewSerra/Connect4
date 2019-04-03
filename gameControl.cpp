/*
 *  Title: gameControl.cpp
 *  Course: Computational Problem Solving 1 (CPET-121)
 *  Developer: Andrew Serra
 *  Date: 04/02/2019
 *  Description: Game control functions and helper functions
 *  Implementation: BEST
 */

#include <iostream>
#include <cmath>
#include "connectFour.h"

// checks if the game ended
void didGameEnd(char p_marker, int last_move, bool col_is_full, int game_board[6][7], bool& game_ended) {

    // Only execute if the previous round turn was not lost
    if(!col_is_full) {

        int last_move_col = last_move;
        int last_move_row = getTopChecker(last_move, game_board);
        int count_horizontal,
            count_vertical,
            count_diagonal;

        switch (p_marker) {
            case 'X':

                // check winning combos
                count_horizontal = checkHorizontal(last_move_row, last_move_col, 1, 1, 1, game_board);
                count_vertical = checkVertical(last_move_row, last_move_col, 1, 1, 1, game_board);
                count_diagonal = checkDiagonal(last_move_row, last_move_col, 1, 1, 1, 1, 1, game_board);

                if(count_horizontal >= 4 || count_vertical >= 4 || count_diagonal >= 4) {

                    // clear the screen
                    removeOldGameState();

                    drawGame("\n", game_board, 6, 7);

                    std::cout << "\n\nPlayer 1 (X) wins the game!\n\n";
                    game_ended = true;
                }

                break;

            case 'O':

                // check winning combos
                count_horizontal = checkHorizontal(last_move_row, last_move_col, 1, 1, 2, game_board);
                count_vertical = checkVertical(last_move_row, last_move_col, 1, 1, 2, game_board);
                count_diagonal = checkDiagonal(last_move_row, last_move_col, 1, 1, 1, 1, 2, game_board);


                if(count_horizontal >= 4 || count_vertical >= 4 || count_diagonal >= 4) {

                    // clear the screen
                    removeOldGameState();

                    drawGame("\n", game_board, 6, 7);

                    std::cout << "\n\nPlayer 2 (O) wins the game!\n\n";
                    game_ended = true;
                }

                break;
        }
    }
    else {
        // check for tie game
        for(int i=0; i < 6; i++) {
            if(game_board[0][i] != 0) {
                game_ended = true;
            }
            else {
                game_ended = false;
                break;
            }
        }

        if(game_ended) {
            // clear the screen
            removeOldGameState();

            drawGame("\n", game_board, 6, 7);

            std::cout << "\n\nTie game!\n\n";
        }
    }
}

// places marker to appropriate position if the moves are valid
void place_marker(char p_marker, int game_board[6][7], int last_move, bool& col_is_full, std::string& msg) {

    int move = last_move;
    bool move_is_valid = isLastMoveValid(move);

    col_is_full = isColFull(game_board, move);

    // if more is not valid request until valid
    if(!move_is_valid) {
        do {
            std::cout << "Illegal Position, Please Reenter: ";
            std::cin >> move;

            move -= 1;

            move_is_valid = isLastMoveValid(move);
        } while (!move_is_valid);
    }

    // if column is not full place marker
    if(!col_is_full) {

        // Start from bottom 7-1 = 6 <-- index
        for(int i=6; i >= 0; i--) {
            // enter player 1 marker
            if(game_board[i][move] == 0 && p_marker == 'X') {
                game_board[i][move] = 1;
                break;
            }
            // enter player 2 marker
            else if(game_board[i][move] == 0 && p_marker == 'O') {
                game_board[i][move] = 2;
                break;
            }
        }
    }
    else {

        // set message to be displayed when next drawGame is called
        msg = "\n\nMove Not Available, You Lost Your Turn.\n\n";
    }
}

// shifts columns and removes the marker requested
void popOutChecker(char p_marker, int column, int game_board[6][7]) {

    bool move_is_valid = isLastMoveValid(column);
    int pop_column = column;
    int index;

    // if more is not valid request until valid
    if(!move_is_valid) {
        do {
            std::cout << "Illegal Position, Please Reenter: ";
            std::cin >> pop_column;

            move_is_valid = isLastMoveValid(column);

        } while (!move_is_valid);
    }

    for(int i=5; i >= 0; i--) {
        if(game_board[i][pop_column] == 1 && p_marker == 'X') {

            // remove requested checker player 1
            game_board[i][pop_column] = 0;
            index = i;
            break;
        }
        else if(game_board[i][pop_column] == 2 && p_marker == 'O') {

            // remove requested checker player 2
            game_board[i][pop_column] = 0;
            index = i;
            break;
        }
    }

    // shift checkers down
    for(int i=index; i > 0; i--) {

        game_board[i][column] = game_board[i-1][column];
    }

    // set top cell to empty
    game_board[0][column] = 0;
}

//////////
// helpers
//////////

// checks if the column choice is in range
bool isLastMoveValid(int last_move) {

    if (last_move >= 0 && last_move <= 6) {
        return true;
    }
    else {
        return false;
    }
}

// checks if the chosen column is full
bool isColFull(int game_board[6][7], int last_move) {

    // check from top to bottom for faster results
    for(int i=0; i < 6; i++) {
        if(game_board[i][last_move] == 0) {
            return false;
        }
    }
    return true;
}

// fetches the top checker in the column and returns index
int getTopChecker(int last_move, int game_board[6][7]) {

    int index;

    for(int i=0; i < 6; i++) {

        if(game_board[i][last_move] != 0) {
            index = i;
            break;
        }
    }

    return index;
}


///////////////////////////////////////
// WIN CHECK FUNCTIONS USE RECURSION //
///////////////////////////////////////

/*
 *  Offset UP    is DECREASING the row value.
 *  Offset DOWN  is INCREASING the row value.
 *  Offset LEFT  is DECREASING the row value.
 *  Offset RIGHT is INCREASING the row value.
 */

// checks horizontal wining condition for last move
int checkHorizontal(int row, int col,
                    int offset_right, int offset_left,
                    int marker_num, int game_board[6][7]) {

    // both directions
    if(game_board[row][col+offset_right] == marker_num &&
       game_board[row][col-offset_left] == marker_num) {

        return checkHorizontal(row, col, offset_right+1, offset_left+1,
                        marker_num, game_board);
    }
    // right direction
    else if(game_board[row][col+offset_right] == marker_num) {

        return checkHorizontal(row, col, offset_right+1, offset_left,
                        marker_num, game_board);
    }
    // left direction
    else if(game_board[row][col-offset_left] == marker_num) {

        return checkHorizontal(row, col, offset_right, offset_left+1,
                        marker_num, game_board);
    }
    else {
        unsigned int dist = std::abs((offset_right) + (offset_left)) - 1;

        return dist;
    }
}

// checks vertical wining condition for last move
int checkVertical(int row, int col,
                    int offset_up, int offset_down,
                    int marker_num, int game_board[6][7]) {

    // both directions
    if(game_board[row-offset_up][col] == marker_num &&
       game_board[row+offset_down][col] == marker_num) {

        return checkVertical(row, col, offset_up+1, offset_down+1,
                               marker_num, game_board);
    }
    // up direction
    else if(game_board[row-offset_up][col] == marker_num) {

        return checkVertical(row, col, offset_up+1, offset_down,
                               marker_num, game_board);
    }
    // down direction
    else if(game_board[row+offset_down][col] == marker_num) {

        return checkVertical(row, col, offset_up, offset_down+1,
                               marker_num, game_board);
    }
    else {
        unsigned int dist = std::abs((offset_up) + (offset_down)) - 1;

        return dist;
    }
}

// checks both diagonals for last move
int checkDiagonal(int row, int col,
                  int offset_up, int offset_right, int offset_down, int offset_left,
                  int marker_num, int game_board[6][7]) {

    int right_dist = checkDiagonalRight(row, col, offset_up, offset_right, offset_down, offset_left,
                                        marker_num, game_board);
    int left_dist = checkDiagonalLeft(row, col, offset_up, offset_right, offset_down, offset_left,
                                       marker_num, game_board);


    // Use the diagonal that has most elements in it.
    if(right_dist > left_dist) {
        return right_dist;
    }
    else {
        return left_dist;
    }

}

// checks right diagonal wining condition for last move
// works nested in checkDiagonal()
int checkDiagonalRight(int row, int col,
                  int offset_up, int offset_right, int offset_down, int offset_left,
                  int marker_num, int game_board[6][7]) {

    // right slant diagonal
    // both directions
    if(game_board[row-offset_up][col+offset_right] == marker_num &&
       game_board[row+offset_down][col-offset_left] == marker_num) {

        return checkDiagonalRight(row, col, offset_up+1, offset_right+1, offset_down+1, offset_left+1,
                             marker_num, game_board);
    }
        // up right direction
    else if(game_board[row-offset_up][col+offset_right] == marker_num) {

        return checkDiagonalRight(row, col, offset_up+1, offset_right+1, offset_down, offset_left,
                             marker_num, game_board);
    }
        // bottom left direction
    else if(game_board[row+offset_down][col-offset_left] == marker_num) {

        return checkDiagonalRight(row, col, offset_up, offset_right, offset_down+1, offset_left+1,
                             marker_num, game_board);
    }
    else {

        unsigned int dist = std::abs((offset_up) + (offset_down)) - 1;

        return dist;
    }
}

// checks left diagonal wining condition for last move
// works nested in checkDiagonal()
int checkDiagonalLeft(int row, int col,
                       int offset_up, int offset_right, int offset_down, int offset_left,
                       int marker_num, int game_board[6][7]) {

    // left slant diagonal
    // both directions
    if(game_board[row-offset_up][col-offset_left] == marker_num &&
       game_board[row+offset_down][col+offset_right] == marker_num) {

        return checkDiagonalLeft(row, col, offset_up+1, offset_right+1, offset_down+1, offset_left+1,
                             marker_num, game_board);
    }
    // up left direction
    else if(game_board[row-offset_up][col-offset_left] == marker_num) {

        return checkDiagonalLeft(row, col, offset_up+1, offset_right, offset_down, offset_left+1,
                             marker_num, game_board);
    }
    // bottom right direction
    else if(game_board[row+offset_down][col+offset_right] == marker_num) {

        return checkDiagonalLeft(row, col, offset_up, offset_right+1, offset_down+1, offset_left,
                             marker_num, game_board);
    }
    // calculation all done
    else {
        unsigned int dist = std::abs((offset_up) + (offset_down)) - 1;

        return dist;
    }
}
