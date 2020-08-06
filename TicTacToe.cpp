#include <iostream>
#include "TicTacToe.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

TicTacToe::TicTacToe()
{
	int i = 0;
	int j;
	for (; i < 3; i++)
		for (j = 0; j < 3; j++)
			board[i][j] = 0;

	srand(time(0));
	numOfPlacesConsumed = 0;
}

void TicTacToe::setPlayersCharacters(char p1, char p2)
{
	p1Char = p1;
	p2Char = p2;
}

void TicTacToe::printBoard()
{
	std::cout << std::string(13, '-') << std::endl;
	int i = 0, j;
	char charToPrint;
	for (; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			char theChar = board[i][j];
			if (theChar == 1)
				charToPrint = p1Char;
			else if (theChar == 2)
				charToPrint = p2Char;
			else
				charToPrint = ' ';
			std::cout << "| " << charToPrint << ' ';
		}
		std::cout << "|\n" << std::string(13, '-') << std::endl;
	}
}

bool TicTacToe::isHeWinner(char who)
{
	int i = 0, j;
	int contCount; // consecutive occuration count
	for (; i < 3; i++) {
		contCount = 0;
		for (j = 0; j < 3; j++) {
			if (board[i][j] == who)
				contCount++;
			else
				break;
		}
		if (contCount == 3) return true;
	}

	for (j = 0; j < 3; j++) {
		contCount = 0;
		for (i = 0; i < 3; i++) {
			if (board[i][j] == who)
				contCount++;
			else
				break;
		}
		if (contCount == 3) return true;
	}

	contCount = 0;
	for (i = 0, j = 0; i < 3; i++, j++) {
		if (board[i][j] == who)
			contCount++;
		else
			break;
	}
	if (contCount == 3) return true;

	contCount = 0;
	for (i = 2, j = 0; i > -1; i--, j++) {
		if (board[i][j] == who)
			contCount++;
		else
			break;
	}
	if (contCount == 3) return true;
	return false;
}

char TicTacToe::set(int x, int y, char value)
{
	if (board[x][y] != 0) return TTT_NOT_EMPTY;
	board[x][y] = value;
	bool nOneWins = isHeWinner(1);
	bool nTwoWins = isHeWinner(2);
	numOfPlacesConsumed++;

	char retval;
	if (!nOneWins && !nTwoWins && numOfPlacesConsumed == 9)
		retval = TTT_DRAW;
	else if (nOneWins && !nTwoWins)
		retval = 1;
	else if (nTwoWins && !nOneWins)
		retval = 2;
	else
		retval = TTT_NOTHING_HAPPENED;
	return retval;
}

std::vector <TicTacToe::Linear_Availables> *TicTacToe::getAvailablesFor(char who)
{
	std::vector <Linear_Availables> *retvalAvail; // it is a vector pointer
	try {
		retvalAvail = new std::vector<Linear_Availables>();
	} catch (std::bad_alloc &ex) {
		std::cout << "Error: Out of memory. " << ex.what() << std::endl;
		exit(0);
	}
	unsigned char i = 0, j;
	bool hasWho, hasEmptyPlaces;

	for (; i < 3; i++) { // rowic linearization
		hasWho = hasEmptyPlaces = false;
		for (j = 0; j < 3; j++) {
			if (board[i][j] == who)
				hasWho = true;
			else if (board[i][j] == 0)
				hasEmptyPlaces = true;

			if (hasWho && hasEmptyPlaces) {
				Linear_Availables linear_avails;
				linear_avails.consumedCount = 0;
				for (j = 0; j < 3; j++) {
					if (board[i][j] == who)
						linear_avails.consumedCount++;
					else if (board[i][j] == 0) {
						linear_avails.placesEmpty.push_back({i, j});
					}
				}
				retvalAvail->push_back(linear_avails);
				break;
			}
		}
	}

	for (j = 0; j < 3; j++) { // columnic linearization
		hasWho = hasEmptyPlaces = false;
		for (i = 0; i < 3; i++) {
			if (board[i][j] == who)
				hasWho = true;
			else if (board[i][j] == 0)
				hasEmptyPlaces = true;

			if (hasWho && hasEmptyPlaces) {
				Linear_Availables linear_avails;
				linear_avails.consumedCount = 0;
				for (i = 0; i < 3; i++) {
					if (board[i][j] == who)
						linear_avails.consumedCount++;
					else if (board[i][j] == 0) {
						linear_avails.placesEmpty.push_back({i, j});
					}
				}
				retvalAvail->push_back(linear_avails);
				break;
			}
		}
	}

	j = 0;
	hasWho = hasEmptyPlaces = false;
	for (i = 0; i < 3; i++, j++) { // left hand of X linearization
		if (board[i][j] == who)
			hasWho = true;
		else if (board[i][j] == 0)
			hasEmptyPlaces = true;

		if (hasWho && hasEmptyPlaces) {
			Linear_Availables linear_avails;
			linear_avails.consumedCount = 0;
			for (i = 0, j = 0; i < 3; i++, j++) {
				if (board[i][j] == who)
					linear_avails.consumedCount++;
				else if (board[i][j] == 0) {
					linear_avails.placesEmpty.push_back({i, j});
				}
			}
			retvalAvail->push_back(linear_avails);
			break;
		}
	}

	j = 2;
	hasWho = hasEmptyPlaces = false;
	for (i = 0; i < 3; i++, j--) { // right hand of X linearization
		if (board[i][j] == who)
			hasWho = true;
		else if (board[i][j] == 0)
			hasEmptyPlaces = true;

		if (hasWho && hasEmptyPlaces) {
			Linear_Availables linear_avails;
			linear_avails.consumedCount = 0;

			for (i = 0, j = 2; i < 3; i++, j--) {
				if (board[i][j] == who)
					linear_avails.consumedCount++;
				else if (board[i][j] == 0) {
					linear_avails.placesEmpty.push_back({i, j});
				}
			}
			retvalAvail->push_back(linear_avails);
			break;
		}
	}

	return retvalAvail;
}

