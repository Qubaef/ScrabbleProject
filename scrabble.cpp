#include"scrabble.h"

void screen_draw(struct pocket_letter pocket[], struct game_status &status) {		//render whole screen
	clrscr();						//clear screen
	legend_draw(pocket);			//draw legend
	board_draw(status);				//draw board
	output_draw(status, NO_MSG);	//draw current points and msg
}

//

void legend_draw(struct pocket_letter pocket[]) {			//render legend

	gotoxy(MENU_POS_RIGHT, MENU_POS_TOP);
	//
	cputs("=====Jakub Fedorowicz 176087=====");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("FinalBuild a,b,c,d,e,f,g,h,i,j,k");				//display implemented points
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	//
	textattr(240);											//set background to white, and font to black
	cputs("Scrabble Project");
	textattr(15);											//set background to black, and font to white
	gotoxy(MENU_POS_RIGHT, wherey() + 1);					//move coursor one row down
	//
	cputs("Menu:");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("strzalki  = ruch kursorem");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("q         = wyjscie");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("n         = nowa gra");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("enter     = potwierdz i zakoncz");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("i         = nowe slowo");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("esc       = anuluj");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("backspace = kasuj ostatnia litere");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("0         = pionowo/poziomo");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("w         = wymien zaznaczone kafelki");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("1234567   = zaznacz kafelki do wymiany");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("s         = zapisz gre");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("l         = wczytaj ostatnia gre");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("t         = tryb nauki");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	////
	textbackground(LIGHTCYAN);
	cputs("chX");
	int_to_char(MULTIPLIER_CHAR_LIGHTCYAN);
	//
	textbackground(BLUE);
	cputs("chX");
	int_to_char(MULTIPLIER_CHAR_BLUE);
	//
	textbackground(LIGHTMAGENTA);
	cputs("wsX");
	int_to_char(MULTIPLIER_WORD_MAGENTA);
	//
	textbackground(RED);
	cputs("wsX");
	int_to_char(MULTIPLIER_WORD_RED);
	//
	textbackground(BLACK);
	////
	gotoxy(MENU_POS_RIGHT, wherey() + 1);
	cputs("Aktualna pozycja wskaznika: ");

	//
	pocket_draw(pocket);									//render current pocket size
}

void pocket_draw(struct pocket_letter pocket[]) {						//render current pocket state

	gotoxy(MENU_POS_RIGHT, MENU_POS_TOP + POSITION_POCKETINFO_TOP);		 //draw menu under informations
	cputs("Twoje litery: ");
	gotoxy(MENU_POS_RIGHT, wherey() + 1);

	for (int i = 0; i < POCKET_SIZE; i++) {
		gotoxy(MENU_POS_RIGHT + (i * 3), wherey() + 1);

		putch(' ');
		if (pocket[i].selected == true) { textbackground(BLUE); }		//check if letter was selected and if was, change its background color to blue
		else if (pocket[i].selected == false) { textbackground(BLACK); }
		putch(pocket[i].value);
		textbackground(BLACK);
		putch(' ');

		gotoxy(MENU_POS_RIGHT + (i * 3), wherey() + 1);					 //draw 3*'=' over and under each letter
		cputs("===");
		gotoxy(MENU_POS_RIGHT + (i * 3), wherey() - 2);
		cputs("===");
	}
}

void board_draw(struct game_status &status) {		//render current board state
	textattr(240);									//set background to white, and font to black
	gotoxy(BOARD_POS_RIGHT, BOARD_POS_TOP - 1);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		gotoxy(BOARD_POS_RIGHT, wherey() + 1);
		if (i == 0)									//if it is first row, draw row of letters
		{
			draw_letters();
			gotoxy(BOARD_POS_RIGHT, wherey() + 1);
		}
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (j == 0)
				int_to_char(i + 1);;				//display number of current row
			putch('|');
			if (status.bonuses[i][j] == '#')
				textbackground(YELLOW);
			else if (status.bonuses[i][j] == '2')	//char x MULTIPLIER
				textbackground(LIGHTCYAN);
			else if (status.bonuses[i][j] == '3')	//char x MULTIPLIER
				textbackground(BLUE);
			else if (status.bonuses[i][j] == '4')	//word x MULTIPLIER
				textbackground(RED);
			else if (status.bonuses[i][j] == '5')	//word x MULTIPLIER
				textbackground(LIGHTMAGENTA);
			if (status.board[i][j] == ' ') {
				putch('_');
			}
			else if (status.board[i][j] >= 'a' && status.board[i][j] <= 'z')
			{
				textbackground(YELLOW);
				putch(status.board[i][j]);
			}
			textbackground(WHITE);
			if (j == (BOARD_SIZE - 1))
			{
				putch('|');
				int_to_char(i + 1);					//display number of current row
			}
		}
		if (i == (BOARD_SIZE - 1))					//if it is last row, draw row of letters
		{
			gotoxy(BOARD_POS_RIGHT, wherey() + 1);
			draw_letters();
		}
	}
	textattr(15);	 //set background to black, and font to white
}

void draw_letters() {						//draw row of letters with the size of the BOARD_SIZE
	gotoxy(wherex() + 2, wherey());
	for (int i = 0; i < BOARD_SIZE; i++) {
		putch('|');
		putch('A' + i);
	}
	putch('|');
}

void output_draw(struct game_status &status, int msg) {				//draw current points and msg under the legend
	gotoxy(MENU_POS_RIGHT, POSITION_INPUT_TOP - 2);
	cputs("Punkty: ");
	int_to_char(status.points);
	////
	static int current_msg;
	if (msg != 0)
		current_msg = msg;
	gotoxy(MENU_POS_RIGHT, POSITION_INPUT_TOP - 1);
	cputs("                                                   ");
	gotoxy(MENU_POS_RIGHT, POSITION_INPUT_TOP - 1);
	switch (current_msg)
	{
	case MSG_HELLO:
		cputs("Nowa gra rozpoczeta! Wybierz klawisz z instrukcji!");
		break;
	case MSG_NOTPOSSIBLE:
		cputs("Brak mozliwosci wstawienia slowa!");
		break;
	case MSG_REPLACED:
		cputs("Zamieniono wybrane litery!");
		break;
	case MSG_PLACED:
		cputs("Wstawiono slowo!");
		break;
	case MSG_FILENAME:
		cputs("Podaj nazwe pliku.");
		break;
	case MSG_SAVED:
		cputs("Zapisano!");
		break;
	case MSG_SAVED_ERROR:
		cputs("Blad zapisu!");
		break;
	case MSG_LOADED:
		cputs("Wczytano!");
		break;
	case MSG_LOADED_ERROR:
		cputs("Blad wczytywania!");
		break;
	case MSG_WORD_FOUND:
		cputs("Slowo jest w slowniku!");
		break;
	case MSG_WORD_MISSING:
		cputs("Slowo nie jest w slowniku!");
		break;
	case MSG_LEARNMODE_OFF:
		cputs("Tryb nauki nieaktywny!");
		break;
	case MSG_LEARNMODE_ON:
		cputs("Tryb nauki aktywny!");
		break;
	case MSG_REPLACE:
		cputs("Wybierz litery do zamiany!");
		break;
	case MSG_WORD_INPUT:
		cputs("Wprowadz slowo!");
		break;
	case MSG_CANCELED:
		cputs("Anulowano!");
		break;
	case MSG_WORD_SETPOS:
		cputs("Ustaw slowo na planszy!");
		break;
	}
}

//

