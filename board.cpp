#include "board.h"
// Board represents 3 by 3 board with the 8 numbers and the one-blank piece
// Blank piece will be 0

Board::Board()
{
    // default method board will just create
    int num = 1;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (num != 9)
                pos[row][col] = num;
            else
                pos[row][col] = 0;
        }
    }
}
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
                cout << "Error: invalid character used <" << (char)(c + 48) << ">\n"
                     << "Only numerals 1-8 or 0 or \' \' are valid for the the 8 Puzzle." << endl;
                exit(1);
            }
        }
    }
}
