// Scrabble game

#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#include<string.h>
#include"scrabble.h"

int main(int argc, char* argv[]) {

	//variables//
	game_status status;

	char input;
	char* directory;
	int coursor_x, coursor_y;								//position of the cursor

	pocket_letter pocket[POCKET_SIZE];
	////

#ifndef __cplusplus
	Conio2_Init();
#endif

	settitle("ScrabbleProject");					//set window title

	//load dictionary from passed parameters//
	gotoxy(1, 1);
	cputs(DICTIONARY_LOADING);
	if (argc > 1)
	{
		directory = file_path(argv[0], argv[1]);			//generate file path and pass it to load_dictionary
		status.list = load_dictionary(directory);
	}
	else
	{
		char d_default[] = DEFAULT_DICTIONARY;				//if there was no parameter, set default dictionary
		directory = file_path(argv[0], d_default);
		status.list = load_dictionary(directory);
	}
	if (status.list->next != NULL)
	{

		reset_values(pocket, status, coursor_x, coursor_y);	//set all values to default

		do {

			_setcursortype(_NOCURSOR);						//hide coursor when drawing, not to create irritating screen glitches
			pocket_fulfill(pocket, status);					//fullfill pocket to 7 letters
			screen_draw(pocket, status);					//update screen info
			coursor_pos(coursor_x, coursor_y);				//update coursor pos in the legend since last move
			_setcursortype(_SOLIDCURSOR);					//show coursor back
			gotoxy(coursor_x, coursor_y);

			input = getch();										//get key from user

			if (input == 0) {										//if key was arrow, move
				coursor_move(coursor_x, coursor_y, input);
			}
			else if (input == 'i')									//if key was 'i',start creating new word
			{
				output_draw(status, MSG_WORD_INPUT);
				if (word_create(pocket, status) == false)			//if creating was not possible, show proper msg in output
				{
					output_draw(status, MSG_NOTPOSSIBLE);
				}
			}
			else if (input == 'w') {								//if key was 'w', start replacing letters in pocket
				output_draw(status, MSG_REPLACE);
				pocket_replace(pocket, status);
			}
			else if (input == 'n')									//if key was 'n', start new game by reseting all values to default
			{
				reset_values(pocket, status, coursor_x, coursor_y);
			}
			else if (input == 's')									//if key was 's', save game to file
			{
				output_draw(status, MSG_FILENAME);
				game_save(status, pocket);
			}
			else if (input == 'l')									//if key was 'l', load game from file
			{
				output_draw(status, MSG_FILENAME);
				game_load(status, pocket);
			}
			else if (input == 't')									//if key was 't', swicth learn mode to true or false and show proper msg
			{
				if (status.learn_mode == true)
				{
					status.learn_mode = false;
					output_draw(status, MSG_LEARNMODE_OFF);
				}
				else {
					status.learn_mode = true;
					output_draw(status, MSG_LEARNMODE_ON);
				}
			}
		} while (input != 'q');										//if key was 'q', quit
		clrscr();
	}
	else
	{
		cputs(DICTIONARY_ERROR);
	}
	return 0;
}