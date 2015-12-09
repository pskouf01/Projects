////////////////////////////////msnake.h/////////////////////////////////////
//	By: Panos Skoufalos
//    Date: November 8th, 2015
// Purpose: This file contains constants for snack symbols and the function
//	    initialization for the placement of those snacks.	

#ifndef MSNAKE_H
#define MSNAKE_H

const char BUG_SYM = 'X';
const char EGG_SYM = 'O';
void place_snack(char snackType, char board[][COLS]);

#endif
