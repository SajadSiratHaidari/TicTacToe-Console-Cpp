#include <iostream>
#include <cctype>
#include <cstdlib>
#include <conio.h>
#include "TicTacToe.h"

/*
	This game is programmed for console. You can play with your friend or your pc.
*/

#define ILLIGAL_ROW_COLUMN_INDEX 23

char displayInputAndReturnData(char who, char pChar, TicTacToe &t)
{
	std::cout << "Enter your move position (" << pChar << ").\nIn format (row column) like 2 2: ";
	int rowIndex, columnIndex;
	std::cin >> rowIndex >> columnIndex;
	if (rowIndex < 0 || rowIndex > 2 || columnIndex < 0 || columnIndex > 2)
		return ILLIGAL_ROW_COLUMN_INDEX;
	return t.set(rowIndex, columnIndex, who);
}

int ticTacToeWithPC();

int main()
{
	std::cout << "Do you want to play with computer? (Y/N): ";
	char yesNo;
	std::cin >> yesNo;
	yesNo = toupper(yesNo);
	if (yesNo == 'Y')
		return ticTacToeWithPC();
	else if (yesNo != 'N') {
		std::cout << "Wrong choice." << std::endl;
		getch();
		return 0;
	}
    std::cout << "As player one, do you want to choose 'O' or 'X'. (O, X)? ";
    char p1Char;
    std::cin >> p1Char;
    p1Char = toupper(p1Char);
    if (p1Char != 'O' && p1Char != 'X') {
		std::cout << "Illigal character used." << std::endl;
		return 0;
    }

    char p2Char = p1Char == 'X' ? 'O':'X';
    TicTacToe t;
    t.setPlayersCharacters(p1Char, p2Char);
    std::cout << "P1 = " << p1Char << "\nP2 = " << p2Char << "\n\n";

    while (true) {
		t.printBoard();
		while (true) {
			switch (displayInputAndReturnData(1, p1Char, t)) {
			case ILLIGAL_ROW_COLUMN_INDEX:
				std::cout << "Illigal cell location entered. Try again." << std::endl;
				continue;

			case 1:
				t.printBoard();
				std::cout << "Player 1 wins!" << std::endl;
				return 0;

			case TTT_DRAW:
				std::cout << "MATCH DRAW!" << std::endl;
				return 0;

			case TTT_NOT_EMPTY:
				std::cout << "Not empty cell." << std::endl;
				continue;
			}
			break;
		}
		t.printBoard();

		while (true) {
			switch (displayInputAndReturnData(2, p2Char, t)) {
			case ILLIGAL_ROW_COLUMN_INDEX:
				std::cout << "Illigal row-column index." << std::endl;
				continue;

			case 2:
				t.printBoard();
				std::cout << "Player 2 wins!" << std::endl;
				return 0;

			case TTT_DRAW:
				std::cout << "MATCH DRAW!" << std::endl;
				return 0;

			case TTT_NOT_EMPTY:
				std::cout << "Not empty place. Try again." << std::endl;
				continue;
			}
			break;
		}
    }
}

#define TTT_CLIENT 0
#define TTT_COMPUTER 1

int ticTacToeWithPC()
{
	std::cout << "Do you want to be player one? (Y/N): ";
	char choice;
	std::cin >> choice;
	choice = toupper(choice);
	char playerOne;
	if (choice == 'Y')
		playerOne = TTT_CLIENT;
	else
		playerOne = TTT_COMPUTER;

	char p1Char, p2Char;
	std::cout << "Choose your occupied cell icon. (X, O)? ";
	std::cin >> choice;
	choice = toupper(choice);
	if (choice != 'O' && choice != 'X') {
		std::cout << "Error: Invalid character." << std::endl;
		return 0;
	}

	if (playerOne == TTT_CLIENT) {
		p1Char = choice;
		p2Char = choice == 'X' ? 'O':'X';
	} else {
		p1Char = choice == 'X' ? 'O':'X';
		p2Char = choice;
	}

	TicTacToe t;
	t.setPlayersCharacters(p1Char, p2Char);
	t.printBoard();
	while (true) {
		unsigned char rowIndex, columnIndex;
		if (playerOne == TTT_CLIENT) {
			while (true) {
				std::cout << "Enter a location move (like \"1 2\" i.e. row 1 column 2) as (" << p1Char << "): ";
				std::cin >> rowIndex >> columnIndex;
				rowIndex -= '0';
				columnIndex -= '0';
				if (rowIndex < 0 || rowIndex > 2 || columnIndex < 0 || columnIndex > 2) {
					std::cout << "Illigal row-column index." << std::endl;
					continue;
				}

				char retval = t.set(rowIndex, columnIndex, 1);
				if (retval == TTT_NOT_EMPTY) {
					std::cout << "Not empty location. Try again.\n\n";
					continue;
				}
				t.printBoard();

				switch (retval) {
				case TTT_DRAW:
					std::cout << "MATCH DRAW!" << std::endl;
					return 0;

				case 1:
					std::cout << "YOU WON!!!" << std::endl;
					return 0;
				}
				break;
			}

			t.pc_getAMoveLocation(rowIndex, columnIndex, 2);
			std::cout << "COMPUTER MOVE: " << +rowIndex << ", " << +columnIndex << std::endl;
			char retval = t.set(rowIndex, columnIndex, 2);
			t.printBoard();
			switch (retval) {
			case TTT_DRAW:
				std::cout << "MATCH DRAW!" << std::endl;
				return 0;

			case 2:
				std::cout << "COMPUTER WON!!!" << std::endl;
				return 0;
			}
		} else {
			t.pc_getAMoveLocation(rowIndex, columnIndex, 1);
			std::cout << "COMPUTER MOVE: (" << +rowIndex << ',' << +columnIndex << ')' << std::endl;
			char retval = t.set(rowIndex, columnIndex, 1);
			t.printBoard();
			switch (retval) {
			case TTT_DRAW:
				std::cout << "MATCH DRAW!" << std::endl;
				return 0;

			case 1:
				std::cout << "COMPUTER WON!!!" << std::endl;
				return 0;
			}

			while (true) {
				std::cout << "Enter your move location as (" << p2Char << "): ";
				std::cin >> rowIndex >> columnIndex;
				rowIndex -= '0';
				columnIndex -= '0';
				if (rowIndex > 2 || rowIndex < 0 || columnIndex < 0 || columnIndex > 2) {
					std::cout << "Invalid row-column index." << std::endl;
					continue;
				}

				char retval = t.set(rowIndex, columnIndex, 2);
				if (retval == TTT_NOT_EMPTY) {
					std::cout << "Not empty place. Try again.\n\n";
					continue;
				}
				t.printBoard();

				switch (retval) {
				case TTT_DRAW:
					std::cout << "MATCH DRAW!" << std::endl;
					return 0;

				case 2:
					std::cout << "Player 2 wins!" << std::endl;
					return 0;
				}
				break;
			}
		}
	}

	return 0;
}
