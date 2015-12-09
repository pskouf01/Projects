#include <iostream>
using namespace std;
#include "termfuncs.h"

/*
 * 2snake version 1.0
 * This program runs a version of the famous game, Snake
 * The catch here is that you have two snakes competing against each other
 * The program inquires the user for information regarding the snake and
 * then runs the game.
 * Each snake starts in the middle of the board facing away from each other
 * and with 60 Energy Units. 
 * Every time the snake moves forward you lose an Energy Unit
 * The Bug symbol is X and the has a value of 25 Energy Units
 * The Egg symbol is an O and has a value of 15 Energy Units
 */

const int 	ROWS    = 24;		
const int 	COLS    = 63;		
const int	EU_INIT = 60;
const char 	HORIZONTAL_BORDERS = '-';
const char 	VERTICAL_BORDERS = '|';
const char 	CORNERS = '+';
const char 	HEAD_DIRECTIONS[4] = {'^','<','>','v'}; 

const char	BUG_SYM = 'X';
const int	BUG_VAL = 25;
const char	EGG_SYM = 'O';
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
	void	set_color(string fg, string bg);	// not required

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
	char s_head;
	int  headDirection;
	void rotate_head(char input, char[ROWS][COLS]);
	bool runs_into_self(char board[][COLS]);
	void snake_munchies(char board[ROWS][COLS]);
	void move_forward(char [ROWS][COLS]);
	void mover(char board[ROWS][COLS]);

};

// -------------------------------------------------------------
// ----- Main Game that uses a Snake ---------------------------
// -------------------------------------------------------------
/*
 * multi-snake game
 */

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

//    ---- note: DO NOT MODIFY main() AT ALL ----
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
		draw_board(board);
		print_status();
		return alive = false;
	}
	if (EU == 0){
		board[rows][cols] = headDirection;
		draw_board(board);
		print_status();
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

