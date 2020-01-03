#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#include<string.h>
#include"conio2.h"

#ifndef SCRABBLE_H
#define SCRABBLE_H

//constant variables(changable)//
#define BOARD_SIZE 15		    //number of fields on board (width and height)
#define BOARD_POS_RIGHT 70		//position of the board from RIGHT screen border
#define BOARD_POS_TOP 2			//position of the board from top screen border

#define POCKET_SIZE 7			//maximum amount of letters in pocket
#define LETTERS_NUMBER 100		//number of letters  used in the game (connected with n_letters)

#define MENU_POS_RIGHT 2		//position of the menu from RIGHT screen border
#define MENU_POS_TOP 2			//position of the menu from top screen border

#define RIGHT 2					//directions of the words
#define DOWN 1

//multipliers for each bonus field
#define MULTIPLIER_WORD_RED 3
#define MULTIPLIER_WORD_MAGENTA 2
#define MULTIPLIER_CHAR_BLUE 3
#define MULTIPLIER_CHAR_LIGHTCYAN 2

#define DEFAULT_DICTIONARY "dictionary.txt"				//default dictionary filenmae (have to be placed in the same directiory as .exe file)
#define DICTIONARY_LOADING "Loading dictionary..."
#define DICTIONARY_ERROR "Dictionary error."
#define MEMORY_ERROR "Memory error. Closing. "

enum n_letters {				//amounts of letters(while changing, it is needed to change LETTERS_NUMBER proportionately)
	blank = 2,
	e = 12,
	a = 9, i = 9,
	o = 8,
	n = 6, r = 6, t = 6,
	l = 4, s = 4, u = 4, d = 4,
	g = 3,
	b = 2, c = 2, m = 2, p = 2, f = 2, h = 2, v = 2, w = 2, y = 2,
	k = 1, j = 1, x = 1, q = 1, z = 1,
};
enum v_letters {				//value of points for every letter
	e_v = 1, a_v = 1, i_v = 1, o_v = 1, n_v = 1, r_v = 1, t_v = 1, l_v = 1, s_v = 1, u_v = 1,
	d_v = 2, g_v = 2,
	b_v = 3, c_v = 3, m_v = 3, p_v = 3,
	f_v = 4, h_v = 4, v_v = 4, w_v = 4, y_v = 4,
	k_v = 5,
	j_v = 8, x_v = 8,
	q_v = 10, z_v = 10,
};
//constant variables(seriously constant)//	
#define POSITION_COURSORINFO_RIGHT 28			//value of x coursor info position in legend
#define POSITION_COURSORINFO_TOP 18				//value of y coursor info position in legend
#define POSITION_POCKETINFO_TOP 25				//value of y pocket position in legend
#define POSITION_INPUT_TOP (23+MENU_POS_TOP)	//value of y input position in legend

//different msgs displayed in output_draw
#define NO_MSG 0								
#define MSG_HELLO 1
#define MSG_NOTPOSSIBLE 2
#define MSG_REPLACED 3
#define MSG_PLACED 4
#define MSG_FILENAME 5
#define MSG_SAVED 6
#define MSG_SAVED_ERROR 7
#define MSG_LOADED 8
#define MSG_LOADED_ERROR 9
#define MSG_WORD_FOUND 10
#define MSG_WORD_MISSING 11
#define MSG_LEARNMODE_OFF 12
#define MSG_LEARNMODE_ON 13
#define MSG_REPLACE 14
#define MSG_WORD_INPUT 15
#define MSG_CANCELED 16
#define MSG_WORD_SETPOS 17
////

//structures
struct pocket_letter {							//struct for letters in pocket
	char value;
	bool selected;
};

struct field_letter {							//struct for letter in new created word
	char value;
	bool inpocket;
	bool wellplaced;
	bool newonboard;
};

struct list {
	char* word;
	int lenght;
	struct list* next;
};

struct game_status {
	char board[BOARD_SIZE][BOARD_SIZE];					//array which contains content of the board
	char bonuses[BOARD_SIZE][BOARD_SIZE];				//array which contains information about special fields
	char letters_bag[LETTERS_NUMBER];					//array which contains all letters
	int points;											//current player points
	int turn;											//current turn
	int placed_words;									//current amount of the words on the board
	int pocket_replacer;								//current position from which letters in bag should be replaced
	list* list;											//pointer to dictionary's head
	bool learn_mode;
};

