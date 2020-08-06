#include <vector>

#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

/* TTT stands for Tic Tac Toe */
#define TTT_DRAW (0)
#define TTT_NOTHING_HAPPENED (-1)
#define TTT_NOT_EMPTY (-2)

class TicTacToe {
private:
	char board[3][3];
	char p1Char, p2Char;
	char numOfPlacesConsumed; // count of places occupied

	typedef struct {
		unsigned char row;
		unsigned char column;
	} TTT_Coord; // tic tac toe coordinate

	/* Linear_Availables (although the name does not define the structure very well) is a structure
	   that is used to access the available empty cells in the tic tac toe board. For example the
	   following board has two consumed cells and one empty cell in second row. In other words
	   the second row is a Linear_Availables:
	   -------------
	   |   |   |   |
	   -------------
	   | O | O |   |
	   -------------
	   |   |   |   |
	   -------------

	   Linear_Availables.consumedCount contains the count for the cells that are occupied by any player
	 */
	typedef struct {
		char consumedCount;
		std::vector <TTT_Coord> placesEmpty;
	} Linear_Availables;

	bool isHeWinner(char who); // checks if the @who is a winner
	std::vector <Linear_Availables> *getAvailablesFor(char); // this function returns a vector to the Linear_Availables(s) that are in the board
	void cleanupAvailVector(std::vector <Linear_Availables> *availVector);
	char getWhoCount(char who);

public:
	TicTacToe();
	char set(int, int, char);
	void printBoard();
	void setPlayersCharacters(char, char);
	void pc_getAMoveLocation(unsigned char &, unsigned char &, char); // gets a move location as pc
};
#endif // TIC_TAC_TOE_H
