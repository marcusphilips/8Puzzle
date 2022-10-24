#include "board.h"
// Board represents 3 by 3 board with the 8 numbers and the one-blank piece
// Blank piece will be 0

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
// the custom string input for the board the format should be precisely (ignore quotes)
// "size num_1 num_2 ... num_(size^2 - 1)"
// ex (ignore quotes)
// "3 "
Board::Board(const string &customBoard)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
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
Board::operator==(const Board& rhs) const {
    for ()
}
