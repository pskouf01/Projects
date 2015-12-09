//////////////////////////////snake.cpp ////////////////////////////////////
//	By: Panos Skoufalos
//    Date: November 8th, 2015
// Purpose: The purpose of this program is to have all of the in class 
//	    functions for a Snake Class.This program can be called by other
//	    programs and have all the functions from this class.	

#include<iostream>
#include"snake.h"
#include"termfuncs.h"
#include"msnake.h"
using namespace std;
//
// setup_snake -- initialize a snake for the game
//  args: the snake number, the snake, its row, col, dir, and initial EU
//
void Snake::setup_snake(int num, int r, int c, char d, int eu )
{
	string	n;
	char	lkey,rkey,fkey, body;

	init();			// set any initial default values
	set_EU(eu);			// set initial energy
	set_pos(r, c, d);		// set pos and direction

	cout << "Welcome, player " << num << endl;
	cout << "Name? ";
	cin  >> n;
	set_name(n);

	cout << "Body character? ";
	cin  >> body;
	set_body(body);

	cout << "Keys for left, right, fwd? ";
	cin  >> lkey >> rkey >> fkey ;
	set_controls(lkey, rkey, fkey);
}

////////////////////////////////////////////////////////////////////////////
//////////////////////SNAKE IMPLEMENTATION//////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// init -- set initial default values for a Snake 
//   args: none
//   rets: nothing
//   mods: modifies the snake by setting its member variables
//
void Snake::init()
{
	score    = 0;
	 alive    = true;
}

// set_name() - initializes the name of each snake
//	args: string
//	rets: none
//
void Snake::set_name(string n) 
{
	name = n;
}

// set_pos - initializes position
// 	args: two integers and a character 
// 	rets: nothing
void Snake::set_pos(int r, int c, char dir)
{
	rows = r;
	cols = c;
	headDirection = dir;
}

// set_controls - initializes controls
//	args: three characters
// 	rets: nothing
void Snake::set_controls(char l, char r, char f)
{
	left = l;
	right = r;
	forward = f;
}

// set_body - initalizes the body of the snake
//	args: a character
//	rets: nothing
void Snake::set_body(char b)
{
	body_character = b;
}

// set_EU - initializes the EU point system
//	args: an integer
//	rets: nothing
void Snake::set_EU(int eu)
{
	EU = eu;
}

// get_name() - gets the name out of the private section
//	args: nothing
//	rets: a string called name
//
string Snake::get_name()
{
	return name;
}

// get_score() - gets the score out of the private section
//	args: nothing
//	rets: a integer called score
//
int Snake::get_score()
{
	return score;
}

///////////////////////////////////////////////////////////////////////////
///////////////////SNAKE FUNCTIONS/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// process_key() - processes the keys inputed by user
//	args: two character
//	rets: a boolean
//
bool Snake::process_key(char input, char board[][COLS])
{
	if (input == forward){
		mover(board);
		board[rows][cols] = headDirection;
		return true;
	}
	else if( input == left || input == right ){
		rotate_head(input, board);
		return true;
	}
	return false;
}

//print_status()- prints the status of the snakes
//	args: nothing
//	rets: nothing
//
void Snake::print_status()
{
	cout<<name<<" EU: "<<EU<<" Score: "<<score<<" Keys: "<<left<<right
	    <<forward<<endl;
}

//rotate_head() - rotates the head of the snake
//	args: two characters, input and board
//	rets: nothing
void Snake::rotate_head(char input, char board[][COLS])
{
	if(input == right){
		if (headDirection == HEAD_DIRECTIONS[0]){
			headDirection = HEAD_DIRECTIONS[2];
		}else if (headDirection == HEAD_DIRECTIONS[1]){
			headDirection = HEAD_DIRECTIONS[0];
		}else if (headDirection == HEAD_DIRECTIONS[2]){
			headDirection = HEAD_DIRECTIONS[3];
		}else{
			headDirection = HEAD_DIRECTIONS[1];
		}
	}else {
		if (headDirection == HEAD_DIRECTIONS[0]){
			headDirection = HEAD_DIRECTIONS[1];
		}else if (headDirection == HEAD_DIRECTIONS[1]){
			headDirection = HEAD_DIRECTIONS[3];
		}else if (headDirection == HEAD_DIRECTIONS[2]){
			headDirection = HEAD_DIRECTIONS[0];
		}else{
			headDirection = HEAD_DIRECTIONS[2];
		}
	}
	board[rows][cols] = headDirection;
}

// is_alive() - checks the status of the snake life
//	args: none
//	rets: a boolean
bool Snake::is_alive()
{
	return alive;
}
// mover() -- delegates different tasks in moving the snake.
//	args: a character, board
//	rets: nothing
void Snake::mover(char board[][COLS])
{
	move_forward(board);
	snake_munchies(board);
	alive = runs_into_self(board);
	board[rows][cols] = headDirection;
	EU--;
       	score++;
}
//runs_into_self() -- checks to see if snake runs into it self
//	args: a character, board
//	rets: a boolean, either true or false
bool Snake::runs_into_self(char board[][COLS])
{
	if (board[rows][cols] == body_character){
		board[rows][cols] = headDirection;
		return alive = false;
	}
	if (EU == 0){
		board[rows][cols] = headDirection;
		return alive = false;
	}
	return alive;
}
//move_forward() - moves the snake forward
//	args: a character, board
//	rets: nothing
//
void Snake::move_forward(char board[ROWS][COLS])
{
	if (headDirection == HEAD_DIRECTIONS[0]){
		board[rows][cols] = body_character;
	      	if (rows == 1){
			rows = ROWS-1;}
			rows--;		
	}else if (headDirection == HEAD_DIRECTIONS[1]){
	       	board[rows][cols] = body_character;
	       	if (cols == 1){
       			cols = COLS-1;}
                cols--;
       	}else if (headDirection == HEAD_DIRECTIONS[2]){
       		board[rows][cols] = body_character;
       		if (cols ==COLS-2){
	       		cols = 0;}
		cols++;
	}else {
		board[rows][cols] = body_character;
		if (rows == ROWS-2){
			rows = 0;}
		rows++;
	}
}
//draw_head_on_board() - gives the head of the snake a position on the board
//	args: a character, board
//	rets: nothing
void Snake::draw_head_on_board(char board[ROWS][COLS])
{
	board[rows][cols] = headDirection;
}

// snake_munchies() -- places the different foods on the board and gives them
// a value
// 	args: a character, board
//	rets: nothing
void Snake::snake_munchies(char board[ROWS][COLS])
{
	if (board[rows][cols] == BUG_SYM){
		place_snack(BUG_SYM,board);
		EU += BUG_VAL;
	}
	else if (board[rows][cols] == EGG_SYM){
		place_snack(EGG_SYM,board);
		EU += EGG_VAL;
	}
}

