//////////////////////////////msnake_main.cpp/////////////////////////////
//	By: Panos Skoufalos
//    Date: November 8th, 2015
// Purpose: The purpose of this program is to call the main function of a 
// 	    snake program that calls all functions outside of a class Snake.

#include<iostream>
#include"termfuncs.h"
#include"snake.h"
#include"msnake.h"
using namespace std;

void	place_snack(char, char[ROWS][COLS]);
string	play_game(char[ROWS][COLS]);
void	display(char [ROWS][COLS], Snake, Snake);
string	compute_outcome(Snake, Snake);
void 	setup_board(char[ROWS][COLS]);
void 	report(string result);
void 	draw_board(char[ROWS][COLS]);
void 	rotate_head(char input);
void 	place_snack(char, char board[ROWS][COLS]);
bool    check_location_snack(char board[][COLS], int rows, int cols);

int main()
{
	char	board[ROWS][COLS];
	string	result;

	setup_board(board);
	result = play_game(board);
	report(result);
}
//
// play_game -- run a game of multi-snake
//    args: a board ready to use
//    rets: "X wins" or "X died" where X is name of snake
//    note: USE THIS MAIN UNCHANGED FOR PHASE 0
//    note: FOR PHASE 1, move setup_snake into class 
//
string play_game(char b[ROWS][COLS])
{
	Snake	s0, s1;		// the players
	char	input;
	string	outcome = "";
	// set up the snakes and put food on board
	screen_clear();
	s0.setup_snake(0, ROWS/2-1, COLS/2, '^', EU_INIT);
	s1.setup_snake(1, ROWS/2  , COLS/2, 'v', EU_INIT);
	s0.draw_head_on_board(b);
	s1.draw_head_on_board(b);
	place_snack(BUG_SYM, b);
	place_snack(EGG_SYM, b);
	// play the game
	while( s0.is_alive() && s1.is_alive() )
	{
		display(b, s0, s1);
		input = getachar();
		s0.process_key(input, b);
		s1.process_key(input, b);
	}
	display(b, s0,s1);
	outcome = compute_outcome(s0, s1);
	return outcome;
}
// compute_outcome -- determine if someone won 
//  args: two snakes
//  rets: "X wins" OR  "X died"
//  note: to win, a snake must be alive AND have a higher score
//
string compute_outcome(Snake a, Snake b)
{
	string aName = a.get_name();
	string bName = b.get_name();
	string result;
	if (a.is_alive() == false){
			if (a.get_score() <= b.get_score()){
				result = bName + " wins.";
			}else {
				result =aName + " died.";
			}
       	}
	else if(b.is_alive() == false){
       		if (b.get_score() <= a.get_score()){
       			result = aName + " wins.";
       		}else{ 
       			result = bName + " dies.";
       		}
       	}
       	return result;
}

// display - show current state of game including board and snake status
//  args: the board, the snakes
//  rets: nothing
//  does: sends info to cout
//
void display(char board[ROWS][COLS], Snake a, Snake b)
{
	draw_board(board);
	a.print_status();
	b.print_status();
}
///////////////////////////////////////////////////////////////////////////
///////////////////FUNCTIONS OUTSIDE OF CLASS/////////////////////////////
//////////////////////////////////////////////////////////////////////////

// place_snack() -- gives the snacks an actual location on the board
//	args: two character types, board and snack_type
//	rets: nothing
void place_snack(char snack_type, char board[][COLS])
{
	int rows;
	int cols;
	bool Alive = false;
	while(Alive == false){
		rows = random_int(1, ROWS-2);
		cols = random_int(1, COLS-2);
		Alive = check_location_snack(board,rows,cols);
	}
	board[rows][cols] = snack_type;
}

// check_location_snack() -- checks the location of the snack and if it has 
// been eaten
//	args: a character, board and two integers
//	rets: a boolean either true or false
bool check_location_snack(char board[][COLS], int rows, int cols)
{
	bool false_location = false;
	if( board[rows][cols] == ' '){
		false_location = true;
	}
	return false_location;
}
//setup_board() - sets up the board for the snake
//	args: a character, board
//	rets: nothing
void setup_board(char board[ROWS][COLS])
{
	for (int i = 0; i < ROWS; i++){
		for(int k = 0; k < COLS; k++){
			board[i][k] = ' ';
		}
	}
	for (int i = 0; i < COLS-1; i++){
		board[0][i] = HORIZONTAL_BORDERS;
		board[ROWS-1][i] = HORIZONTAL_BORDERS;
	}
	for (int i = 0; i < ROWS-1; i++){
		board[i][0]= VERTICAL_BORDERS;
		board[i][COLS-1] = VERTICAL_BORDERS;
	}
	board[0][0] = CORNERS;
	board[0][COLS-1] = CORNERS;
	board[ROWS-1][COLS-1] = CORNERS;
	board[ROWS-1][0] = CORNERS;
	draw_board(board);
}
//draw_board() - draws set up board 
//	args: a character, board
//	rets: nothing
void draw_board(char board[ROWS][COLS])
{
	screen_clear();
	for (int i = 0; i < ROWS; i++){
		for (int k = 0; k < COLS; k++){
			cout << board[i][k];
		}
		cout << endl;
	}
}
//report() - reports the results
//	args: a string
//	rets: nothing
void report(string result)
{
	cout << "Game over. " << result << endl;
}