//functions//
void screen_draw(struct pocket_letter pocket[], struct game_status &status);															//render whole screen
void legend_draw(struct pocket_letter pocket[]);																						//render legend
void pocket_draw(struct pocket_letter pocket[]);																						//render current pocket state
void board_draw(struct game_status &status);																							//render current board state
void draw_letters();																													//draw row of letters with the size of the BOARD_SIZE
void output_draw(struct game_status &status, int msg);																					//draw current points and msg under the legend
//
void coursor_move(int &x, int &y, int input);																							//move coursor by pressing arrow keys
void coursor_pos(int x, int y);																											//dipslay current coursor pos in legend
//
void bag_shuffle(struct game_status &status);																							//shuffle all letters placed in the bag
void pocket_replace(struct pocket_letter pocket[], struct game_status &status);															//if 1-7 key is clicked, change letter's selected value to true
void pocket_fulfill(struct pocket_letter pocket[], struct game_status &status);															//swap all ' ' and selected=true letters to letters from bag 
bool letters_bag_check(struct game_status &status);																						//check if there is any letter in letters bag
//
bool word_create(struct pocket_letter pocket[], struct game_status &status);															//create new word
void letter_check(struct pocket_letter pocket[], struct field_letter new_word[], char input, int size);									//check if letters that are going to be used are available
void word_status_msg(struct game_status & status, bool check);
bool word_check_global(struct field_letter new_word[], struct pocket_letter pocket[], int size, struct game_status &status);										//check if word is placeable in any postion of the board
bool word_check_position(struct field_letter new_word[], struct pocket_letter pocket[], int size, struct game_status &status, int x, int y, int direction);			//check if word is placeable in given position
bool blank_check(struct pocket_letter pocket[]);																						//check if there is a blank in the pocket
void blank_reset(struct pocket_letter pocket[]);
void word_target(struct field_letter new_word[], struct pocket_letter pocket[], int size, struct game_status &status);					//start proccess of placing the word to the board
bool board_dictionary_check(struct game_status &status, struct field_letter new_word[], int x, int y, int size, int direction);										//check if every word on board is in dictionary
char letter_dictionary_check(struct game_status &status, struct field_letter new_word[], int x, int y, int size, int direction, int j, int i);						//check which character will be at the given pos after the word will be placed
void word_place(struct field_letter new_word[], struct pocket_letter pocket[], int size, struct game_status &status, int x, int y, int direction);					//finish placing the word to board by swapping letters

int points_count(struct field_letter new_word[], int size, int x, int y, struct game_status &status, int direction);					//count points for placed word with all bonuses included			
int points_for_letter(char ch);																											//return points for given letter
void points_display(struct game_status &status, struct field_letter new_word[], int size, int x, int y, int direction);					//display points for given word placed at given position
//
char* file_input(int &size);																											//input file name
void game_save(struct game_status &status, struct pocket_letter pocket[]);																//save current state of the games to file
void game_load(struct game_status &status, struct pocket_letter pocket[]);																//load game form the file if exists
//
list* load_dictionary(char filename[]);																									//load dictionary from the file
list* list_add(char tab[], int size);																									//add element at the end of the list
list* list_sorted_add(char tab[], int size, list* p);																					//add element in the sorted place of the list (depending of size)
list* list_lenght_search(list* head, int size);																							//find place in the list where word of given size should be placed 
bool list_word_search(list* head, char word[], int size);																				//search for specified word in list
//
void swap(int a, int b, char tab[]);																									//replace two values in given array
void swap_pocket(int a, int b, struct pocket_letter pocket[], char tab2[]);																//replace two values in two given arrays
void swap_board(int a, int bx, int by, struct pocket_letter pocket[], struct game_status &status);										//replace two values in two given arrays, but one is two-dimensional
void reset_values(struct pocket_letter pocket[], struct game_status &status, int &coursor_x, int &coursor_y);							//reset all values to default, to start new game
void int_to_char(int number);																											//prints given int <999, in the current pos on the screen
char upper_to_lower(char letter);																										//if passed char is capital letter, change it to lower case letter and return
char* file_path(char *argv, char * filename);

////
#endif // ! scrabble_h