void coursor_move(int &x, int &y, int input) {				//move coursor by pressing arrow keys
	input = getch();
	if (input == 0x48) y--;									//if down arrow is placed
	else if (input == 0x50) y++;							//if up arrow is placed
	else if (input == 0x4b) x -= 2;							//if left arrow is placed
	else if (input == 0x4d) x += 2;							//if right arrow is placed

	if (x > (BOARD_POS_RIGHT + BOARD_SIZE * 2 + 2)) {		//if coursor is placed further than right border of the board, place him back inside
		x -= 2;
	}
	if (x < (BOARD_POS_RIGHT + 3)) {						//if coursor is placed futher than left border of the board, place him back inside
		x += 2;

	}
	if (y > (BOARD_POS_TOP + BOARD_SIZE)) {					//if coursor is placed futher than bottom border of the board, place him back inside
		y--;
	}
	if (y < (BOARD_POS_TOP + 1)) {							//if coursor is placed futher than upper border of the board, place him back inside
		y++;
	}

}

void coursor_pos(int x, int y) {				//dipslay current coursor pos in legend
	x = (x - BOARD_POS_RIGHT - 3) / 2;																	//count coursor position basing on position on screen//
	y = y - BOARD_POS_TOP;
	gotoxy(MENU_POS_RIGHT + POSITION_COURSORINFO_RIGHT, MENU_POS_TOP + POSITION_COURSORINFO_TOP);		//show coursor pos in specified place in legend
	putch('A' + x);
	putch(' ');
	int_to_char(y);
}

void bag_shuffle(struct game_status &status) {								//shuffle all letters placed in the bag
	int rand_pos;
	srand(time(NULL));
	for (int i = 0; i < LETTERS_NUMBER; i++)
	{
		rand_pos = rand() % LETTERS_NUMBER;
		swap(i, rand_pos, status.letters_bag);
	}
}

void pocket_replace(struct pocket_letter pocket[], struct game_status &status) {		//if 1-7 key is clicked, change letter's selected value to true
	int input;

	do {														//if one of the buttons 1234567 was pressed, select its letter
		legend_draw(pocket);
		input = getch();

		if (input >= '1' && input <= '1' + POCKET_SIZE)
		{
			if (pocket[(int)(input - '1')].selected == false)
			{
				pocket[(int)(input - '1')].selected = true;
			}
			else if (pocket[(int)(input - '1')].selected == true)
			{
				pocket[(int)(input - '1')].selected = false;
			}
		}
		else if (input == 0x0d || input == 'w')					//if enter or 'w' was pressed, confirm action and replace selected letters
		{
			pocket_fulfill(pocket, status);
			output_draw(status, MSG_REPLACED);					//show msg that letters have been replaced
			for (int i = 0; i < POCKET_SIZE; i++)
			{
				pocket[i].selected = false;
			}
			break;
		}
		else if (input == 0x1b)									//if esc was pressed, cancel all selections and go back to board
		{
			for (int i = 0; i < POCKET_SIZE; i++)
			{
				pocket[i].selected = false;
			}
			output_draw(status, MSG_CANCELED);					//show information that action was canceled
			break;
		}

	} while (true);
}

void pocket_fulfill(struct pocket_letter pocket[], struct game_status &status) {		//swap all ' ' and selected=true letters to letters from bag 
	int none = 0;
	bool letters_in_bag;
	do {																				//replace all ' ' in pocket to letters from bag, if there are any
		letters_in_bag = letters_bag_check(status);
		if (letters_in_bag)
		{
			if (pocket[none].value == ' ' || pocket[none].selected == true) {
				if (status.pocket_replacer < LETTERS_NUMBER) {
					pocket[none].selected = false;
					swap_pocket(none, status.pocket_replacer, pocket, status.letters_bag);
					status.pocket_replacer++;
				}
				else
				{
					status.pocket_replacer = status.pocket_replacer - LETTERS_NUMBER;
				}
			}
			else {
				none++;
			}
		}
	} while (none < POCKET_SIZE && letters_in_bag);
}

bool letters_bag_check(struct game_status &status) {		//check if there is any letter in letters bag
	for (int i = 0; i < LETTERS_NUMBER; i++)
	{
		if (status.letters_bag[i] != ' ')
		{
			return true;
		}
	}
	return false;
}

//

bool word_create(struct pocket_letter pocket[], struct game_status &status) {
	bool check;
	char input;
	int size = 0;
	field_letter* new_word1 = new field_letter[size];
	field_letter* new_word2 = new field_letter[size + 1];
	char * new_char = new char[size];

	_setcursortype(_SOLIDCURSOR);

	do
	{
		gotoxy(MENU_POS_RIGHT, POSITION_INPUT_TOP);
		cputs("Wprowadzanie: ");
		gotoxy(MENU_POS_RIGHT + 14 + size, POSITION_INPUT_TOP);

		input = getch();
		//after letter was pressed//
		if (input >= 'a' && input <= 'z' && size % 2 == 0)		//create array of exact same size as an word size
		{
			delete[] new_word2;
			delete[] new_char;
			new_word2 = new field_letter[(size + 1)];			//crate array one char larger
			new_char = new char[size + 2];

			for (int i = 0; i < size; i++)
			{
				new_word2[i] = new_word1[i];					//copy all values form last array
				new_char[i] = new_word1[i].value;
			}

			letter_check(pocket, new_word2, input, size);		//check if the added letter is available in pocket, if it is, it will be printed on green background
			new_word2[size].value = input;						//copy new letter to last pos of the array
			new_char[size] = input;
			new_char[size + 1] = NULL;
			size++;
			check = list_word_search(status.list, new_char, size);

			if (status.learn_mode)
			{
				word_status_msg(status, check);
			}

		}
		else if (input >= 'a' && input <= 'z' && size % 2 == 1)
		{
			delete[] new_word1;
			delete[] new_char;
			new_word1 = new field_letter[(size + 1)];			//crate array one char larger
			new_char = new char[size + 2];

			for (int i = 0; i < size; i++)
			{
				new_word1[i] = new_word2[i];					//copy all values form last array
				new_char[i] = new_word2[i].value;
			}

			letter_check(pocket, new_word1, input, size);		//check if the added letter is available in pocket, if it is, it will be printed on green background
			new_word1[size].value = input;						//copy new letter to last pos of the array
			new_char[size] = input;
			new_char[size + 1] = NULL;
			size++;
			check = list_word_search(status.list, new_char, size);

			if (status.learn_mode)
			{
				word_status_msg(status, check);
			}
		}
		//if backspace was pressed//
		else if (input == 0x08 && size % 2 == 0)
		{
			if (size != 0)										//if word's length is currently 0, do not use backspace cause it is nothing to remove
			{
				delete[] new_word2;
				delete[] new_char;
				new_word2 = new field_letter[(size - 1)];
				new_char = new char[size];

				for (int i = 0; i < size - 1; i++)
				{
					new_word2[i] = new_word1[i];				//copy all values form last array
					new_char[i] = new_word1[i].value;
				}

				new_char[size - 1] = NULL;
				size--;
				check = list_word_search(status.list, new_char, size);

				if (status.learn_mode)
				{
					word_status_msg(status, check);
				}
			}
		}
		else if (input == 0x08 && size % 2 == 1)
		{
			delete[] new_word1;
			delete[] new_char;
			new_word1 = new field_letter[(size - 1)];
			new_char = new char[size];

			for (int i = 0; i < size - 1; i++) {
				new_word1[i] = new_word2[i];					//copy all values form last array
				new_char[i] = new_word2[i].value;
			}

			new_char[size - 1] = NULL;
			size--;
			check = list_word_search(status.list, new_char, size);

			if (status.learn_mode)
			{
				word_status_msg(status, check);
			}

		}
		//draw current state of the word
		if (input != 0x1b) {										//if esc wasnt prssed
			gotoxy(MENU_POS_RIGHT + 14, POSITION_INPUT_TOP);		//erase last last state of the word

			for (int i = 0; i < size + 2; i++)
			{
				putch(' ');
			}

			gotoxy(MENU_POS_RIGHT + 14, POSITION_INPUT_TOP);

			//write word with colors green/red informing user about availability of every leter
			if (size % 2 == 0 && size > 0)
			{
				for (int i = 0; i < size; i++)
				{
					if (new_word1[i].inpocket == true)
					{
						textbackground(GREEN);
					}
					else textbackground(RED);
					putch(new_word1[i].value);
					textbackground(BLACK);
				}
			}
			else if (size % 2 == 1 && size > 0)
			{
				for (int i = 0; i < size; i++)
				{
					if (new_word2[i].inpocket == true)
					{
						textbackground(GREEN);
					}
					else textbackground(RED);
					putch(new_word2[i].value);
					textbackground(BLACK);
				}
			}
			gotoxy(wherex() + size, wherey());
		}
	} while (input != 0x0d && input != 0x1b);					//if enter of esc was pressed, finish creating a word

	delete[] new_char;
	field_letter* new_word = new field_letter[size + 1];
	new_char = new char[size + 1];

	new_word[size].value = NULL;
	new_char[size] = NULL;

	for (int i = 0; i < size; i++)
	{
		if (size % 2 == 0)
		{
			new_word[i] = new_word1[i];
			new_char[i] = new_word1[i].value;
			new_word[i].wellplaced = false;
			new_word[i].newonboard = false;

		}
		if (size % 2 == 1)
		{
			new_word[i] = new_word2[i];
			new_char[i] = new_word2[i].value;
			new_word[i].wellplaced = false;
			new_word[i].newonboard = false;
		}
	}

	check = list_word_search(status.list, new_char, size);

	delete[]new_word1;
	delete[]new_word2;
	delete[]new_char;

	//call word_target and pass new_word with its parameters, if enter was pressed and word is pleacable
	if (check == true && input == 0x0d)
	{
		if (word_check_global(new_word, pocket, size, status) == true)									//if enter was pressed and word is placable, go choose its position in word target
		{
			word_status_msg(status, check);
			word_target(new_word, pocket, size, status);
			delete[] new_word;
			return true;
		}
	}
	else if (input != 0x1b)																				//if esc wasn't pressed, return true and finish
	{
		delete[] new_word;
		return false;
	}
	if (input == 0x1b)
	{
		output_draw(status, MSG_CANCELED);
	}
	delete[] new_word;

	return true;
}

