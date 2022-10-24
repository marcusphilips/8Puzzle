#include "board.h"

/// @brief  Board represents n by n board with the 8 numbers and the one-blank piece
/// Blank piece will be 0
/// @param n 
Board::Board(int n)
{
    this->n = n; // set the dimension of the board
    // default method board will just create
    int num = 1;
    pos = int[n][n]; // n by n array as specified by the user
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (num != 9)
                pos[row][col] = num;
            else
                pos[row][col] = 0;
            num++;
        }
    }
}
/// @brief the custom string input for the board the format should be precisely (ignore quotes)
/// "num_1 num_2 ... num_(n^2 - 1) "
/// ex (ignore quotes) for 3 by 3 board
/// "1 3 4 5 6 8 2 7 "
/// Does not check for duplicates other than making sure the numbers are between 1 and n^2 - 1, inclusive
/// @param n how many rows or columns
/// @param customBoard a custom string representation of the board
Board::Board(int n, const std::string &customBoard)
{
    this->n = n;
    int i = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            int c = ((int)customBoard.at(i)) - 48;
            if (c >= 1 || c <= 8)
                pos[row][col] = c;
            else if (c == 0 || c == -16) // test for ASCII 0 or ' '
                pos[row][col] = 0;
            else
            {
                std::cout << "Error: invalid character used <" << (char)(c + 48) << ">\n"
                     << "Only numerals 1-8 or 0 or \' \' are valid for the the 8 Puzzle." << endl;
                exit(1);
            }
        }
    }
}
/// @brief Checks whether two boards are in equivalent states. Does not check size. That should be left to the user.
/// @param rhs 
/// @return bool
bool Board::operator==(const Board& rhs) const {
    for (int row = 0; row < n; row++){
        for (int col; col < n; col++){
            if (pos[row][col] != rhs.getPos(row, col)){
                return false;
            }
        }
    }
    return true;
}
