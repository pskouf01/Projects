#ifndef SNAKE_H
#define SNAKE_H
//////////////////////////////////snake.h//////////////////////////////
//	By: Panos Skoufalos
//    Date: November 8th, 2015
// Purpose: this file contains all of the constants for the program 
// 	    msnake.cpp and a class called Snake.


#include<iostream>
using namespace std;

const int 	ROWS    = 24;		
const int 	COLS    = 63;		
const int	EU_INIT = 60;
const char 	HORIZONTAL_BORDERS = '-';
const char 	VERTICAL_BORDERS = '|';
const char 	CORNERS = '+';
const char 	HEAD_DIRECTIONS[4] = {'^','<','>','v'}; 

//const char	BUG_SYM = 'X';
const int	BUG_VAL = 25;
//const char	EGG_SYM = 'O';
const int	EGG_VAL = 15;



////////////////////////////////////////////////////////////////////////////
////////////////////////SNAKE DEFINITION////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class Snake
{
    public:
	void	init();
	void	set_name(string);
	void	set_pos(int r, int c, char dir);
	void	set_controls(char l, char r, char f);
	void	set_body(char);
	void	set_EU(int);


	string	get_name();
	int	get_score();

	bool	process_key(char, char [ROWS][COLS]);
	bool	is_alive();
	void	print_status();
	void	draw_head_on_board(char [ROWS][COLS]);

	void setup_snake(int, int row, int col, char dir, int EU);

    private:
	string  name;
	bool alive;
	int rows;
	int cols;
	char left;
	char right;
	char forward;
	char body_character;
	int EU;
	int score;
	int  headDirection;
	void rotate_head(char input, char[ROWS][COLS]);
	bool runs_into_self(char board[][COLS]);
	void snake_munchies(char board[ROWS][COLS]);
	void move_forward(char [ROWS][COLS]);
	void mover(char board[ROWS][COLS]);

};

#endif 