void letter_check(struct pocket_letter pocket[], struct field_letter new_word[], char input, int size) {
	int amount_pocket = 0;			//how many times inputed letter appears in the pocket
	int amount_word = 0;			//how many times inputed letter appears in the written word

	for (int i = 0; i < POCKET_SIZE; i++) {
		if (input == pocket[i].value)
		{
			amount_pocket++;		//when new letter same as input is found in pocket, add it the amount
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (input == new_word[i].value)
		{
			amount_word++;			//when new letter same as input is found in new word, add it the amount
		}
	}
	if (amount_pocket > amount_word)
	{
		new_word[size].inpocket = true;
	}
	else {
		new_word[size].inpocket = false;
	}
}

void word_status_msg(struct game_status & status, bool check)
{
	if (check == true)
	{
		output_draw(status, MSG_WORD_FOUND);			//display msg thet word is in dictionary
	}
	else
	{
		output_draw(status, MSG_WORD_MISSING);			//display msg thet word is not in dictionary
	}
}

bool word_check_global(struct field_letter new_word[], struct pocket_letter pocket[], int size, struct game_status &status) {
	bool found_1 = true;
	bool found_2 = false;
	bool* found = new bool[size];

	for (int l = 0; l < size; l++)									//first check if letters from word, that are not in pocket, are somewhere on the board
	{
		if (new_word[l].inpocket == false)
		{
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (status.board[i][j] == new_word[l].value)
					{
						found[l] = true;
					}
				}
			}
		}
		else
		{
			found[l] = true;
		}
	}

	for (int l = 0; l < size; l++)
	{
		if (found[l] == false)
		{
			found_1 = false;
		}
	}
	////
	if (found_1 == true)											//if missing letters are on the board, check every position on the board and try to find any position where word can be placed
	{
		for (int i = 0; i < BOARD_SIZE && found_2 == false; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (j + size <= BOARD_SIZE)
				{
					if (word_check_position(new_word, pocket, size, status, i, j, RIGHT) == true)
					{
						if (board_dictionary_check(status, new_word, j, i, size, RIGHT) == true)		//if it is possible to place word in a position, also check if all words from the board are in dictionary
						{
							found_2 = true;			//if they are, set found as true
						}
					}
				}
				if (i + size <= BOARD_SIZE)
				{
					if (word_check_position(new_word, pocket, size, status, i, j, DOWN) == true)
					{
						if (board_dictionary_check(status, new_word, j, i, size, DOWN) == true)			//if it is possible to place word in a position, also check if all words from the board are in dictionary
						{
							found_2 = true;			//if they are, set found as true
						}
					}
				}
			}
			if (found_2 == true)					//if posiiton has been already found, break the loop, cause there is no point to check rest of the board
			{
				break;
			}
		}
	}
	delete[] found;
	return found_2;									//if allowed position was found, returns true
}