void TicTacToe::cleanupAvailVector(std::vector <Linear_Availables> *availVector)
{
	int vectorSize = availVector->size();
	int i = 0;
	for ( ;i < vectorSize; i++) {
		(*availVector)[i].placesEmpty.clear();
	}
	availVector->clear();
	delete availVector;
}

char TicTacToe::getWhoCount(char who)
{
	int i = 0, j;
	char whoCount = 0;
	for (; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (board[i][j] == who)
				whoCount++;
		}
	}
	return whoCount;
}

void TicTacToe::pc_getAMoveLocation(unsigned char &rowIndex, unsigned char &columnIndex, char who)
{
	if (numOfPlacesConsumed == 9) return;
	else if (numOfPlacesConsumed == 0) {
		rowIndex = rand()%3;
		columnIndex = rand()%3;
		return;
	} else if (getWhoCount(who) == 0) {
		do {
			rowIndex = rand()%3;
			columnIndex = rand()%3;
		} while (board[rowIndex][columnIndex] != 0);
		return;
	}
	std::vector <Linear_Availables> *avails_wantedPlayer = getAvailablesFor(who); // both avail vectors are allocated on heap
	std::vector <Linear_Availables> *avails_otherPlayer = getAvailablesFor(who == 1 ? 2:1);

	int avail_size = avails_wantedPlayer->size();
	Linear_Availables *curLinearAvail;

	for (int i = 0; i < avail_size; i++) {
		curLinearAvail = &((*avails_wantedPlayer)[i]);
		if (curLinearAvail->consumedCount == 2) {
			rowIndex = curLinearAvail->placesEmpty[0].row;
			columnIndex = curLinearAvail->placesEmpty[0].column;
			cleanupAvailVector(avails_wantedPlayer);
			cleanupAvailVector(avails_otherPlayer);
			return;
		}
	}

	avail_size = avails_otherPlayer->size();
	for (int i = 0; i < avail_size; i++) {
		curLinearAvail = &((*avails_otherPlayer)[i]);
		if (curLinearAvail->consumedCount == 2) {
			rowIndex = curLinearAvail->placesEmpty[0].row;
			columnIndex = curLinearAvail->placesEmpty[0].column;
			cleanupAvailVector(avails_wantedPlayer);
			cleanupAvailVector(avails_otherPlayer);
			return;
		}
	}

	TTT_Coord chosenCoord;
	char curStageCount = 0; // stages that have been "continued"
	while (true) {
		Linear_Availables &chosenAvailRef = (*avails_wantedPlayer)[rand()%avails_wantedPlayer->size()];
		int emptySize = chosenAvailRef.placesEmpty.size();
		chosenCoord = chosenAvailRef.placesEmpty[rand()%emptySize];

		if (chosenAvailRef.consumedCount == 1 && emptySize == 1 && numOfPlacesConsumed < 4) {
			if (curStageCount > 4)
				break;
			curStageCount++;
			continue;
		}
		break;
	}
	rowIndex = chosenCoord.row;
	columnIndex = chosenCoord.column;

	cleanupAvailVector(avails_otherPlayer);
	cleanupAvailVector(avails_wantedPlayer);
}
