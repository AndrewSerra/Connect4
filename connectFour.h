/*
 *  Title: connectFour.h
 *  Course: Computational Problem Solving 1 (CPET-121)
 *  Developer: Andrew Serra
 *  Date: 04/02/2019
 *  Description: Header file for Connect4 game.
 *  Implementation: BEST
 */

#ifndef DEMO_CONNECTFOUR_H
#define DEMO_CONNECTFOUR_H

//gameLoop
void removeOldGameState(void);
void drawGame(std::string move_loss_msg, int game_board[6][7], int NUM_ROWS, int NUM_COLS);
void gameLoop(bool p1_starts, int game_board[6][7], int NUM_ROWS, int NUM_COLS,
              char p1_marker, char p2_marker);

// gameControl
void didGameEnd(char p_marker, int last_move, bool col_is_full, int game_board[6][7], bool& game_ended);
void place_marker(char p_marker, int game_board[6][7], int last_move, bool& col_is_full, std::string& msg);
void popOutChecker(char p_marker, int column, int game_board[6][7]);

bool isLastMoveValid(int last_move);
bool isColFull(int game_board[6][7], int last_move);
int getTopChecker(int last_move, int game_board[6][7]);

int checkHorizontal(int row, int col,
                    int offset_right, int offset_left,
                    int marker_num, int game_board[6][7]);

int checkVertical(int row, int col,
                  int offset_up, int offset_down,
                  int marker_num, int game_board[6][7]);

int checkDiagonal(int row, int col,
                  int offset_up, int offset_right, int offset_down, int offset_left,
                  int marker_num, int game_board[6][7]);

int checkDiagonalRight(int row, int col,
                       int offset_up, int offset_right, int offset_down, int offset_left,
                       int marker_num, int game_board[6][7]);

int checkDiagonalLeft(int row, int col,
                      int offset_up, int offset_right, int offset_down, int offset_left,
                      int marker_num, int game_board[6][7]);


#endif //DEMO_CONNECTFOUR_H