bool word_check_position(struct field_letter new_word[], struct pocket_letter pocket[], int size, struct game_status &status, int x, int y, int direction)
{
	int sum = 0;
	field_letter* copy_word = new field_letter[size];
	bool wellplaced = true;
	bool newonboard = true;
	bool correct;

	for (int i = 0; i < size; i++)
	{
		copy_word[i] = new_word[i];
	}

	if (status.placed_words == 0)									//if placed words is 0, check only if any letter is in point (BOARD_SIZE/2,BOARD_SIZE/2) and if every letter is in pocket
	{
		////
		correct = true;

		if (direction == RIGHT)
		{
			for (int i = 0; i < size; i++)
			{
				if (new_word[i].inpocket == false)
					if (blank_check(pocket))
					{
						new_word[i].inpocket = true;
					}
					else
					{
						correct = false;
					}
			}

			for (int i = 0; i < size; i++)
			{
				if (x == (BOARD_SIZE / 2) && (y + i) == (BOARD_SIZE / 2) && correct == true)
				{
					for (int k = 0; k < size; k++)
					{
						new_word[k].wellplaced = true;
						new_word[k].newonboard = true;
					}
					delete[] copy_word;
					return true;
				}
			}
			for (int i = 0; i < size; i++)
			{
				new_word[i].newonboard = true;
			}
		}
		//
		else if (direction == DOWN)
		{
			for (int i = 0; i < size; i++)
			{
				if (new_word[i].inpocket == false)
					if (blank_check(pocket))
					{
						new_word[i].inpocket = true;
					}
					else
					{
						correct = false;
					}
			}

			for (int i = 0; i < size; i++)
			{
				if ((x + i) == (BOARD_SIZE / 2) && y == (BOARD_SIZE / 2) && correct == true)
				{
					for (int k = 0; k < size; k++)
					{
						new_word[k].wellplaced = true;
						new_word[k].newonboard = true;
					}
					delete[] copy_word;
					return true;
				}
			}
			for (int i = 0; i < size; i++)
			{
				new_word[i].newonboard = true;
			}
		}
	}

	////

	else if (direction == RIGHT)									//if placed words is greater than 0, check if word is placable in given position by checking every letter
	{
		for (int k = 0; k < size; k++)
		{
			if (new_word[k].value == status.board[x][y + k])		//if letter is same as letter on board, set its newonboard to false
			{
				sum += 2;
				new_word[k].newonboard = false;
				new_word[k].wellplaced = true;

				for (int i = 0; i < size; i++)						//if there is any letter in pocket same as current letter, and its inpocket is false, set it to true, and current letter's inpocket to false 
				{
					if (new_word[k].value == new_word[i].value && new_word[k].inpocket == true && i != k)
					{
						if (new_word[i].inpocket == false)
						{
							sum += 1;
							new_word[i].wellplaced = true;
							new_word[i].inpocket = true;
							new_word[k].inpocket = false;
							break;
						}
					}
				}
			}
			else if (status.board[x][y + k] == ' ' && new_word[k].inpocket)		//if there is free space on the board and our letter is in pocket, set its's parameters to true
			{
				sum += 1;
				new_word[k].wellplaced = true;
				new_word[k].newonboard = true;
			}
			else if (status.board[x][y + k] == ' ' && new_word[k].inpocket == false)		//if there is free space but our letter is not in pocket, check if there are any blanks in pocket, that could become missing letter
			{
				if (blank_check(pocket))
				{
					new_word[k].inpocket = true;
					sum += 1;
					new_word[k].wellplaced = true;
					new_word[k].newonboard = true;
				}
				else
				{
					sum = 0;
					new_word[k].inpocket = false;
					new_word[k].wellplaced = false;
					new_word[k].newonboard = true;
				}
			}
			else
			{
				new_word[k].wellplaced = false;
			}
		}
	}
	//
	else if (direction == DOWN)
	{
		for (int k = 0; k < size; k++)
		{
			if (new_word[k].value == status.board[x + k][y])			//if letter is same as letter on board, set its newonboard to false
			{
				sum += 2;
				new_word[k].newonboard = false;
				new_word[k].wellplaced = true;

				for (int i = 0; i < size; i++)							//if there is any letter in pocket same as current letter, and its inpocket is false, set it to true, and current letter's inpocket to false
				{
					if (new_word[k].value == new_word[i].value && new_word[k].inpocket == true && i != k)
					{
						if (new_word[i].inpocket == false)
						{
							sum += 1;
							new_word[i].wellplaced = true;
							new_word[i].inpocket = true;
							new_word[k].inpocket = false;
							break;
						}
					}
				}
			}
			else if (status.board[x + k][y] == ' ' && new_word[k].inpocket)		//if there is free space on the board and our letter is in pocket, set its's parameters to true
			{
				sum += 1;
				new_word[k].wellplaced = true;
				new_word[k].newonboard = true;
			}
			else if (status.board[x + k][y] == ' ' && new_word[k].inpocket == false)		//if there is free space but our letter is not in pocket, check if there are any blanks in pocket, that could become missing letter
			{
				if (blank_check(pocket))
				{
					new_word[k].inpocket = true;
					sum += 1;
					new_word[k].wellplaced = true;
					new_word[k].newonboard = true;
				}
				else
				{
					sum = 0;
					new_word[k].inpocket = false;
					new_word[k].wellplaced = false;
					new_word[k].newonboard = true;
				}
			}
			else
			{
				new_word[k].wellplaced = false;
			}
		}
	}
	////
	blank_reset(pocket);

	for (int i = 0; i < size; i++)
	{
		if (new_word[i].wellplaced == false)
		{
			wellplaced = false;
		}
		if (new_word[i].newonboard == false)
		{
			newonboard = false;
		}
	}


	if (sum == size && newonboard == true)
	{
		for (int i = 0; i < size; i++)
		{
			new_word[i].wellplaced = false;
		}
	}

	if (sum > size && sum != size * 2 && wellplaced == true)
	{
		delete[] copy_word;
		return true;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			new_word[i].inpocket = copy_word[i].inpocket;
		}
		delete[] copy_word;
		return false;
	}
}

bool blank_check(struct pocket_letter pocket[]) {		//check if there is a blank in the pocket; if there is, change it to '$' not to mess up later searches
	for (int i = 0; i < POCKET_SIZE; i++)
	{
		if (pocket[i].value == '@')
		{
			pocket[i].value = '$';
			return true;
		}
	}
	return false;
}

void blank_reset(struct pocket_letter pocket[]) {		//reset blanks back tp '@'
	for (int i = 0; i < POCKET_SIZE; i++)
	{
		if (pocket[i].value == '$')
		{
			pocket[i].value = '@';
		}
	}
}

void word_target(struct field_letter new_word[], struct pocket_letter pocket[], int size, struct game_status &status)
{
	bool allowed;
	char input;
	int coursor_x, coursor_y;
	int x, y;
	int direction = RIGHT;

	coursor_x = BOARD_POS_RIGHT + 3;				//set coursor to A 01
	coursor_y = BOARD_POS_TOP + 1;

	output_draw(status, MSG_WORD_SETPOS);			//tell user to choose word position

	do {

		y = coursor_y - BOARD_POS_TOP - 1;			//translate coursor on-screen coordinates to cordinates on the board
		x = (coursor_x - BOARD_POS_RIGHT - 3) / 2;

		_setcursortype(_NOCURSOR);					//hide coursor when drawing, not to create irritating screen glitches
		screen_draw(pocket, status);

		if (status.learn_mode == true)				//if learnmode is ON, display estimated amount of the points granted by current position
		{
			points_display(status, new_word, size, y, x, direction);
		}

		coursor_pos(coursor_x, coursor_y);			//update coursor pos in legend
		gotoxy(coursor_x, coursor_y);				//move coursor on the board

		for (int i = 0; i < size; i++)				//reset all new_word display colors
		{
			new_word[i].wellplaced = false;
			new_word[i].newonboard = false;
		}

		allowed = word_check_position(new_word, pocket, size, status, y, x, direction);		//check if there is a possibility to place word in given position

		if (direction == RIGHT) {					//draw word on the board with right colors
			for (int i = 0; i < size; i++)
			{
				if (new_word[i].wellplaced == true)
				{
					textbackground(GREEN);
				}
				else
				{
					textbackground(RED);
				}

				putch(new_word[i].value);
				gotoxy(wherex() + 1, wherey());
				textbackground(BLACK);
			}
		}
		else if (direction == DOWN) {
			for (int i = 0; i < size; i++)
			{
				if (new_word[i].wellplaced == true)
				{
					textbackground(GREEN);
				}
				else
				{
					textbackground(RED);
				}

				putch(new_word[i].value);
				gotoxy(wherex() - 1, wherey() + 1);
				textbackground(BLACK);
			}
		}

		gotoxy(coursor_x, coursor_y);			//place coursor again at its position after drawing word on the board

		input = getch();						//get key from user

		if (input == 0)
		{
			coursor_move(coursor_x, coursor_y, input);
		}
		else if (input == 'o')					//if 'o' was pressed, rotate the word
		{
			if (direction == DOWN)
			{
				direction = RIGHT;
			}
			else
			{
				direction = DOWN;
			}
		}

		do {									//if part of word is placed out of board, place it back in
			if (coursor_x + size * 2 - 1 > (BOARD_POS_RIGHT + BOARD_SIZE * 2 + 2) && direction == RIGHT)
			{
				coursor_x -= 2;
			}
			if (coursor_y + size - 1 > (BOARD_POS_TOP + BOARD_SIZE) && direction == DOWN)
			{
				coursor_y--;
			}
		} while ((coursor_x + size * 2 - 1 > (BOARD_POS_RIGHT + BOARD_SIZE * 2 + 2) && direction == RIGHT) || (coursor_y + size - 1 > (BOARD_POS_TOP + BOARD_SIZE) && direction == DOWN));

	} while (input != 0x0d && input != 0x1b);	//if enter or esc was pressed, finish placing a word


	if (input == 0x1b)							//if esc was pressed, refresh the screen and go back to inputing the word from keyboard
	{
		screen_draw(pocket, status);
		word_create(pocket, status);
	}
	else if (input == 0x0d && allowed == true)					//if enter was pressed and word position correct, check if every word on the board will be in the dictionary
	{
		allowed = board_dictionary_check(status, new_word, x, y, size, direction);

		if (allowed == true || status.placed_words == 0)		//if everything is ok, place the word, add points and show msg
		{
			word_place(new_word, pocket, size, status, y, x, direction);
			status.points += points_count(new_word, size, y, x, status, direction);
			output_draw(status, MSG_PLACED);
		}
		else
		{
			output_draw(status, MSG_WORD_MISSING);
		}
	}
	else
	{
		output_draw(status, MSG_NOTPOSSIBLE);
	}
}

