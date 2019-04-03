/*
 *  Title: gameLoop.cpp
 *  Course: Computational Problem Solving 1 (CPET-121)
 *  Developer: Andrew Serra
 *  Date: 04/02/2019
 *  Description: Essential functions for the game.
 *               Clear screen, draw the final state of game, and game loop
 *  Implementation: BEST
 */

#include <iostream>
#include <iomanip>
#include "connectFour.h"

// Clears the screen
// Work around to not use system("clear")
void removeOldGameState(void) {
    for (int i=0; i < 10; i++) {
        std::cout << "\n\n\n\n\n\n\n\n\n\n";
    }
}

void drawGame(std::string move_loss_msg, int game_board[6][7], int NUM_ROWS, int NUM_COLS) {

    std::cout << move_loss_msg;

    for(int i=0; i <= NUM_ROWS; i++) {

        // cell rows
        if (i > 0) {

            for (int j = 0; j < NUM_COLS; j++) {

                // individual cell
                for (int cell_elem = 0; cell_elem < 4; cell_elem++) {

                    switch (cell_elem) {
                        case 0:
                            std::cout << "|";
                            break;
                        case 1:
                        case 3:
                            std::cout << " ";
                            break;
                        case 2:
                            if (game_board[i-1][j] == 0) {
                                std::cout << " ";
                            } else {
                                if(game_board[i-1][j] == 1) {
                                    std::cout << 'X';
                                }
                                else if(game_board[i-1][j] == 2) {
                                    std::cout << 'O';
                                }
                            }
                    }
                }
            }
            // last element in cell row
            std::cout << "|\n";
        }
        // column numbers
        else {

            for (int j = 0; j <= NUM_COLS * 4; j++) {

                // every 4th element
                if (j % 4 == 2) {
                    std::cout << (j / 4) + 1;
                }
                else {
                    std::cout << " ";
                }

            }
            std::cout << std::endl;
        }

        // separator rows
        for (int j = 0; j < NUM_COLS; j++) {

            for (int sep_elem = 0; sep_elem < 4; sep_elem++) {

                // every 4th element
                if (sep_elem % 4 == 0) {
                    std::cout << "+";
                } else {
                    std::cout << "-";
                }
            }
        }
        // last element in row separator
        std::cout << '+' << std::endl;
    }
}

void gameLoop(bool p1_starts, int game_board[6][7], int NUM_ROWS, int NUM_COLS,
              char p1_marker, char p2_marker) {

    bool game_ended = false,
         col_is_full = false;
    int loop_count = 0;

    int last_move;

    // if player 2 starts increase loop count +1
    if(!p1_starts) {
        loop_count += 1;
    }

    // wait for user to press a key
    system("pause");

    // message for illegal moves
    std::string msg;

    do {

        // clear the screen
        removeOldGameState();

        // player 1 plays
        if(loop_count % 2 == 0) {

            drawGame(msg, game_board, NUM_ROWS, NUM_COLS);

            // reset msg to empty string
            msg = "\n";

            std::cout << "\nPlayer #1's Turn (X)\nEnter your move: ";
            std::cin >> last_move;

            if(last_move != 0) {
                // last move-1 to get correct index
                place_marker(p1_marker, game_board, last_move-1, col_is_full, msg);
            }
            else {

                int pop_out_col_choice;
                std::cout << "Choose column to pop out from: ";
                std::cin >> pop_out_col_choice;

                popOutChecker(p1_marker, pop_out_col_choice-1, game_board);
            }
            if(loop_count >= 5 && last_move != 0) {
                // check if there is a winning combo
                didGameEnd(p1_marker, last_move-1, col_is_full, game_board, game_ended);
            }

            std::cout << std::endl;
        }
        // player 2 plays
        else {
            drawGame(msg, game_board, NUM_ROWS, NUM_COLS);

            // reset msg to empty string
            msg = "\n";

            std::cout << "\nPlayer #2's Turn (O)\nEnter your move: ";
            std::cin >> last_move;

            if(last_move != 0) {
                // last move-1 to get correct index
                place_marker(p2_marker, game_board, last_move-1, col_is_full, msg);
            }
            else {

                int pop_out_col_choice;
                std::cout << "Choose column to pop out from: ";
                std::cin >> pop_out_col_choice;

                popOutChecker(p2_marker, pop_out_col_choice-1, game_board);
            }

            if(loop_count >= 5 && last_move != 0) {
                // check if there is a winning combo
                didGameEnd(p2_marker, last_move-1, col_is_full, game_board, game_ended);
            }

            std::cout << std::endl;
        }

        loop_count += 1;

    } while(!game_ended);

}