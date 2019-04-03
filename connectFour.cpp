/*
 *  Title: connectFour.cpp
 *  Course: Computational Problem Solving 1 (CPET-121)
 *  Developer: Andrew Serra
 *  Date: 04/02/2019
 *  Description: Main file for the game. Initializes the game field,
 *               shows the intro text, and the who starts the game.
 *  Implementation: BEST
 */

#include <iostream>
#include <ctime>
#include "connectFour.h"

int main(void) {

    const int NUM_ROWS = 6,
              NUM_COLS = 7;
    const char p1_marker = 'X',
               p2_marker = 'O';

    bool p1_starts;

    // init game board                           COLUMNS
    //                                     0  1  2  3  4  5  6
    int game_board[NUM_ROWS][NUM_COLS] = {{0, 0, 0, 0, 0, 0, 0},    // ROW 0
                                          {0, 0, 0, 0, 0, 0, 0},    // ROW 1
                                          {0, 0, 0, 0, 0, 0, 0},    // ROW 2
                                          {0, 0, 0, 0, 0, 0, 0},    // ROW 3
                                          {0, 0, 0, 0, 0, 0, 0},    // ROW 4
                                          {0, 0, 0, 0, 0, 0, 0}};   // ROW 5

    srand(time(NULL));

    // Game intro
    std::cout << "\n\t\t\t\tWelcome to Connect4\n\t\tThe goal of Connect4 is to be the first\n"
              << "\tplayer to place four checkers in a row, either\n"
              << "\t\thorizontally, vertically, or diagonally.\n\n";

    // Decide who starts
    if(rand() % 2 == 0) {
        std::cout << "\n\n\t\tPlayer #1 (" << p1_marker << ") was selected to go first.\n\n";
        p1_starts = true;
    }
    else {
        std::cout << "\n\n\t\tPlayer #2 (" << p2_marker << ") was selected to go first.\n\n";
        p1_starts = false;
    }

    gameLoop(p1_starts, game_board, NUM_ROWS, NUM_COLS, p1_marker, p2_marker);

    return 0;
}