bool board_dictionary_check(struct game_status &status, struct field_letter new_word[], int x, int y, int size, int direction) {
	int word_index;
	int word_size;
	char ch;
	char word[BOARD_SIZE];
	char* word_to_check;

	//check if every word, that appears vertically or horizontaly, is in dicitonary. If not, return false

	//RIGHT
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		word_size = 0;
		word_index = 0;

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			ch = letter_dictionary_check(status, new_word, x, y, size - 1, direction, j, i);	//check which character will be placed in the given position after the word will be placed

			if (ch != ' ')
			{
				word[word_index] = ch;
				word_size++;
				word_index++;
			}
			else if (ch == ' ' && word_size > 0)
			{
				if (word_size > 1)
				{
					word_to_check = new char[word_size + 1];

					for (int k = 0; k < word_size; k++)
					{
						word_to_check[k] = word[k];
					}

					word_to_check[word_size] = NULL;

					if (list_word_search(status.list, word_to_check, word_size) == false)
					{
						return false;
					}
					delete[]word_to_check;
				}

				word_size = 0;
				word_index = 0;
			}
		}

	}
	//DOWN
	for (int j = 0; j < BOARD_SIZE; j++)
	{
		word_size = 0;
		word_index = 0;

		for (int i = 0; i < BOARD_SIZE; i++)
		{


			ch = letter_dictionary_check(status, new_word, x, y, size - 1, direction, j, i);	//check which character will be placed in the given position after the word will be placed

			if (ch != ' ')
			{
				word[word_index] = ch;
				word_size++;
				word_index++;
			}
			else if (ch == ' ' && word_size > 0)
			{
				if (word_size > 1)
				{
					word_to_check = new char[word_size + 1];

					for (int k = 0; k < word_size; k++)
					{
						word_to_check[k] = word[k];
					}

					word_to_check[word_size] = NULL;

					if (list_word_search(status.list, word_to_check, word_size) == false)
					{
						return false;
					}

					delete[]word_to_check;
				}

				word_size = 0;
				word_index = 0;
			}
		}
	}

	return true;
}

char letter_dictionary_check(struct game_status &status, struct field_letter new_word[], int x, int y, int size, int direction, int j, int i)
{
	//check which character will be placed in the given position after the word will be placed

	char ch;

	if (direction == RIGHT)
	{
		if (j >= x && j <= x + size && i == y)
		{
			ch = new_word[j - x].value;
		}
		else
		{
			ch = status.board[i][j];
		}
	}
	else if (direction == DOWN)
	{
		if (i >= y && i <= y + size && j == x)
		{
			ch = new_word[i - y].value;
		}
		else
		{
			ch = status.board[i][j];
		}
	}

	return ch;
}

void word_place(struct field_letter new_word[], struct pocket_letter pocket[], int size, struct game_status &status, int x, int y, int direction) {		//finish placing the word to board by swapping letters
	bool swaped;

	for (int i = 0; i < size; i++)						//find all letters from new_word in pocket, and then replace it with board letters
	{
		swaped = false;

		for (int j = 0; j < POCKET_SIZE; j++)
		{
			if (new_word[i].value == pocket[j].value)
			{
				if (direction == DOWN)
				{
					swap_board(j, x + i, y, pocket, status);
				}
				if (direction == RIGHT)
				{
					swap_board(j, x, y + i, pocket, status);
				}
				swaped = true;
				break;
			}
		}
		if (swaped == false && new_word[i].newonboard == true)		//if letter wasn't swaped already, it means that it have to be blank used; find blank and set it to expected letter
		{
			for (int j = 0; j < POCKET_SIZE; j++)
			{
				if (pocket[j].value == '@')
				{
					pocket[j].value = new_word[i].value;
					if (direction == DOWN)
					{
						swap_board(j, x + i, y, pocket, status);
					}
					if (direction == RIGHT)
					{
						swap_board(j, x, y + i, pocket, status);
					}
					break;
				}
			}
		}
	}

	status.placed_words++;
}

//

int points_count(struct field_letter new_word[], int size, int x, int y, struct game_status &status, int direction) {
	int points = 0;
	int tmp_points;

	for (int i = 0; i < size; i++)											//check how many points it is for each letter, then add bonuses if there are any
	{
		if (new_word[i].newonboard)
		{
			tmp_points = points_for_letter(new_word[i].value);
			points += tmp_points;
			if (direction == DOWN)
			{
				if (status.bonuses[x + i][y] == '2')
				{
					points += tmp_points * (MULTIPLIER_CHAR_LIGHTCYAN - 1);
					status.bonuses[x + i][y] = ' ';
				}
				if (status.bonuses[x + i][y] == '3')
				{
					points += tmp_points * (MULTIPLIER_CHAR_BLUE - 1);
					status.bonuses[x + i][y] = ' ';
				}
			}
			if (direction == RIGHT)
			{
				if (status.bonuses[x][y + i] == '2')
				{
					points += tmp_points * (MULTIPLIER_CHAR_LIGHTCYAN - 1);
					status.bonuses[x][y + i] = ' ';
				}
				if (status.bonuses[x][y + i] == '3')
				{
					points += tmp_points * (MULTIPLIER_CHAR_BLUE - 1);
					status.bonuses[x][y + i] = ' ';
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (direction == DOWN)
		{
			if (status.bonuses[x + i][y] == '5')
			{
				points = points * MULTIPLIER_WORD_MAGENTA;
				status.bonuses[x + i][y] = ' ';
			}
			else if (status.bonuses[x][y + i] == '4')
			{
				points = points * MULTIPLIER_WORD_RED;
				status.bonuses[x + i][y] = ' ';
			}
		}
		else if (direction == RIGHT)
		{
			if (status.bonuses[x][y + i] == '5')
			{
				points = points * MULTIPLIER_WORD_MAGENTA;
				status.bonuses[x][y + i] = ' ';
			}
			else if (status.bonuses[x][y + i] == '4')
			{
				points = points * MULTIPLIER_WORD_RED;
				status.bonuses[x][y + i] = ' ';
			}
		}
	}

	if (size == POCKET_SIZE)								//if every letter from pocket was used, add aditional 50 points
	{
		points += 50;
	}

	return points;
}

int points_for_letter(char ch) {
	int points = 0;
	v_letters letter;

	switch (ch) {				//return points acquired for given letter
	case 'a':
		letter = a_v;
		break;
	case 'b':
		letter = b_v;
		break;
	case 'c':
		letter = c_v;
		break;
	case 'd':
		letter = d_v;
		break;
	case 'e':
		letter = e_v;
		break;
	case 'f':
		letter = f_v;
		break;
	case 'g':
		letter = g_v;
		break;
	case 'h':
		letter = h_v;
		break;
	case 'i':
		letter = i_v;
		break;
	case 'j':
		letter = j_v;
		break;
	case 'k':
		letter = k_v;
		break;
	case 'l':
		letter = l_v;
		break;
	case 'm':
		letter = m_v;
		break;
	case 'n':
		letter = n_v;
		break;
	case 'o':
		letter = o_v;
		break;
	case 'p':
		letter = p_v;
		break;
	case 'q':
		letter = q_v;
		break;
	case 'r':
		letter = r_v;
		break;
	case 's':
		letter = s_v;
		break;
	case 't':
		letter = t_v;
		break;
	case 'u':
		letter = u_v;
		break;
	case 'v':
		letter = v_v;
		break;
	case 'w':
		letter = w_v;
		break;
	case 'x':
		letter = x_v;
		break;
	case 'y':
		letter = y_v;
		break;
	case 'z':
		letter = z_v;
		break;
	}
	points += (int)letter;
	return points;
}

void points_display(struct game_status &status, struct field_letter new_word[], int size, int x, int y, int direction) {
	gotoxy(MENU_POS_RIGHT, POSITION_INPUT_TOP - 1);
	cputs("                                                      ");
	gotoxy(MENU_POS_RIGHT, POSITION_INPUT_TOP - 1);

	if (size == POCKET_SIZE)
	{
		cputs("50+");
	}

	putch('(');

	for (int i = 0; i < size; i++)								//display amount of points that would be given for every letter(with bonuses included)
	{

		if (i > 0)
		{
			putch('+');
		}

		int_to_char(points_for_letter(new_word[i].value));

		putch('(');
		putch(new_word[i].value);
		putch(')');

		if (direction == DOWN)
		{
			if (status.bonuses[x + i][y] == '2')
			{
				putch('*');
				int_to_char(MULTIPLIER_CHAR_LIGHTCYAN);
			}
			if (status.bonuses[x + i][y] == '3')
			{
				putch('*');
				int_to_char(MULTIPLIER_CHAR_BLUE);
			}
		}
		if (direction == RIGHT)
		{

			if (status.bonuses[x][y + i] == '2')
			{
				putch('*');
				int_to_char(MULTIPLIER_CHAR_LIGHTCYAN);
			}
			if (status.bonuses[x][y + i] == '3')
			{
				putch('*');
				int_to_char(MULTIPLIER_CHAR_BLUE);
			}
		}
	}

	putch(')');

	for (int i = 0; i < size; i++)
	{
		if (direction == DOWN)
		{
			if (status.bonuses[x + i][y] == '5')
			{
				putch('*');
				int_to_char(MULTIPLIER_WORD_MAGENTA);
			}
			else if (status.bonuses[x + i][y] == '4')
			{
				putch('*');
				int_to_char(MULTIPLIER_WORD_RED);
			}
		}
		else if (direction == RIGHT)
		{
			if (status.bonuses[x][y + i] == '5')
			{
				putch('*');
				int_to_char(MULTIPLIER_WORD_MAGENTA);
			}
			else if (status.bonuses[x][y + i] == '4')
			{
				putch('*');
				int_to_char(MULTIPLIER_WORD_RED);
			}
		}
	}

	putch(')');
}
//

char* file_input(int &size) {
	char input;
	size = 0;
	char* new_file1 = new char[size];
	char* new_file2 = new char[size];

	_setcursortype(_SOLIDCURSOR);
	do {
		gotoxy(MENU_POS_RIGHT, POSITION_INPUT_TOP);
		cputs("Nazwa pliku:  ");
		gotoxy(MENU_POS_RIGHT + 14 + size, POSITION_INPUT_TOP);

		input = getch();										//if letter was pressed

		if (input >= '0' && input <= 'z' && size % 2 == 0)		//create array of exact same size as an word size
		{
			delete[] new_file2;
			new_file2 = new char[(size + 1)];					//crate array one char larger

			for (int i = 0; i < size; i++)
			{
				new_file2[i] = new_file1[i];					//copy all values form last array
			}

			new_file2[size] = input;							//copy new letter to last pos of the array
			size++;
		}
		else if (input >= '0' && input <= 'z' && size % 2 == 1)
		{
			delete[] new_file1;
			new_file1 = new char[(size + 1)];					//crate array one char larger

			for (int i = 0; i < size; i++)
			{
				new_file1[i] = new_file2[i];					//copy all values form last array
			}

			new_file1[size] = input;
			size++;
		}
		//if backspace was pressed
		else if (input == 0x08 && size % 2 == 0)
		{
			if (size != 0)										//if word's length is currently 0, do not use backspace cause it is nothing to remove
			{
				delete[] new_file2;
				new_file2 = new char[(size - 1)];

				for (int i = 0; i < size - 1; i++)
				{
					new_file2[i] = new_file1[i];				//copy all values form last array
				}

				size--;
			}
		}
		else if (input == 0x08 && size % 2 == 1)
		{
			delete[] new_file1;
			new_file1 = new char[(size - 1)];

			for (int i = 0; i < size - 1; i++) {
				new_file1[i] = new_file2[i];					//copy all values form last array
			}

			size--;
		}
		//draw current state of the word
		_setcursortype(_NOCURSOR);

		if (input != 0x1b) {										//if esc wasnt prssed
			gotoxy(MENU_POS_RIGHT + 14, POSITION_INPUT_TOP);		//erase last state of the word

			for (int i = 0; i < size + 2; i++)
			{
				putch(' ');
			}

			gotoxy(MENU_POS_RIGHT + 14, POSITION_INPUT_TOP);

			if (size % 2 == 0 && size > 0)
				for (int i = 0; i < size; i++)
				{
					putch(new_file1[i]);
				}
			else if (size % 2 == 1 && size > 0)
				for (int i = 0; i < size; i++)
				{
					putch(new_file2[i]);

				}

			_setcursortype(_SOLIDCURSOR);
		}
	} while (input != 0x0d && input != 0x1b);

	if (size % 2 == 0) {
		if (input == 0x0d)			//if enter was pressed, return file name
		{
			return new_file1;
		}
		else if (input == 0x1b)
		{
			return NULL;			//if ecs was pressed, return NULL
		}
	}
	if (size % 2 == 1) {
		if (input == 0x0d)
		{
			return new_file2;		//if enter was pressed, return file name
		}
		else if (input == 0x1b)
		{
			return NULL;			//if ecs was pressed, return NULL
		}
	}

	return NULL;
}

void game_save(struct game_status &status, struct pocket_letter pocket[]) {
	int size;
	char* p = file_input(size);
	FILE* new_file;

	if (p != NULL)
	{
		char* filename = new char[size + 1];

		for (int i = 0; i < size; i++)
		{
			filename[i] = p[i];
		}

		filename[size] = NULL;
		new_file = fopen(filename, "w");

		delete[]filename;

		if (new_file != NULL)
		{
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (status.board[i][j] == ' ')
					{
						fprintf(new_file, "_ ");
					}
					else
					{
						fprintf(new_file, "%c ", status.board[i][j]);
					}
				}
				fprintf(new_file, "\n");
			}
			//
			fprintf(new_file, "\n");
			//
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (status.bonuses[i][j] == ' ')
					{
						fprintf(new_file, "_ ");
					}
					else
					{
						fprintf(new_file, "%c ", status.bonuses[i][j]);
					}
				}
				fprintf(new_file, "\n");
			}
			//
			fprintf(new_file, "\n");
			//
			for (int i = 0; i < LETTERS_NUMBER; i++)
			{
				if (i % 10 == 0)
				{
					fprintf(new_file, "\n");
				}
				if (status.letters_bag[i] == ' ')
				{
					fprintf(new_file, "_ ");
				}
				else
				{
					fprintf(new_file, "%c ", status.letters_bag[i]);
				}
			}
			//
			fprintf(new_file, "\n\n");
			//
			for (int i = 0; i < POCKET_SIZE; i++)
			{
				if (pocket[i].value == ' ')
				{
					fprintf(new_file, "_ ");
				}
				else
				{
					fprintf(new_file, "%c ", pocket[i].value);
				}
			}
			//
			fprintf(new_file, "\n\n");
			//
			fprintf(new_file, "%d.", status.points);
			fprintf(new_file, "%d.", status.turn);
			fprintf(new_file, "%d.", status.pocket_replacer);
			fprintf(new_file, "%d", status.placed_words);

			output_draw(status, MSG_SAVED);
		}
		else
		{
			output_draw(status, MSG_SAVED_ERROR);
		}
		fclose(new_file);
	}
}

void game_load(struct game_status &status, struct pocket_letter pocket[]) {
	int size;
	char* p = file_input(size);
	char read = ' ';
	FILE* new_file;

	if (p != NULL)
	{
		char* filename = new char[size + 1];

		for (int i = 0; i < size; i++)
		{
			filename[i] = p[i];
		}

		filename[size] = NULL;

		new_file = fopen(filename, "r");

		delete[]filename;

		if (new_file != NULL)
		{
			rewind(new_file);

			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					fscanf(new_file, "%c ", &read);

					if (read == '_')
					{
						status.board[i][j] = ' ';
					}
					else
					{
						status.board[i][j] = read;
					}
				}
			}
			//
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					fscanf(new_file, "%c ", &read);

					if (read == '_')
					{
						status.bonuses[i][j] = ' ';
					}
					else
					{
						status.bonuses[i][j] = read;
					}
				}
			}
			//
			for (int i = 0; i < LETTERS_NUMBER; i++)
			{
				fscanf(new_file, "%c ", &read);

				if (read == '_')
				{
					status.letters_bag[i] = ' ';
				}
				else
				{
					status.letters_bag[i] = read;
				}
			}
			//
			for (int i = 0; i < POCKET_SIZE; i++)
			{
				fscanf(new_file, "%c ", &read);

				if (read == '_')
				{
					pocket[i].value = ' ';
				}
				else
				{
					pocket[i].value = read;
				}
			}
			//
			fscanf(new_file, "%d.%d.%d.%d", &status.points, &status.turn, &status.pocket_replacer, &status.placed_words);
			//
			fclose(new_file);
			output_draw(status, MSG_LOADED);
		}
		else
		{
			output_draw(status, MSG_LOADED_ERROR);
		}
	}
}

//

list* load_dictionary(char filename[]) {
	list* head = new list;
	head->next = NULL;

	list* p = head;
	list* t;
	FILE* new_file;
	char ch;
	int size = 0;
	char* new_word1;
	char* new_word2;

	new_file = fopen(filename, "r");

	if (new_file != NULL)
	{
		do {
			size = 0;
			new_word1 = new char[size];
			new_word2 = new char[size];

			do {

				ch = fgetc(new_file);

				if (size % 2 == 0)
				{
					if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
					{
						delete[] new_word1;
						new_word1 = new char[size + 1];

						for (int i = 0; i < size; i++)
						{
							new_word1[i] = new_word2[i];
						}

						ch = upper_to_lower(ch);
						new_word1[size] = ch;
						size++;
					}
				}
				else if (size % 2 == 1)
				{
					if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
					{
						delete[] new_word2;
						new_word2 = new char[size + 1];

						for (int i = 0; i < size; i++)
						{
							new_word2[i] = new_word1[i];
						}

						ch = upper_to_lower(ch);
						new_word2[size] = ch;
						size++;
					}
				}
			} while (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');

			if (size > 0)
			{
				char* new_word = new char[size + 1];

				if (size % 2 == 0)
				{
					for (int i = 0; i < size; i++)
					{
						new_word[i] = new_word2[i];
					}
				}
				else if (size % 2 == 1)
				{
					for (int i = 0; i < size; i++)
					{
						new_word[i] = new_word1[i];
					}
				}

				new_word[size] = NULL;
				size++;

				if (list_word_search(head, new_word, size) != true && (size - 1) <= BOARD_SIZE)
				{
					t = list_lenght_search(head, size);

					if (t != NULL)
					{
						p = list_sorted_add(new_word, size, t);
						if (p == NULL)
						{
							cputs(MEMORY_ERROR);
							fclose(new_file);
							return NULL;
						}
					}
					else
					{
						p->next = list_add(new_word, size);
						if (p == NULL)
						{
							cputs(MEMORY_ERROR);
							fclose(new_file);
							return NULL;
						}
					}
				}

				delete[] new_word;
			}

			delete[] new_word1;
			delete[] new_word2;

		} while (ch != EOF);
		fclose(new_file);
	}

	return head;
}

list* list_add(char tab[], int size) {
	list *word = new list;
	if (word == NULL)
	{
		return word;
	}
	word->word = new char[size];
	word->lenght = size;

	word->next = NULL;
	strcpy(word->word, tab);

	return word;
}

list* list_sorted_add(char tab[], int size, list* p) {
	list *word = new list;
	if (word == NULL)
	{
		return word;
	}
	list *tmp = p->next;

	word->word = new char[size];
	strcpy(word->word, tab);
	word->lenght = size;

	p->next = word;
	word->next = tmp;

	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	return tmp;
}

list* list_lenght_search(list* head, int size) {
	list* p = head;
	list* previous;

	while (p->next != NULL)
	{
		previous = p;
		p = p->next;

		if (size < p->lenght)
		{
			return previous;
		}
	}
	return NULL;
}

bool list_word_search(list* head, char word[], int size)
{
	list* p = head;
	int compare;

	while (p->next != NULL)
	{
		p = p->next;

		if (p->lenght - 1 > size)
		{
			break;
		}

		compare = strcmp(word, p->word);

		if (compare == 0)
		{
			return true;
		}
	}
	return false;
}

//

void swap(int a, int b, char tab[]) {							//replace two values in given array
	char x = tab[a];
	tab[a] = tab[b];
	tab[b] = x;
}

void swap_pocket(int a, int b, struct pocket_letter pocket[], char tab2[]) {			//replace two values in two given arrays
	char x = pocket[a].value;
	pocket[a].value = tab2[b];
	tab2[b] = x;
}

void swap_board(int a, int bx, int by, struct pocket_letter pocket[], struct game_status &status) {
	char x = pocket[a].value;
	pocket[a].value = status.board[bx][by];
	status.board[bx][by] = x;
}

void reset_values(struct pocket_letter pocket[], struct game_status &status, int &coursor_x, int &coursor_y) {
	coursor_x = BOARD_POS_RIGHT + 3;			//place coursor in 01 A
	coursor_y = BOARD_POS_TOP + 1;

	//starting values//
	for (int i = 0; i < POCKET_SIZE; i++)		//prepare pocket
	{
		pocket[i].value = ' ';
		pocket[i].selected = false;
	}

	////

	status.points = 0;							//reset points, turns, and placed words counters
	status.turn = 0;
	status.placed_words = 0;
	status.pocket_replacer = 0;
	status.learn_mode = false;

	////

	for (int i = 0; i < BOARD_SIZE; i++)		//clear board
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			status.board[i][j] = ' ';
			status.bonuses[i][j] = ' ';
		}
	}

	////

	for (int i = 0; i < BOARD_SIZE; i++) {								//place all special fields
		status.bonuses[i][i] = '5';										//lightmagenta word x MULTIPLIER
		status.bonuses[BOARD_SIZE - i - 1][i] = '5';
	}

	status.bonuses[BOARD_SIZE / 2][BOARD_SIZE / 2] = '#';				//middle marked as yellow

	status.bonuses[BOARD_SIZE / 2 - 2][BOARD_SIZE / 2 - 2] = '3';		//Blue char x MULTIPLIER
	status.bonuses[BOARD_SIZE / 2 - 2][BOARD_SIZE / 2 + 2] = '3';
	status.bonuses[BOARD_SIZE / 2 + 2][BOARD_SIZE / 2 - 2] = '3';
	status.bonuses[BOARD_SIZE / 2 + 2][BOARD_SIZE / 2 + 2] = '3';

	status.bonuses[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = '2';		//lightcyan char x MULTIPLIER
	status.bonuses[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 + 1] = '2';
	status.bonuses[BOARD_SIZE / 2 + 1][BOARD_SIZE / 2 - 1] = '2';
	status.bonuses[BOARD_SIZE / 2 + 1][BOARD_SIZE / 2 + 1] = '2';

	status.bonuses[3][0] = '2';
	status.bonuses[0][3] = '2';

	status.bonuses[BOARD_SIZE - 1][3] = '2';
	status.bonuses[3][BOARD_SIZE - 1] = '2';

	status.bonuses[BOARD_SIZE - 3 - 1][0] = '2';
	status.bonuses[0][BOARD_SIZE - 3 - 1] = '2';

	status.bonuses[BOARD_SIZE - 1][BOARD_SIZE - 3 - 1] = '2';
	status.bonuses[BOARD_SIZE - 3 - 1][BOARD_SIZE - 1] = '2';

	status.bonuses[1][BOARD_SIZE / 2 - 2] = '3';
	status.bonuses[2][BOARD_SIZE / 2 - 1] = '2';
	status.bonuses[3][BOARD_SIZE / 2] = '2';
	status.bonuses[2][BOARD_SIZE / 2 + 1] = '2';
	status.bonuses[1][BOARD_SIZE / 2 + 2] = '3';

	status.bonuses[BOARD_SIZE - 2][BOARD_SIZE / 2 - 2] = '3';
	status.bonuses[BOARD_SIZE - 3][BOARD_SIZE / 2 - 1] = '2';
	status.bonuses[BOARD_SIZE - 4][BOARD_SIZE / 2] = '2';
	status.bonuses[BOARD_SIZE - 3][BOARD_SIZE / 2 + 1] = '2';
	status.bonuses[BOARD_SIZE - 2][BOARD_SIZE / 2 + 2] = '3';

	status.bonuses[BOARD_SIZE / 2 - 2][1] = '3';
	status.bonuses[BOARD_SIZE / 2 - 1][2] = '2';
	status.bonuses[BOARD_SIZE / 2][3] = '2';
	status.bonuses[BOARD_SIZE / 2 + 1][2] = '2';
	status.bonuses[BOARD_SIZE / 2 + 2][1] = '3';

	status.bonuses[BOARD_SIZE / 2 - 2][BOARD_SIZE - 2] = '3';
	status.bonuses[BOARD_SIZE / 2 - 1][BOARD_SIZE - 3] = '2';
	status.bonuses[BOARD_SIZE / 2][BOARD_SIZE - 4] = '2';
	status.bonuses[BOARD_SIZE / 2 + 1][BOARD_SIZE - 3] = '2';
	status.bonuses[BOARD_SIZE / 2 + 2][BOARD_SIZE - 2] = '3';

	status.bonuses[0][0] = '4';											//red word x MULTIPLIER
	status.bonuses[0][BOARD_SIZE - 1] = '4';
	status.bonuses[BOARD_SIZE - 1][0] = '4';
	status.bonuses[BOARD_SIZE - 1][BOARD_SIZE - 1] = '4';

	status.bonuses[0][BOARD_SIZE / 2] = '4';
	status.bonuses[BOARD_SIZE / 2][0] = '4';
	status.bonuses[BOARD_SIZE - 1][BOARD_SIZE / 2] = '4';
	status.bonuses[BOARD_SIZE / 2][BOARD_SIZE - 1] = '4';

	////

	for (int i = 0; i < LETTERS_NUMBER; i++)
	{
		status.letters_bag[i] = ' ';
	}

	n_letters liczba;														//fulfill letters bag with given amounts of letters
	liczba = e;

	int start = 0;
	////
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'e';
	start = start + (int)liczba;
	//
	liczba = a;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'a';
	start = start + (int)liczba;
	//
	liczba = i;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'i';
	start = start + (int)liczba;
	//
	liczba = o;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'o';
	start = start + (int)liczba;
	//
	liczba = n;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'n';
	start = start + (int)liczba;
	//
	liczba = r;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'r';
	start = start + (int)liczba;
	//
	liczba = t;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 't';
	start = start + (int)liczba;
	//
	liczba = l;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'l';
	start = start + (int)liczba;
	//
	liczba = s;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 's';
	start = start + (int)liczba;
	//
	liczba = u;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'u';
	start = start + (int)liczba;
	//
	liczba = d;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'd';
	start = start + (int)liczba;
	//
	liczba = g;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'g';
	start = start + (int)liczba;
	//
	liczba = b;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'b';
	start = start + (int)liczba;
	//
	liczba = c;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'c';
	start = start + (int)liczba;
	//
	liczba = m;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'm';
	start = start + (int)liczba;
	//
	liczba = p;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'p';
	start = start + (int)liczba;
	//
	liczba = f;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'f';
	start = start + (int)liczba;
	//
	liczba = h;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'h';
	start = start + (int)liczba;
	//
	liczba = v;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'v';
	start = start + (int)liczba;
	//
	liczba = w;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'w';
	start = start + (int)liczba;
	//
	liczba = y;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'y';
	start = start + (int)liczba;
	//
	liczba = k;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'k';
	start = start + (int)liczba;
	//
	liczba = j;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'j';
	start = start + (int)liczba;
	//
	liczba = x;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'x';
	start = start + (int)liczba;
	//
	liczba = q;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'q';
	start = start + (int)liczba;
	//
	liczba = z;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = 'z';
	start = start + (int)liczba;
	//
	liczba = blank;
	for (int i = 0; i < liczba; i++) status.letters_bag[start + i] = '@';
	start = start + (int)liczba;
	////

	bag_shuffle(status);										//shuffle all letters in bag
	////

	output_draw(status, MSG_HELLO);
}

void int_to_char(int number) {
	char tmp[3];

	for (int i = 0; i < 3; i++)
	{
		tmp[i] = '0';
	}

	do {

		if (number >= 100)
		{
			number -= 100;
			tmp[0]++;
		}
		else if (number >= 10)
		{
			number -= 10;
			tmp[1]++;
		}
		else if (number > 0)
		{
			number -= 1;
			tmp[2]++;
		}

	} while (number > 0);

	if (tmp[0] != '0')
	{
		putch(tmp[0]);
	}

	putch(tmp[1]);
	putch(tmp[2]);
}

char upper_to_lower(char letter) {					//if passed char is capital letter, change it to lower case letter and return
	if (letter >= 'A' && letter <= 'Z')
	{
		letter = letter + 32;
	}
	return letter;
}

char* file_path(char *argv, char * filename) {
	int filename_lenght = 0;
	int last_slash_pos = 0;
	int indeks = 0;

	if (*filename >= 'A' && *filename <= 'Z')
	{
		if (filename[1] == ':')
		{
			return filename;
		}
	}
	else
	{
		do {
			if (argv[indeks] == '\\')
			{
				last_slash_pos = indeks + 1;
			}
			indeks++;
		} while (argv[indeks] != NULL);

		indeks = 0;

		for (; filename[indeks] != NULL; indeks++)
		{
			filename_lenght++;
		}
		filename_lenght++;
		for (int i = 0; i < filename_lenght; i++)
		{
			argv[last_slash_pos + i] = filename[i];
		}

		return argv;
	}
}